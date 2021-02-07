//---------------------------------------------------------
//	CameraComponent					Date	2020/7/18
//									Author	本多玲虎		
//	GameObjectのtranceformからRendererにカメラ情報を渡すだけ
//---------------------------------------------------------

#include "main.h"
#include "Component.h"
#include <utility>
#pragma once
class CameraComponent:public Component
{
public:
	CameraComponent();

	virtual void Init() override;
	virtual void UnInit() override;
	virtual void Update() override;

	virtual D3DXMATRIX GetProjectionMatrix() final;
	virtual D3DXMATRIX GetViewMatrix() final;

	//first 手前位置、second 正規化済み方向
	virtual std::pair<D3DXVECTOR3, D3DXVECTOR3> GetMouseVector();

protected:
	D3DXVECTOR3 m_EulerAngle = {0,0,0};

	float m_fov = 1.0f;
	float m_near = 0.1f;
	float m_far = 1000.0f;

	D3DXMATRIX m_view, m_projection;
};

