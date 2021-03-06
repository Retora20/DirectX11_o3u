#include "GameObject.h"
#pragma once
class TitleSaruGameObject :public GameObject
{
public:
	// GameObject を介して継承されました
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;

private:
	class SkinMeshDrawer* m_model;
};

