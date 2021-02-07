//---------------------------------------------------------
//	Scene_Base						Date	2020/7/19
//									Author	�{�����		
//	�V�[���̊��
//	Update�̓��C���[�����ADraw�̓\�[�g���čs���܂�
//	�p����ł͊�{�I�ɃR���X�g���N�^�݂̂̏����������Ă����܂�
//---------------------------------------------------------
#pragma once
#include <vector>
#include <list>
#include <utility>
#include <typeinfo>

class DrawManager;

enum UpdateLayer
{
	FIRST = 0, 
	DEFAULT,
	LAST,
	MAX
};

class Scene_Base
{
public:
	Scene_Base();
	virtual ~Scene_Base() ;

	//������p�����ăV�[���ɍŏ����炠��Q�[���I�u�W�F�N�g���쐬���܂�
	virtual void CreateGameObject()= 0;


	//�I�u�W�F�N�g�𐶐����ۗ����X�g�ɒǉ����܂�
	//���̎��_��Init()���Ă΂�Ȃ����Ƃɒ���
	template<class T>
	T* AddGameObject(UpdateLayer layer = DEFAULT)
	{
		T* obj = new T;

		std::vector<std::pair<GameObject*, UpdateLayer>>* pend;
		if (m_isUsePendFlag)	pend = &m_pending1;	//for�ŉ񂵂ĂȂ�����I��
		else					pend = &m_pending2;

		pend->push_back(std::make_pair(obj, layer));
		return obj;
	}

	//�ŏ��Ɍ������I�u�W�F�N�g�̂ݕԂ��܂�
	template<class T>
	T* GetGameObject()
	{
		for (size_t i = 0; i < UpdateLayer::MAX; i++)
		{
			for (auto obj : m_gameobject[i])
			{
				if (typeid(*obj) == typeid(T))
				{
					return static_cast<T*>(obj);
				}
			}
		}

		//�ۗ����X�g���m�F����
		for (auto pair : m_pending1)
		{
			auto obj = pair.first;
 			if (typeid(*obj) == typeid(T))
			{
				return static_cast<T*>(obj);
			}
		}
		//�ۗ����X�g���m�F����
		for (auto pair : m_pending2)
		{
			auto obj = pair.first;
			if (typeid(*obj) == typeid(T))
			{
				return static_cast<T*>(obj);
			}
		}

		return nullptr;
	}

	//�R���e�i�ɓ���ĕԂ��܂�
	template<class T>
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> tmp;

		for (size_t i = 0; i < UpdateLayer::MAX; i++)
		{
			for (auto obj : m_gameobject[i])
			{
				if (typeid(*obj) == typeid(T))
				{
					tmp.push_back(static_cast<T*>(obj));
				}
			}
		}

		//�ۗ����X�g���m�F����
		for (auto pair : m_pending1)
		{
			auto obj = pair.first;
			if (typeid(*obj) == typeid(T))
			{
				tmp.push_back(static_cast<T*>(obj));
			}
		}
		//�ۗ����X�g���m�F����
		for (auto pair : m_pending2)
		{
			auto obj = pair.first;
			if (typeid(*obj) == typeid(T))
			{
				tmp.push_back(static_cast<T*>(obj));
			}
		}

		return tmp;
	}

	//�폜��GameObject�̃����o�֐��ōs���܂�


	//�ȉ���Game�N���X�ő���

	//�p���s��

	virtual void Uninit()	final;
	virtual void Update()	final;
	virtual void Draw()		final;

	//�����ł��ׂĂ̕`����Ǘ����܂�
	virtual DrawManager* GetDrawManager() final { return m_drawMgr; }

private:
	DrawManager* m_drawMgr;	//Drawer
	std::list<class GameObject*> m_gameobject[UpdateLayer::MAX];

	//�R���|�[�l���g����addGameObjcet�����ƃo�O��̂����
	std::vector <std::pair<class GameObject*, UpdateLayer>> m_pending1, m_pending2;
	bool m_isUsePendFlag = false;
};