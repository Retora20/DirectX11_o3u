#pragma once
#include "GameObject.h"
class CameraGameObject :public GameObject
{
public:
	CameraGameObject();

	// GameObject を介して継承されました
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};