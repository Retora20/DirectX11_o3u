#pragma once
#include "GameObject.h"
class GrassGameObject:public GameObject
{
public:

	// GameObject ����Čp������܂���
	virtual void Init() override;
	virtual void Uninit() override;
};

