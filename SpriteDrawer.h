#pragma once
#include "Component.h"

//“§‹“Š‰e‚Å
class SpriteDrawer : public Drawer
{
public:
	// Drawer ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
protected:
	class VPoint* m_vpoint;
};

