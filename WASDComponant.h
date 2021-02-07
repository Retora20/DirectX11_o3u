#pragma once
#include "Component.h"
#include "input.h"
#include "Game.h"
#include "CameraGameObject.h"
#include "Time.h"
class WASDComponant :public Component
{
public:
	// Component ‚ð‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void Init() override { camera = Game::GetScene()->GetGameObject<CameraGameObject>(); };
	virtual void UnInit() override {};
	virtual void Update() override
	{
		if (!camera) return;


		//“ü—Í‚ðƒxƒNƒgƒ‹‚É‰ÁŽZ•³‹K‰»
		D3DXVECTOR3 inputVec = { 0,0,0 };
		if (Input::GetKeyPress('A'))	inputVec.x -= 1.0f;
		if (Input::GetKeyPress('D'))	inputVec.x += 1.0f;
		if (Input::GetKeyPress('W'))	inputVec.z += 1.0f;
		if (Input::GetKeyPress('S'))	inputVec.z -= 1.0f;
		if (Input::GetKeyPress('E'))	inputVec.y += 1.0f;
		if (Input::GetKeyPress('Q'))	inputVec.y -= 1.0f;
		D3DXVec3Normalize(&inputVec, &inputVec);

		D3DXMATRIX camMtx;
		D3DXMatrixRotationQuaternion(&camMtx, &camera->GetRotation());
		D3DXVec3TransformNormal(&inputVec, &inputVec, &camMtx);
		//inputVec.y = 0;
		D3DXVec3Normalize(&inputVec, &inputVec);

		GameObject* obj = GetOwnGameObject();
		obj->SetPosition(obj->GetPosition() + inputVec * Time::GetDeltaTime() * 5.0f);

	}
protected:
	GameObject* camera;
};

