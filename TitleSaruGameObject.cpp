//#include "TitleSaruGameObject.h"
//#include "Time.h"
//#include "SaruDrawer.h"
//#include "StaticModel.h"
//#include "SkinMeshDrawer.h"
//#include "input.h"
//
//void TitleSaruGameObject::Init()
//{
//	//AddCompoent<StaticModelDrawer>()->SetModel("Asset\\model\\salty\\Salty.fbx");
//	 m_model = AddCompoent<SkinMeshDrawer>();
//	 m_model->SetModel(std::string("Asset\\model\\salty\\Salty.fbx"));
//	 m_model->GetModel()->LoadAnimation("Asset\\model\\salty\\Anime1.fbx","1");
//
//	m_scale *= 1.0f;
//
//	m_position.y = -0.7f;
//	m_position.z = 1;
//
//}
//
//void TitleSaruGameObject::Uninit()
//{
//}
//
//void TitleSaruGameObject::Update()
//{
//	static bool s = false;
//	if (Input::GetKeyTrigger('S'))
//	{
//		s = !s;
//
//		if (s)  m_model->animeName = "1";
//		else	m_model->animeName = "";
//	}
//
//	//D3DXQuaternionRotationAxis(&m_rotation, &D3DXVECTOR3(0, 1, 0), Time::GetTime());
//	D3DXQuaternionNormalize(&m_rotation, &m_rotation);
//	ComponentsUpdate();
//}
