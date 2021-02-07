#include "GrassGameObject.h"
#include "InstancingDrawer.h"
void GrassGameObject::Init()
{
	AddCompoent<InstancingDrawer>();
}

void GrassGameObject::Uninit()
{
}
