#include "MapEditor_GameObject.h"
#include "MapEditorManager_Component.h"
void MapEditor_GameObject::Init()
{
	AddCompoent<MapEditorManager_Component>();
}

void MapEditor_GameObject::Uninit()
{

}
