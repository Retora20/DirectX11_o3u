#pragma once
#include "GameObject.h"
#include <vector>
class TitleLine_GameObject :public GameObject
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Uninit() override;

private:
	std::vector<class LineDrawer*> m_Lines;
};