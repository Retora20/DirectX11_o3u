#pragma once
#include "GameObject.h"
class FadeEffectGameObject :public GameObject
{
public:
	// GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;

	float m_start = 0.0f;
	float m_end = 1.0f;
	float m_speed = 1.0f;
	bool  m_isDeleat = false;

private:
	float m_time = 0.0f;
};