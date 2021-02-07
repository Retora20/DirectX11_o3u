#pragma once
#include "Scene_Base.h"
#include "Title_o3u_Camera_GameObject.h"
#include "line_GameObject.h"
#include "TitleLogo_o3u_GameObject.h"
#include "ElementLogo.h"
#include "EnterNextScene.h"
#include "Scene_Play_o3u.h"
#include "Scene_Edit_o3u.h"

class Scene_Title_o3u : public Scene_Base
{
public:
	// Scene_Base ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void CreateGameObject() override
	{
		//ÉJÉÅÉâ
		auto camera = AddGameObject<Title_o3u_Camera_GameObject>(UpdateLayer::LAST);
		camera->SetPosition(D3DXVECTOR3(4, 0, -15));

		AddGameObject<TitleLine_GameObject>();
		AddGameObject<TitleLogo_o3u_GameObject>();
	//	AddGameObject<ElementLogo>();
		AddGameObject<EnterNextScene<Scene_Play_o3u>>()->GetKey() = {VK_RETURN,VK_LBUTTON};
		AddGameObject<EnterNextScene<Scene_Edit_o3u>>()->GetKey() = { 'E' };


	}
};
