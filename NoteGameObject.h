#pragma once
#include "GameObject.h"
class NoteGameObject:public GameObject
{
public:
	virtual void Init() override;
	virtual void Uninit() override;
};