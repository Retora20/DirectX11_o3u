#include "UIDrawer.h"
#include "Renderer.h"
#include "TextureAsset.h"
#include "VPoint.h"


void UIDrawer::Init()
{
	m_Vertexpoint = AssetsManager::Assign<VPoint>(std::string("VPoint"));

	m_vs = AssetsManager::Assign<VS_Asset>(std::string("VSNop.cso"));
	m_gs = AssetsManager::Assign<GS_Asset>(std::string("GSQuad.cso"));
	m_ps = AssetsManager::Assign<PS_Asset>(std::string("PSTexture.cso"));

	SetRQ(RQ::Overlay);
	DrawerRegister();
}

void UIDrawer::Update()
{
}

void UIDrawer::Draw()
{
	SetShader();
	SetTexture();
	//並行投影
	Renderer::SetViewProjection2D();
	CreateAndSetWorldMatrix();

	//プリミティブ・トポロジーをセット
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	//Renderer::SetDepthEnable(false);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Vertexpoint->m_VertexBuffer, &stride, &offset);
	Renderer::GetDeviceContext()->Draw(1, 0);

	Renderer::SetDepthEnable(true);
}