#include "TitleLogo_o3u_GameObject.h"
#include "TitleLogoDrawer.h"
void TitleLogo_o3u_GameObject::Init()
{
	AddCompoent<TitleLogoDrawer>()->AssignTexture("Asset/texture/start.png");
	m_scale *= 220;
	m_scale.y *= 0.4;
	m_position.x = 350;
	m_position.y = -150;

}

void TitleLogo_o3u_GameObject::Uninit()
{
}
