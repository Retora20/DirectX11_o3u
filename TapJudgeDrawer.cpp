#include "TapJudgeDrawer.h"
#include "Time.h"
#include "VPositon.h"
void TapJudgeDrawer::Init()
{
	SetRQ(RQ::AlphaTest + 2);
	DrawerRegister();

	m_vposition = AssetsManager::Assign<VPosition>("VPosition");

	m_vs = AssetsManager::Assign<VSPosition_Asset>(std::string("NopLineVS.cso"));
	m_gs = AssetsManager::Assign<GS_Asset>(std::string("JudgeGS.cso"));
	m_ps = AssetsManager::Assign<PS_Asset>(std::string("TexturePS.cso"));
}

void TapJudgeDrawer::Update()
{
	m_timer += Time::GetDeltaTime();

	if (m_timer>=1.0f)	GetOwnGameObject()->Destroy();
}

void TapJudgeDrawer::Draw()
{
	SetShader();
	SetTexture();
	CreateAndSetWorldMatrix();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_Positon);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vposition->m_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	Renderer::SetZTest(false);
	Renderer::SetDepthEnable(false);
	//描画
	Renderer::GetDeviceContext()->Draw(1, 0);
	Renderer::SetDepthEnable(true);
	Renderer::SetZTest(true);
}
