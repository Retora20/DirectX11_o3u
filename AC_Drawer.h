#include "SliderDrawer.h"
#pragma once
class AC_Drawer:public NoteDrawer
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	void	SetScale(float set) { m_scale = set; }
	void	SetPos(const D3DXVECTOR3& set) { m_pos = set; }
protected:
	float m_scale;
	D3DXVECTOR3 m_pos;
};