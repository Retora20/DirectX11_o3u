//#include "TitleLogoGameObject.h"
//#include "Time.h"
//#include "StaticModelDrawer.h"
//#include "SaruDrawer.h"
//void TitleLogoGameObject::Init()
//{
//	AddCompoent<SaruDrawer>()->SetModel(std::string("Asset\\model\\titlelogo\\titlelogo.obj"));
//
//	m_scale *= 4.0f;
//	m_position.y = 0.5f;
//	m_position.z = 1.0f;
//
//}
//
//void TitleLogoGameObject::Uninit()
//{
//}
//
//inline void LookAt(D3DXQUATERNION* out, D3DXQUATERNION* q, D3DXVECTOR3* position, D3DXVECTOR3* target, float t = 1.0f )
//{
//	//�^�[�Q�b�g�ւ̃x�N�g���v�Z
//	D3DXVECTOR3 targetvec = *target - *position;
//	D3DXVec3Normalize(&targetvec, &targetvec);
//
//	//�N�H�[�^�j�I����������x�N�g���̋��ߕ����킩��Ȃ�
//	D3DXMATRIX rot;
//	D3DXMatrixRotationQuaternion(&rot, q);
//	D3DXVECTOR3 rotvec = D3DXVECTOR3(rot._31, rot._32, rot._33);
//	D3DXVec3Normalize(&rotvec, &rotvec);
//
//	// ��]�p�x���v�Z
//	float angle = acos(D3DXVec3Dot(&targetvec, &rotvec));
//	if (angle < 0.001f )
//	{
//		return;
//	}
//
//	//��]���v�Z
//	D3DXVECTOR3 axis;
//	D3DXVec3Cross(&axis, &rotvec, &targetvec);
//	D3DXVec3Normalize(&axis, &axis);
//
//	//�^�[�Q�b�g�̃N�H�[�^�j�I���v�Z
//	D3DXQuaternionIdentity(out);
//	D3DXQuaternionRotationAxis(out, &axis, angle);
//	D3DXQuaternionNormalize(out, out);
//
//	//t�̒l�ɕ��
//	//D3DXQuaternionSlerp(out, q, out, t);
//}
//
//void TitleLogoGameObject::Update()
//{
//	m_scale.z = sinf(Time::GetTime()) * 1.5f;
//	
//	//LookAt(&m_rotation, &m_rotation, &m_position, &D3DXVECTOR3(cosf(Time::GetTime()), 0, 0));
//
//	//D3DXQuaternionNormalize(&m_rotation, &m_rotation);
//	ComponentsUpdate();
//}