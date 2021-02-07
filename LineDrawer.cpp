#include "AudioManeger.h"
#include "Asset.h"
#include "VPositon.h"
#include "input.h"
#include "LineDrawer.h"
#include "MapAsset.h"

void LineDrawer::Init()
{
	m_vposition = AssetsManager::Assign<VPosition>("VPosition");

	m_vs = AssetsManager::Assign<VS_Asset>(std::string("NopLineVS.cso"));
	m_hs = AssetsManager::Assign<HS_Asset>(std::string("LineHS.cso"));
	m_ds = AssetsManager::Assign<DS_Asset>(std::string("LineDS.cso"));
	m_gs = AssetsManager::Assign<GS_Asset>(std::string("TitleLineGS.cso"));
	m_ps = AssetsManager::Assign<PS_Asset>(std::string("LinePS.cso"));

	DrawerRegister();
	Renderer::SetZTest(false);
}

void LineDrawer::Update()
{
}

void LineDrawer::Draw()
{
	Renderer::UpdateCP(&cp);

	MATERIAL mt;
	mt.Diffuse = m_color;
	Renderer::SetMaterial(mt);


	SetShader();
	CreateAndSetWorldMatrix();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_Positon);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vposition->m_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST));

	Renderer::SetBlendStateAdd();
	Renderer::SetZTest(false);
	Renderer::SetDepthEnable(false);

	//描画
	Renderer::GetDeviceContext()->Draw(1, 0);
	Renderer::SetDepthEnable(true);
	Renderer::SetZTest(true);
	Renderer::SetBlendStateDefault();
}
