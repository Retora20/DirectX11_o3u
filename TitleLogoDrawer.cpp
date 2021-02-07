#include "TitleLogoDrawer.h"

void TitleLogoDrawer::Init()
{
	UIDrawer::Init();
	m_ps = AssetsManager::Assign<PS_Asset>(std::string("PSTextureSin.cso"));
}
