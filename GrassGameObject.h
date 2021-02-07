#pragma once
#include "GameObject.h"
class GrassGameObject:public GameObject
{
public:

	// GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void Init() override;
	virtual void Uninit() override;
};

