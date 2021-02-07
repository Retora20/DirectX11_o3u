#pragma once
#include "StaticModelDrawer.h"
class SaruDrawer : public StaticModelDrawer
{
	virtual void Init() override
	{
		DrawerRegister();

		m_vs = AssetsManager::Assign<VS_Asset>(std::string("VSSample.cso"));
		m_ps = AssetsManager::Assign<PS_Asset>(std::string("PSGaming.cso"));
	}
};