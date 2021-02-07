#include "MapObjectMgrGameObject.h"
#include "MapObjectManager.h"
#include "Score_Drawer.h"
void MapObjectMgrGameObject::Init()
{
	AddCompoent<MapObjectManager_Component>();
	auto score = AddCompoent<Score_Drawer>();
	score->SetNumScale({ 49.0f,54.0f });
	score->SetNumPos({ SCREEN_WIDTH / 2 - 49.0f / 2.0f ,SCREEN_HEIGHT / 2 - 54.0f / 2.0f });
}

void MapObjectMgrGameObject::Uninit()
{
}
