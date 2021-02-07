#include "LookAtCameraComponent.h"
//#include "CameraGameSceneObject.h"
void LookAtCameraComponent::Init()
{
	//camera = Game::GetScene()->GetGameObject<CameraGameSceneObject>();
}

void LookAtCameraComponent::UnInit()
{

}

void LookAtCameraComponent::Update()
{
	D3DXVECTOR3 camfront = camera->GetFrontVector();
	camfront.y = 0;
	D3DXVec3Normalize(&camfront, &camfront);

//	float rad = acos(D3DXVec3Dot(&camfront, &D3DXVECTOR3(0, 0, 1)));
	float rad = atan2f(camfront.x, camfront.z);
	D3DXQUATERNION q;
	D3DXQuaternionRotationAxis(&q, &D3DXVECTOR3(0, 1, 0),rad);
	GetOwnGameObject()->SetRotation(q);
}
