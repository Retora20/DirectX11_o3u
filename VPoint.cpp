#include "VPoint.h"
#include "model.h"
void VPoint::Load(std::string filename)
{
	VERTEX_3D data =
	{
		D3DXVECTOR3(0,0,0),		//pos
		D3DXVECTOR3(0,0,-1),	//normal
		D3DXVECTOR4(1,1,1,1),	//Diffuse
		D3DXVECTOR2(0.5,0.5)	//TexCoor
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &data;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

void VPoint::Unload()
{
	m_VertexBuffer->Release();
}
