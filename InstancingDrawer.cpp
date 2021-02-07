#include "InstancingDrawer.h"
#include "Asset.h"
#include "SpriteDrawer.h"

static const int Grassnum = 1000;
void InstancingDrawer::Init()
{
	VERTEX_3D data[4] =
	{
		{		
		D3DXVECTOR3(-0.5f,0.5f,0),		//pos
		D3DXVECTOR3(0,0,-1),	//normal
		D3DXVECTOR4(1,1,1,1),	//Diffuse
		D3DXVECTOR2(0,0)	//TexCoor
		},
		{
		D3DXVECTOR3(0.5f,0.5f,0),//pos
		D3DXVECTOR3(0,0,-1),	//normal
		D3DXVECTOR4(1,1,1,1),	//Diffuse
		D3DXVECTOR2(1,0.0)	//TexCoor
		},
		{
		D3DXVECTOR3(-0.5f,-0.5f,0),		//pos
		D3DXVECTOR3(0,0,-1),	//normal
		D3DXVECTOR4(1,1,1,1),	//Diffuse
		D3DXVECTOR2(0,1)	//TexCoor
		},
		{
		D3DXVECTOR3(0.5f,-0.5f,0),		//pos
		D3DXVECTOR3(0,0,-1),	//normal
		D3DXVECTOR4(1,1,1,1),	//Diffuse
		D3DXVECTOR2(1,1)	//TexCoor
		}

	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &data;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


	m_vs = AssetsManager::Assign<VS_Asset>(std::string("GrassVS.cso"));
	m_ps = AssetsManager::Assign<PS_Asset>(std::string("AlphaTest.cso"));

	m_texture = AssetsManager::Assign<TextureAsset>("Asset/texture/akiemon.png");
//	m_texture = AssetsManager::Assign<TextureAsset>("Asset/texture/m.png");
	//m_texture = AssetsManager::Assign<TextureAsset>("Asset/texture/TT.png");

	DrawerRegister();


	{//ストラクチャードバッファ生成
		auto pos = new D3DXVECTOR3[Grassnum* Grassnum];
		int i = 0;
		for (int x = 0; x < Grassnum; x++)
		{
			for (int z = 0; z < Grassnum; z++)
			{
				pos[i] = D3DXVECTOR3(x * 2, 0.0f, z * 2);
				i++;
			}
		}
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;//D3D11_USAGE_DYNAMIC
		bd.ByteWidth = sizeof(D3DXVECTOR3)* Grassnum * Grassnum;
		bd.StructureByteStride = sizeof(D3DXVECTOR3);
		bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		bd.CPUAccessFlags = 0;//D3D11_CPU_ACCESS_WRITE

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pos;
		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_positionBuffer);
		delete[] pos;

		//シェーダーリソースビュー
		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		ZeroMemory(&srvd, sizeof(srvd));

		srvd.Format= DXGI_FORMAT_UNKNOWN;
		srvd.ViewDimension= D3D11_SRV_DIMENSION_BUFFER;
		srvd.Buffer.FirstElement = 0;
		srvd.Buffer.NumElements = Grassnum * Grassnum;
		Renderer::GetDevice()->CreateShaderResourceView(m_positionBuffer,
			&srvd, &m_positionSRV);

	}
	
	GetOwnGameObject()->SetScale(D3DXVECTOR3(0.1, 0.2, 0.1));

}

void InstancingDrawer::UnInit()
{
	m_positionBuffer->Release();
	m_positionSRV->Release();
}

void InstancingDrawer::Update()
{
}

void InstancingDrawer::Draw()
{
	SetShader();
	SetTexture();
	CreateAndSetWorldMatrix();

	//プリミティブ・トポロジーをセット
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//Renderer::SetDepthEnable(false);

	//ストラクチャードバッファ設定
	Renderer::GetDeviceContext()->VSSetShaderResources(2, 1, &m_positionSRV);


	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	//Renderer::GetDeviceContext()->Draw(4, 0);
	Renderer::GetDeviceContext()->DrawInstanced(4, Grassnum * Grassnum, 0, 0);
}
