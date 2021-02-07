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
	//���s���e
	Renderer::SetViewProjection2D();
	CreateAndSetWorldMatrix();

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	//Renderer::SetDepthEnable(false);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Vertexpoint->m_VertexBuffer, &stride, &offset);
	Renderer::GetDeviceContext()->Draw(1, 0);

	Renderer::SetDepthEnable(true);
}