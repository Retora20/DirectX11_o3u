#include "UITest.h"
#include "UIDrawer.h"


UITest::UITest()
{
	AddCompoent<UIDrawer>();
}

void UITest::Init()
{
	
}

void UITest::Update()
{
	m_scale.x = SCREEN_WIDTH;
	m_scale.y = SCREEN_HEIGHT;

	ComponentsUpdate();
}

void UITest::Uninit()
{
}
