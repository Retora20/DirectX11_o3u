#pragma once
#include "GameObject.h"

class MeshFieldGameObject :public GameObject
{
public:
	// GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½

	virtual void Init() override;
	virtual void Uninit() override;
	virtual float GetHeight(D3DXVECTOR3 Position);
};

