#pragma once
#include "Component.h"

//�������e��
class SpriteDrawer : public Drawer
{
public:
	// Drawer ����Čp������܂���
	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
protected:
	class VPoint* m_vpoint;
};

