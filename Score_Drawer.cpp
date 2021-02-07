#include "Score_Drawer.h"
#include <string>
#include "Asset.h"
#include "VPoint.h"
void Score_Drawer::Init()
{
	UIDrawer::Init();

	//�����e�N�X�`���ǂݍ���
	for (size_t i = 0; i < 10; i++)
	{
		std::string path = "Asset/texture/";
		path += std::to_string(i);
		path += ".png";
		m_texture[i] = AssetsManager::Assign<TextureAsset>(path);
	}
}

void Score_Drawer::Update()
{
}

void Score_Drawer::Draw()
{
	Renderer::SetDepthEnable(true);

	SetShader();
	//���s���e
	Renderer::SetViewProjection2D();

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Vertexpoint->m_VertexBuffer, &stride, &offset);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	//�g�k�Ɖ�]�s��̂ݍ쐬
	D3DXMATRIX SR, scale, rotate;

	auto gameobject = GetOwnGameObject();
	
	D3DXQUATERNION	qRotate = gameobject->GetRotation();

	D3DXMatrixScaling(&scale, m_scl.x, m_scl.y, 1.0f);
	D3DXMatrixRotationQuaternion(&rotate, &qRotate);

	SR = scale * rotate;
	int score = m_score;

	for (size_t i = 0; i < 8; i++)
	{
		//�����e�N�X�`���ݒ�
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_texture[score % 10]->m_texture);

		D3DXMATRIX world, trans;
		float x = m_pos.x - m_scl.x * i;

		D3DXMatrixTranslation(&trans, x, m_pos.y, 1.0f);
		world = SR * trans;
		Renderer::SetWorldMatrix(&world);
		Renderer::GetDeviceContext()->Draw(1, 0);

		score /= 10;
	}



	Renderer::SetDepthEnable(true);
}
