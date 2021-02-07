//---------------------------------------------------------
//	GameObject						Date	2020/7/19
//									Author	本多玲虎		
//	全てのゲームオブジェクト基底クラス
//---------------------------------------------------------
#pragma once
#include "main.h"
#include <vector>
#include <algorithm>
class GameObject
{
public:
	//追加したメンバの初期化、リソース取得、コンポーネント追加はコンストラクタで行います
	GameObject();

	//Asset以外のメモリ開放をデストラクタで行います
	virtual ~GameObject() {}

	//ここでは他のゲームオブジェクトを参照書き換えする処理を書きます
	virtual void Init() = 0;

	//ここでは他のゲームオブジェクトを参照書き換えする処理を書きます
	virtual void Uninit() = 0;

	//ここで追加したメンバを更新します
	//使いまわせる処理はコンポーネントにして
	//コンポーネントはComponentsUpdate()を呼んで更新します
	virtual void Update() { ComponentsUpdate(); }

	//描画はコンポーネントを介して描画します
	//Drawは比較的同じ処理になりがちなので必ずコンポーネントを介して描画します

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

	//コンポーネント追加(保留リストに追加）
	//この時点ではインスタンスは生成されるがコンポーネント側のInit()が呼ばれない事に注意
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
		//保留リストも参照
		for (auto comp : m_pendComponents)
		{
			if (typeid(*comp) == typeid(T))return static_cast<T*>(comp);
		}
		return nullptr;
	}

	//自身を削除します
	virtual void Destroy() final { m_IsDestroy = true; }

	//削除フラグを返します
	virtual bool GetIsDestroy() final { return m_IsDestroy; }

	virtual void ComponentsUnInit();

protected:
	//Updateをオーバーライドした際はこれを呼んでください
	virtual void ComponentsUpdate() final;

	D3DXVECTOR3		m_position;
	D3DXQUATERNION	m_rotation;
	D3DXVECTOR3		m_scale;

private:
	std::vector<class Component*> m_components, m_pendComponents;
	bool m_IsDestroy = false;
};