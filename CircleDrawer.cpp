#include "CircleDrawer.h"
#include "Asset.h"
#include "VPositon.h"
#include "CameraComponent.h"
#include "CameraGameObject.h"
#include "input.h"
void CircleDrawer::Init()
{
	DrawerRegister();

	m_vposition = AssetsManager::Assign<VPosition>("VPosition");

	m_vs = AssetsManager::Assign<VSPosition_Asset>(std::string("NopLineVS.cso"));
	m_gs = AssetsManager::Assign<GS_Asset>(std::string("CircleGS.cso"));
	m_ps = AssetsManager::Assign<PS_Asset>(std::string("SliderPS.cso"));
	//m_ps = AssetsManager::Assign<PS_Asset>(std::string("AC_PS.cso"));

	GetOwnGameObject()->SetPosition(m_data.Positions[0]);
}

void CircleDrawer::Update()
{
	if (!m_isUse)	return;
}

void CircleDrawer::Draw()
{
	if (!m_isUse)	return;


	SetShader();
	CreateAndSetWorldMatrix();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_Positon);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vposition->m_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	//描画
	Renderer::GetDeviceContext()->Draw(1, 0);
}
