#include "FieldGameObject.h"
#include "Asset.h"
#include "TextureAsset.h"
#include "SpriteDrawer.h"
void FieldGameObject::Init()
{
	AddCompoent<SpriteDrawer>()->AssignTexture("Asset\\texture\\grass.jpg");
	D3DXQuaternionRotationYawPitchRoll(&m_rotation, 0, D3DXToRadian(90), 0);
}

void FieldGameObject::Uninit()
{
}
