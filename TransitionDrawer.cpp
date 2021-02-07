#include "TransitionDrawer.h"
#include "VPoint.h"
#include "TextureAsset.h"
void TransitionDrawer::Init()
{
	m_Vertexpoint = AssetsManager::Assign<VPoint>(std::string("VPoint"));

	m_texture = AssetsManager::Assign<TextureAsset>(std::string("Asset/texture/rule.png"));

	m_vs = AssetsManager::Assign<VS_Asset>(std::string("VSNop.cso"));
	m_gs = AssetsManager::Assign<GS_Asset>(std::string("GSQuad.cso"));
	m_ps = AssetsManager::Assign<PS_Asset>(std::string("PSTransition.cso"));

	SetRQ(RQ::Overlay);
	DrawerRegister();
}