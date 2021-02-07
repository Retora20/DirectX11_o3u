#pragma once
#include "UIDrawer.h"

class Score_Drawer:public UIDrawer
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	void	SetScore(float set) { m_score = set; }
	void	AddScore(float add) { m_score += add; }

	void	SetNumScale(D3DXVECTOR2 scl) { m_scl = scl; }
	void	SetNumPos(D3DXVECTOR2 pos) { m_pos = pos; }
private:
	float m_score = 0.0f;
	TextureAsset* m_texture[10] = { nullptr };

	D3DXVECTOR2 m_scl = {100,100};
	D3DXVECTOR2 m_pos = {0,0};
};