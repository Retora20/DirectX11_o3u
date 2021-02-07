#include "GameObject.h"
#include "Component.h"

GameObject::GameObject() :m_position(0.0f, 0.0f, 0.0f), m_scale(1.0f, 1.0f, 1.0f)
{
	D3DXQuaternionIdentity(&m_rotation);
}

D3DXVECTOR3 GameObject::GetFrontVector()
{
	D3DXMATRIX rot;
	D3DXMatrixRotationQuaternion(&rot, &m_rotation);
	D3DXVECTOR3 tmp;
	D3DXVec3Normalize(&tmp,&D3DXVECTOR3(rot._31, rot._32, rot._33));
	return tmp;
}

D3DXVECTOR3 GameObject::GetRightVector()
{
	D3DXMATRIX rot;
	D3DXMatrixRotationQuaternion(&rot, &m_rotation);
	D3DXVECTOR3 tmp;
	D3DXVec3Normalize(&tmp, &D3DXVECTOR3(rot._11, rot._12, rot._13));
	return tmp;
}

D3DXVECTOR3 GameObject::GetUpVector()
{
	D3DXMATRIX rot;
	D3DXMatrixRotationQuaternion(&rot, &m_rotation);
	D3DXVECTOR3 tmp;
	D3DXVec3Normalize(&tmp, &D3DXVECTOR3(rot._21, rot._22, rot._23));
	return tmp;
}

void GameObject::ComponentsUnInit()
{
	for (auto& i : m_components)
	{
		i->UnInit();
		delete i;
	}
}

void GameObject::ComponentsUpdate()
{
	for (auto p : m_components) p->Update();

	//保留中のコンポーネントがある場合初期化をしてUpdate、保留リストから削除
	if (!m_pendComponents.empty())
	{
		for (auto p : m_pendComponents)
		{//初期化
			p->SetOwnGameObject(this);
			p->Init();
		}

		for (auto p : m_pendComponents)
		{//アップデート
			p->Update();
			m_components.push_back(p);
		}

		m_pendComponents.clear();
	}
}