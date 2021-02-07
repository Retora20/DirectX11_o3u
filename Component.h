//---------------------------------------------------------
//	Component						Date	2020/7/19
//									Author	本多玲虎		
//	コンポーネント基底クラス
//---------------------------------------------------------
#pragma once
#include "Game.h"
#include "Scene_Base.h"
#include "DrawManager.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ShaderAseet.h"
#include "TextureAsset.h"
class Component
{
public:
	Component(){}
	virtual	~Component() {}

	//Draw登録はここで行う
	virtual void Init() = 0;

	virtual void UnInit() = 0;
	virtual void Update() = 0;

	virtual GameObject* GetOwnGameObject() final			{ return m_ownGameObject; }
	virtual void SetOwnGameObject(GameObject* parent) final	{ m_ownGameObject = parent; }

private:
	GameObject* m_ownGameObject = nullptr;
};


class Drawer :public Component
{
public:
	Drawer() {}
	virtual	~Drawer() {}

	virtual void UnInit() { DrawerUnResiater(); }
	virtual void Draw() = 0;

	virtual int  GetRQ() final { return m_renderQueue; }
	virtual void SetRQ(int set) final { m_renderQueue = set; }

	virtual void AssignTexture(std::string filename) final{ m_texture = AssetsManager::Assign<TextureAsset>(filename); }

protected:
	virtual void DrawerRegister() final { Game::GetScene()->GetDrawManager()->Register(this); }
	virtual void DrawerUnResiater() final { Game::GetScene()->GetDrawManager()->Unregister(this); }
	virtual void SetShader() final;
	virtual void SetTexture() final;
	virtual void CreateAndSetWorldMatrix() final;

	VS_Asset* m_vs = nullptr;
	HS_Asset* m_hs = nullptr;
	DS_Asset* m_ds = nullptr;
	GS_Asset* m_gs = nullptr;
	PS_Asset* m_ps = nullptr;

	TextureAsset* m_texture = nullptr;

	int	m_renderQueue = 2000;
};