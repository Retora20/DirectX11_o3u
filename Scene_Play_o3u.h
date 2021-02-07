#pragma once
#include "Scene_Base.h"
#include "CameraGameObject.h"
#include "TitleSaruGameObject.h"
#include "UITest.h"
#include "MeshFieldGameObject.h"
#include "line_GameObject.h"
#include "MapObjectMgrGameObject.h"
#include "MeshFieldGameObject.h"
#include "o3u_CameraGameObject.h"
class Scene_Play_o3u : public Scene_Base
{
public:
	// Scene_Base ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void CreateGameObject() override
	{
		AddGameObject<MapObjectMgrGameObject>();
		//ÉJÉÅÉâ
		auto camera = AddGameObject<o3u_CameraGameObject>(UpdateLayer::LAST);


		//AddGameObject<line_GameObject>();
		AddGameObject<MeshFieldGameObject>()->SetScale({ 0.7,0.7,0.7 });

	}
};
