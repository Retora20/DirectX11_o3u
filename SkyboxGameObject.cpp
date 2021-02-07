#include "SkyboxGameObject.h"
#include "StaticModelDrawer.h"
void SkyboxGameObject::Init()
{
	AddCompoent<StaticModelDrawer>()->SetModel("Asset\\model\\skybox\\skybox.obj");
	m_scale *= 100;
	//D3DXQuaternionRotationYawPitchRoll(&m_rotation, 0, 1, 0);
}

void SkyboxGameObject::Uninit()
{ 
}
