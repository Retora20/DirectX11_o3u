#include "Scene_Base.h"
#include "DrawManager.h"
#include "GameObject.h"

Scene_Base::Scene_Base():m_drawMgr(new DrawManager)
{
}

Scene_Base::~Scene_Base()
{
	Uninit();
	delete m_drawMgr;
}
void Scene_Base::Uninit()
{
	//�I���������Ăяo���C���X�^���X�������ō폜���܂�
	for (size_t layer = 0; layer < UpdateLayer::MAX; layer++)
	{
		for (auto obj : m_gameobject[layer])
		{
			obj->ComponentsUnInit();
			obj->Uninit();
			delete obj;
		}
	}
}

void Scene_Base::Update()
{
	for (size_t layer = 0; layer < UpdateLayer::MAX; layer++)
	{
		for (auto obj : m_gameobject[layer]) obj->Update();
	}

	//�ۗ����̃I�u�W�F�N�g������ꍇ�͏��������čX�V
	while(!m_pending1.empty() || !m_pending2.empty())
	{
		std::vector<std::pair<GameObject*, UpdateLayer>> *pend;

		if (!m_isUsePendFlag)	pend = &m_pending1;
		else					pend = &m_pending2;


		for (auto& obj : *pend)
		{
			obj.first->Init();
		}

		for (auto& obj : *pend)
		{
			obj.first->Update();
			m_gameobject[obj.second].push_back(obj.first);
		}
		pend->clear();
		m_isUsePendFlag = !m_isUsePendFlag;	//�X�V���ɐ؂�ւ��鎖�ɂ��
	}

	//�폜
	for (size_t layer = 0; layer < UpdateLayer::MAX; layer++)
	{
		m_gameobject[layer].remove_if([](auto object) 
		{
			if (object->GetIsDestroy())
			{
				object->ComponentsUnInit();
				object->Uninit();
				delete object;
				return true;
			}
			else return false;
		});
	}
}

void Scene_Base::Draw()
{
	m_drawMgr->Draw();
}