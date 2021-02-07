#include "ElementLogo.h"
#include "TitleLogoDrawer.h"
void ElementLogo::Init()
{
	AddCompoent<TitleLogoDrawer>()->AssignTexture("Asset/texture/element.png");

	m_scale *= 400;
	m_scale.y *= 0.4;
	m_position.x = 350;
	m_position.y = 100;
}

void ElementLogo::Uninit()
{
}
