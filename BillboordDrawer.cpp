#include "BillboordDrawer.h"
//#include "CameraGameSceneObject.h"
#include "CameraComponent.h"
#include "VPoint.h"
void BillboordDrawer::Init()
{
	//camera = Game::GetScene()->GetGameObject<CameraGameSceneObject>()->GetCompoent<CameraComponent>();

	m_vpoint = AssetsManager::Assign<VPoint>("VPonit");

	m_vs = AssetsManager::Assign<VS_Asset>(std::string("VSNop.cso"));
	m_gs = AssetsManager::Assign<GS_Asset>(std::string("GSQuad.cso"));
	m_ps = AssetsManager::Assign<PS_Asset>(std::string("PSTexture.cso"));

	SetRQ(RQ::AlphaTest);
	DrawerRegister();
}

void BillboordDrawer::Update()
{
}

void BillboordDrawer::Draw()
{
	SetShader();
	SetTexture();
	//CreateAndSetWorldMatrix();

	//マトリックス
	D3DXMATRIX world, scale, rotate,invView, trans;

	auto gameobject = GetOwnGameObject();

	D3DXVECTOR3		vScale = gameobject->GetScale();
	D3DXQUATERNION	qRotate = gameobject->GetRotation();
	D3DXVECTOR3		vPosition = gameobject->GetPosition();

	D3DXMatrixScaling(&scale, vScale.x, vScale.y, vScale.z);
	D3DXMatrixRotationQuaternion(&rotate, &qRotate);
	D3DXMatrixTranslation(&trans, vPosition.x, vPosition.y, vPosition.z);

	D3DXMatrixTranspose(&invView, &camera->GetViewMatrix());
	invView._14 = invView._24 = invView._34 = 0.0f;
	world = scale * rotate  * invView * trans;
	Renderer::SetWorldMatrix(&world);

	//プリミティブ・トポロジーをセット
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	//Renderer::SetDepthEnable(false);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vpoint->m_VertexBuffer, &stride, &offset);
	Renderer::GetDeviceContext()->Draw(1, 0);
}