#include "SliderDrawer.h"
#include "VPositon.h"
void SliderDrawer::Init()
{
	m_vposition = AssetsManager::Assign<VPosition>("VPosition");

	m_vs = AssetsManager::Assign<VSPosition_Asset>(std::string("NopLineVS.cso"));
	m_hs = AssetsManager::Assign<HS_Asset>(std::string("LineHS.cso"));
	m_ds = AssetsManager::Assign<DS_Asset>(std::string("LineDS.cso"));
	m_gs = AssetsManager::Assign<GS_Asset>(std::string("LineGS.cso"));
	m_ps = AssetsManager::Assign<PS_Asset>(std::string("SliderPS.cso"));

	DrawerRegister();

	//cp設定
	cp.CP_Num = m_data.CpNum;

	for (size_t i = 0; i < cp.CP_Num; i++)
	{
		const auto& p = m_data.Positions[i];
		cp.CP[i] = D3DXVECTOR4(p.x, p.y, p.z, 0);
	}
}

void SliderDrawer::Update()
{
	if (!m_isUse)	return;
}

void SliderDrawer::Draw()
{
	if (!m_isUse)	return;


	Renderer::UpdateCP(&cp);

	SetShader();
	CreateAndSetWorldMatrix();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_Positon);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vposition->m_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST));

	//描画
	Renderer::GetDeviceContext()->Draw(1, 0);
}
