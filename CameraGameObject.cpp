#include "CameraGameObject.h"
#include "CameraComponent.h"
#include "FPSCameraMoveComponent.h"
#include "WASDComponant.h"
#include "Time.h"
CameraGameObject::CameraGameObject()
{
	m_position = D3DXVECTOR3(0, 3.0, -5);
	D3DXQuaternionRotationYawPitchRoll(&m_rotation, 0,0, 0);
	AddCompoent<CameraComponent>();
	AddCompoent<FPSCameraMoveComponent>();
	AddCompoent<WASDComponant>();
}

void CameraGameObject::Init()
{
}

void CameraGameObject::Uninit()
{
}

void CameraGameObject::Update()
{
	ComponentsUpdate();
}
