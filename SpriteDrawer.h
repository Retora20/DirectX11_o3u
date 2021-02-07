#pragma once
#include "Component.h"

//透視投影で
class SpriteDrawer : public Drawer
{
public:
	// Drawer を介して継承されました
	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
protected:
	class VPoint* m_vpoint;
};

