#include "GameObject.h"
#pragma once
class TitleSaruGameObject :public GameObject
{
public:
	// GameObject ����Čp������܂���
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;

private:
	class SkinMeshDrawer* m_model;
};

