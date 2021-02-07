#include "MeshDrawer.h"

void FieldDrawer::Init()
{
	//m_vpoint = AssetsManager::Assign<VPoint>("VPonit");

	m_vs = AssetsManager::Assign<VS_Asset>(std::string("VSSample.cso"));
	//m_gs = AssetsManager::Assign<GS_Asset>(std::string("GSQuad.cso"));
	m_ps = AssetsManager::Assign<PS_Asset>(std::string("PSSample.cso"));

	SetRQ(RQ::BackGround);
	DrawerRegister();


	//暫定

	//頂点
	{
		for (int x = 0; x <= 20; x++)
		{
			for (int z = 0; z <= 20; z++)
			{
				float y = sinf(x * 4 + z * 1)*2.5f - abs(x -10) - abs(z - 10);
				 y = 0;
				m_vertex[x][z].Position = D3DXVECTOR3((x - 10) * 1.0f,y, (z - 10) * -1.0f);
				m_vertex[x][z].Normal = D3DXVECTOR3(0, 1, 0);
				m_vertex[x][z].Diffuse = D3DXVECTOR4(1, 1, 1, 1);
				m_vertex[x][z].TexCoord = D3DXVECTOR2(x * 0.5f, z * 0.5f);
			}
		}
		for (int x = 1; x <= 19; x++)
		{
			for (int z = 1; z <= 19; z++)
			{
				D3DXVECTOR3 vx, vz, vn;

				vx = m_vertex[x + 1][z].Position - m_vertex[x - 1][z].Position;
				vz = m_vertex[x][z - 1].Position - m_vertex[x][z + 1].Position;

				D3DXVec3Cross(&vn, &vz, &vx);
				D3DXVec3Normalize(&vn, &vn);
				m_vertex[x][z].Normal = vn;
			}
		}
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * 21 * 21;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_vertex;
		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);
	}

	//インデックス
	{
		unsigned int index[(22 * 2) * 20 - 2];
		int i = 0;

		for (int x = 0; x < 20; x++)
		{
			for (int z = 0; z < 21; z++)
			{
				index[i] = x * 21 + z;
				i++;

				index[i] = (x + 1) * 21 + z;
				i++;
			}

			if (x == 19)	break;

			index[i] = (x + 1) * 21 + 20;
			i++;

			index[i] = (x + 1) * 21;
			i++;
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * ((22 * 2) * 20 - 2);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_indexBuffer);
	}

}

void FieldDrawer::Update()
{
}

void FieldDrawer::Draw()
{
	SetShader();
	SetTexture();
	CreateAndSetWorldMatrix();

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1,
		&m_vertexBuffer, &stride, &offset);

	Renderer::GetDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//MATERIAL mt;
	//ZeroMemory(&mt, sizeof(mt));
	//mt.Diffuse = D3DXCOLOR(1, 1, 1, 1);
	//Renderer::SetMaterial(mt);

	//プリミティブ・トポロジーをセット
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	Renderer::GetDeviceContext()->DrawIndexed((22 * 2) * 20 - 2, 0, 0);
}

float FieldDrawer::GetHeight(D3DXVECTOR3 position)
{
	int x, z;

	//ブロック番号算出
	x = position.x / 5.0f + 10.0f;
	z = position.z / -5.0f + 10.0f;

	D3DXVECTOR3 p0, p1, p2, p3;

	p0 = m_vertex[x][z].Position;
	p1 = m_vertex[x+1][z].Position;
	p2 = m_vertex[x][z+1].Position;
	p3 = m_vertex[x+1][z+1].Position;


	D3DXVECTOR3 v12, v1p, c;

	v12 = p2 - p1;
	v1p = position - p1;

	D3DXVec3Cross(&c, &v12, &v1p);

	float py;
	D3DXVECTOR3 n;

	if (c.y>0)
	{
		//左上ポリゴン
		D3DXVECTOR3 v10;

		v10 = p0 - p1;
		D3DXVec3Cross(&n, &v10, &v12);
	}
	else
	{
		//右下ポリゴン
		D3DXVECTOR3 v13;

		v13 = p3 - p1;
		D3DXVec3Cross(&n, &v12, &v13);
	}

	//高さ取得
	py = -((position.x - p1.x) * n.x + (position.z - p1.z) * n.z) / n.y + p1.y;

	return py;
}
