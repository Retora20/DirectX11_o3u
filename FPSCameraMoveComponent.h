#pragma once
#include "main.h"
#include "Component.h"
#include "Game.h"
#include "input.h"
class FPSCameraMoveComponent :public Component
{
public:

	// Component ‚ð‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void Init() override { Input::SetMousePos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); }
	virtual void Update() override
	{
		static bool s = true;
		if (Input::GetKeyTrigger(VK_RBUTTON))	s = !s;
		if (!s)	return;

		//rotate
		POINT mousepos = Input::GetMousePos();
		Input::SetMousePos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

		m_euler.y += -(mousepos.x - SCREEN_WIDTH / 2) * speed;
		m_euler.x += -(mousepos.y - SCREEN_HEIGHT / 2) * speed;

		m_euler.x = std::min(std::max(m_euler.x, -1.0f), 1.5f);


		D3DXQUATERNION q;
		D3DXQuaternionRotationYawPitchRoll(&q, m_euler.y, m_euler.x, m_euler.z);
		D3DXQuaternionNormalize(&q, &q);
		GetOwnGameObject()->SetRotation(q);

	}

	void SetTarget(GameObject* target) { m_target = target; }


	virtual void UnInit() override {}
protected:
	GameObject* m_target = nullptr;
	static constexpr float speed = -0.002f;
	D3DXVECTOR3 m_euler = { 0, -0.8f, 0 };
};

