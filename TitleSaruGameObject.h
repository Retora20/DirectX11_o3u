#include "GameObject.h"
#pragma once
class TitleSaruGameObject :public GameObject
{
public:
	// GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;

private:
	class SkinMeshDrawer* m_model;
};

