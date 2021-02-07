#pragma once
#include "Component.h"
#include "MapObjectManager.h"
class TapJudgeDrawer: public Drawer
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
private:
	class VPosition* m_vposition;
	float m_timer = 0.0f;
};