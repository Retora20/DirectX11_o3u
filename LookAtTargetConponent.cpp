#include "LookAtTargetConponent.h"

void LookAtTargetConponent::Init()
{
}

void LookAtTargetConponent::UnInit()
{
}

void LookAtTargetConponent::Update()
{
	auto own = GetOwnGameObject();
	D3DXVECTOR3 vec = m_target->GetPosition() - own->GetPosition();
	vec.y = 0.0f;
	
	D3DXQUATERNION q;
	D3DXQuaternionRotationAxis(&q, &D3DXVECTOR3(0, 1, 0), atan2f(vec.x, vec.z));

	own->SetRotation(q);

}

void LookAtTargetConponent::SetTarget(GameObject* target)
{
	m_target = target;
}
