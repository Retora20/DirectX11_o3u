#include "o3u_CameraGameObject.h"
#include "CameraComponent.h"
#include "Time.h"
#include  "MapObjectMgrGameObject.h"
#include "MapObjectManager.h"

void o3u_CameraGameObject::Init()
{
	AddCompoent<CameraComponent>();
}


void o3u_CameraGameObject::Update()
{
	float rad =  m_curtime *0.4;


	m_position.x = sinf(rad) * 10;
	m_position.z = cosf(rad) * 10;

	D3DXQuaternionRotationYawPitchRoll(&m_rotation, rad + D3DX_PI, 0, 0);

	ComponentsUpdate();
}

void o3u_CameraGameObject::Uninit()
{
}
