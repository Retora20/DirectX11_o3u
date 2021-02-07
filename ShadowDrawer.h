#pragma once
#include "SpriteDrawer.h"
#include "VPoint.h"
class ShadowDrawer :
    public SpriteDrawer
{
public:
    virtual void Draw() override
    {
		SetShader();
		SetTexture();

		//マトリックス
		D3DXMATRIX world, scale, rotate, trans;

		auto gameobject = GetOwnGameObject();

		D3DXVECTOR3		vScale = gameobject->GetScale() * 2;
		D3DXQUATERNION	qRotate;
		D3DXVECTOR3		vPosition = gameobject->GetPosition();


		D3DXQuaternionRotationYawPitchRoll(&qRotate, 0, D3DXToRadian(90), 0);
		vPosition.y = 0.01f;

		D3DXMatrixScaling(&scale, vScale.x, vScale.y, vScale.z);
		D3DXMatrixRotationQuaternion(&rotate, &qRotate);
		D3DXMatrixTranslation(&trans, vPosition.x, vPosition.y, vPosition.z);

		world = scale * rotate * trans;
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
};

