#pragma once
#include "GameObject.h"
class CameraGameObject :public GameObject
{
public:
	CameraGameObject();

	// GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
};