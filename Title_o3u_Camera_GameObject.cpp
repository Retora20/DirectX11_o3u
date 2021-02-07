#include "Title_o3u_Camera_GameObject.h"
#include "CameraComponent.h"
void Title_o3u_Camera_GameObject::Init()
{
	AddCompoent<CameraComponent>();
}

void Title_o3u_Camera_GameObject::Uninit()
{
}
