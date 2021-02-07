#include "StaticModelDrawer.h"
#include "Asset.h"
#include "model.h"
#include "StaticModel.h"
#include "SkinAnimationModel.h"
#include "Time.h"

void StaticModelDrawer::SetModel(std::string filename)
{
	m_model = AssetsManager::Assign<StaticModel>(filename);
}

void StaticModelDrawer::Init()
{
	DrawerRegister();

	m_vs = AssetsManager::Assign<VS_Asset>(std::string("VSSample.cso"));
	m_ps = AssetsManager::Assign<PS_Asset>(std::string("PSSample.cso"));
}

void StaticModelDrawer::Update()
{
}

void StaticModelDrawer::Draw()
{
	SetShader();
	CreateAndSetWorldMatrix();

	m_model->Draw();
}
