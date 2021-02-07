//---------------------------------------------------------
//	Scene_Base						Date	2020/7/19
//									Author	本多玲虎		
//	シーンの基底
//	Updateはレイヤー方式、Drawはソートして行います
//	継承先では基本的にコンストラクタのみの処理を書いていきます
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

	//これを継承してシーンに最初からあるゲームオブジェクトを作成します
	virtual void CreateGameObject()= 0;


	//オブジェクトを生成し保留リストに追加します
	//この時点でInit()が呼ばれないことに注意
	template<class T>
	T* AddGameObject(UpdateLayer layer = DEFAULT)
	{
		T* obj = new T;

		std::vector<std::pair<GameObject*, UpdateLayer>>* pend;
		if (m_isUsePendFlag)	pend = &m_pending1;	//forで回してない方を選択
		else					pend = &m_pending2;

		pend->push_back(std::make_pair(obj, layer));
		return obj;
	}

	//最初に見つけたオブジェクトのみ返します
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

		//保留リストも確認する
		for (auto pair : m_pending1)
		{
			auto obj = pair.first;
 			if (typeid(*obj) == typeid(T))
			{
				return static_cast<T*>(obj);
			}
		}
		//保留リストも確認する
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

	//コンテナに入れて返します
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

		//保留リストも確認する
		for (auto pair : m_pending1)
		{
			auto obj = pair.first;
			if (typeid(*obj) == typeid(T))
			{
				tmp.push_back(static_cast<T*>(obj));
			}
		}
		//保留リストも確認する
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

	//削除はGameObjectのメンバ関数で行います


	//以下はGameクラスで操作

	//継承不可

	virtual void Uninit()	final;
	virtual void Update()	final;
	virtual void Draw()		final;

	//ここですべての描画を管理します
	virtual DrawManager* GetDrawManager() final { return m_drawMgr; }

private:
	DrawManager* m_drawMgr;	//Drawer
	std::list<class GameObject*> m_gameobject[UpdateLayer::MAX];

	//コンポーネント内でaddGameObjcetされるとバグるのを回避
	std::vector <std::pair<class GameObject*, UpdateLayer>> m_pending1, m_pending2;
	bool m_isUsePendFlag = false;
};