#pragma once
#include "GameObject.h"
class CameraGameObject :public GameObject
{
public:
	CameraGameObject();

	// GameObject ����Čp������܂���
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};