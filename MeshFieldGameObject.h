#pragma once
#include "GameObject.h"

class MeshFieldGameObject :public GameObject
{
public:
	// GameObject を介して継承されました

	virtual void Init() override;
	virtual void Uninit() override;
	virtual float GetHeight(D3DXVECTOR3 Position);
};

