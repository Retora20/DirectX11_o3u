#pragma once
#include "Scene_Base.h"
#include "MapEditor_GameObject.h"
class Scene_Edit_o3u : public Scene_Base
{
public:
	virtual void CreateGameObject() override
	{
		AddGameObject<MapEditor_GameObject>();
		//ÉJÉÅÉâ
		auto camera = AddGameObject<o3u_CameraGameObject>(UpdateLayer::LAST);
		//AddGameObject<line_GameObject>();
		AddGameObject<MeshFieldGameObject>()->SetScale({ 0.7,0.7,0.7 });
	}
};