//---------------------------------------------------------
//	GameObject						Date	2020/7/19
//									Author	�{�����		
//	�S�ẴQ�[���I�u�W�F�N�g���N���X
//---------------------------------------------------------
#pragma once
#include "main.h"
#include <vector>
#include <algorithm>
class GameObject
{
public:
	//�ǉ����������o�̏������A���\�[�X�擾�A�R���|�[�l���g�ǉ��̓R���X�g���N�^�ōs���܂�
	GameObject();

	//Asset�ȊO�̃������J�����f�X�g���N�^�ōs���܂�
	virtual ~GameObject() {}

	//�����ł͑��̃Q�[���I�u�W�F�N�g���Q�Ə����������鏈���������܂�
	virtual void Init() = 0;

	//�����ł͑��̃Q�[���I�u�W�F�N�g���Q�Ə����������鏈���������܂�
	virtual void Uninit() = 0;

	//�����Œǉ����������o���X�V���܂�
	//�g���܂킹�鏈���̓R���|�[�l���g�ɂ���
	//�R���|�[�l���g��ComponentsUpdate()���Ă�ōX�V���܂�
	virtual void Update() { ComponentsUpdate(); }

	//�`��̓R���|�[�l���g����ĕ`�悵�܂�
	//Draw�͔�r�I���������ɂȂ肪���Ȃ̂ŕK���R���|�[�l���g����ĕ`�悵�܂�

	//transform

	virtual D3DXVECTOR3 GetPosition()	final { return m_position; }
	virtual D3DXQUATERNION GetRotation()final { return m_rotation; }
	virtual D3DXVECTOR3 GetScale()		final { return m_scale; }

	virtual void SetPosition(const D3DXVECTOR3& inPos)		final{ m_position = inPos; }
	virtual void SetRotation(const D3DXQUATERNION& inRot)	final{ m_rotation = inRot; }
	virtual void SetScale(const D3DXVECTOR3& inScl)			final{ m_scale = inScl; }

	D3DXVECTOR3 GetFrontVector();
	D3DXVECTOR3 GetRightVector();
	D3DXVECTOR3 GetUpVector();

	//�R���|�[�l���g�ǉ�(�ۗ����X�g�ɒǉ��j
	//���̎��_�ł̓C���X�^���X�͐�������邪�R���|�[�l���g����Init()���Ă΂�Ȃ����ɒ���
	template<class T>
	T* AddCompoent()
	{
		T* comp = new T;
		m_pendComponents.push_back(comp);
		return comp;
	}

	template<class T>
	T* DestroyCompoent()
	{
		auto f = [](T* x)
		{
			if (typeid(*x) == typeid(T))	return true;
			else false;
		};
		std::remove_if(m_components.begin(), m_components.end(), f);
		std::remove_if(m_pendComponents.begin(), m_pendComponents.end(), f);
	}

	template<class T>
	T* GetCompoent()
	{
		for (auto comp: m_components)
		{
			if (typeid(*comp) == typeid(T))	return static_cast<T*>(comp);
		}
		//�ۗ����X�g���Q��
		for (auto comp : m_pendComponents)
		{
			if (typeid(*comp) == typeid(T))return static_cast<T*>(comp);
		}
		return nullptr;
	}

	//���g���폜���܂�
	virtual void Destroy() final { m_IsDestroy = true; }

	//�폜�t���O��Ԃ��܂�
	virtual bool GetIsDestroy() final { return m_IsDestroy; }

	virtual void ComponentsUnInit();

protected:
	//Update���I�[�o�[���C�h�����ۂ͂�����Ă�ł�������
	virtual void ComponentsUpdate() final;

	D3DXVECTOR3		m_position;
	D3DXQUATERNION	m_rotation;
	D3DXVECTOR3		m_scale;

private:
	std::vector<class Component*> m_components, m_pendComponents;
	bool m_IsDestroy = false;
};