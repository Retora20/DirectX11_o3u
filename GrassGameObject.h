#pragma once
#include "GameObject.h"
class GrassGameObject:public GameObject
{
public:

	// GameObject を介して継承されました
	virtual void Init() override;
	virtual void Uninit() override;
};

