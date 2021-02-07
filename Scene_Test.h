#pragma once
#include "Scene_Base.h"
#include "CameraGameObject.h"
#include "TitleSaruGameObject.h"
#include "UITest.h"
#include "MeshFieldGameObject.h"
#include "GrassGameObject.h"
class Scene_Test : public Scene_Base
{
public:
	// Scene_Base ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void CreateGameObject() override
	{

		//ÉJÉÅÉâ
		auto camera = AddGameObject<CameraGameObject>(UpdateLayer::LAST);
		camera->SetPosition(D3DXVECTOR3(0, 0, -2));
		//AddGameObject<MeshFieldGameObject>();

		AddGameObject<GrassGameObject>();
		//AddGameObject<CameraGameObject>(UpdateLayer::LAST);
		//auto obj = AddGameObject<TitleSaruGameObject>();
		//obj->SetScale(D3DXVECTOR3(0.02, 0.02, 0.02));


		//AddGameObject<TitleBGGameObject>();

	}
};