#pragma once
#include "Component.h"
#include "MapAsset.h"
#include "SliderDrawer.h"
class CircleDrawer: public NoteDrawer
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
};