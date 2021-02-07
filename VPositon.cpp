#include "VPositon.h"
#include "Renderer.h"
void VPosition::Load(std::string filename)
{
	VERTEX_Positon data =
	{
		D3DXVECTOR4(0,0,0,0)		//pos
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_Positon);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &data;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

void VPosition::Unload()
{
	m_VertexBuffer->Release();
}
