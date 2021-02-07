#include "MeshFieldGameObject.h"
#include "Asset.h"
#include "TextureAsset.h"
#include "SpriteDrawer.h"
#include "MeshDrawer.h"
void MeshFieldGameObject::Init()
{
	AddCompoent<FieldDrawer>()->AssignTexture("Asset\\texture\\quad.png");
	//D3DXQuaternionRotationYawPitchRoll(&m_rotation, 0, D3DXToRadian(180), 0);

	m_position.y = -5;
}

void MeshFieldGameObject::Uninit()
{
}

float MeshFieldGameObject::GetHeight(D3DXVECTOR3 Position)
{
	auto field = GetCompoent<FieldDrawer>();
	if (field)
	{
		return field->GetHeight(Position);
	}
	else
	{
		return 0.0f;
	}
}

