#include "AC_Drawer.h"
#include "Asset.h"
#include "VPositon.h"
#include "CameraComponent.h"
#include "CameraGameObject.h"
#include "input.h"

void AC_Drawer::Init()
{
	SetRQ(RQ::AlphaTest + 1);
	DrawerRegister();

	m_vposition = AssetsManager::Assign<VPosition>("VPosition");

	m_vs = AssetsManager::Assign<VSPosition_Asset>(std::string("NopLineVS.cso"));
	m_gs = AssetsManager::Assign<GS_Asset>(std::string("CircleGS.cso"));
	m_ps = AssetsManager::Assign<PS_Asset>(std::string("AC_PS.cso"));

	//親オブジェクトのpos,sclは使わないでワールド行列を作成する
	m_pos = m_data.Positions[0];

}

void AC_Drawer::Update()
{

}

void AC_Drawer::Draw()
{
	if (!m_isUse)	return;


	SetShader();

	//ワールド行列作成
	D3DXMATRIX world ,tmp;
	D3DXMatrixIdentity(&world);

	D3DXMatrixScaling(&tmp,m_scale, m_scale, m_scale);
	world *= tmp;

	D3DXMatrixTranslation(&tmp, m_pos.x, m_pos.y, m_pos.z);
	world *= tmp;

	Renderer::SetWorldMatrix(&world);

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
