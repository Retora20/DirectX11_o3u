#include "Component.h"

void Drawer::SetShader()
{
	auto context = Renderer::GetDeviceContext();

	//vertex
	if (m_vs)
	{
		context->IASetInputLayout(m_vs->m_VertexLayout);
		context->VSSetShader(m_vs->m_vs, NULL, 0);
	}

	//pixel
	if (m_ps)	context->PSSetShader(m_ps->m_ps, NULL, 0);

	//Hull
	if (m_hs)	context->HSSetShader(m_hs->m_hs, NULL, 0);
	else		context->HSSetShader(NULL, NULL, 0);

	//domain
	if (m_ds)	context->DSSetShader(m_ds->m_ds, NULL, 0);
	else		context->DSSetShader(NULL, NULL, 0);

	//geometry
	if (m_gs)	context->GSSetShader(m_gs->m_gs, NULL, 0);
	else		context->GSSetShader(NULL, NULL, 0);
}

void Drawer::SetTexture()
{
	// テクスチャ設定
	if (m_texture)
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_texture->m_texture);
}

void Drawer::CreateAndSetWorldMatrix()
{
	//マトリックス
	D3DXMATRIX world, scale, rotate, trans;

	auto gameobject = GetOwnGameObject();

	D3DXVECTOR3		vScale = gameobject->GetScale();
	D3DXQUATERNION	qRotate = gameobject->GetRotation();
	D3DXVECTOR3		vPosition = gameobject->GetPosition();

	D3DXMatrixScaling(&scale, vScale.x, vScale.y, vScale.z);
	D3DXMatrixRotationQuaternion(&rotate, &qRotate);
	D3DXMatrixTranslation(&trans, vPosition.x, vPosition.y, vPosition.z);

	world = scale * rotate * trans;
	Renderer::SetWorldMatrix(&world);
}
