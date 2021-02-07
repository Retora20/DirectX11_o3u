#include "SpriteDrawer.h"
#include "Asset.h"
#include "VPoint.h"
void SpriteDrawer::Init()
{
	m_vpoint = AssetsManager::Assign<VPoint>("VPonit");

	m_vs = AssetsManager::Assign<VS_Asset>(std::string("VSSample.cso"));
	m_gs = AssetsManager::Assign<GS_Asset>(std::string("GSQuad.cso"));
	m_ps = AssetsManager::Assign<PS_Asset>(std::string("PSTexture.cso"));

	DrawerRegister();
}

void SpriteDrawer::Update()
{
}

void SpriteDrawer::Draw()
{
	SetShader();
	SetTexture();
	CreateAndSetWorldMatrix();

	//プリミティブ・トポロジーをセット
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	//Renderer::SetDepthEnable(false);


	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1,&m_vpoint->m_VertexBuffer , &stride, &offset);
	Renderer::GetDeviceContext()->Draw(1, 0);
}