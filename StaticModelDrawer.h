#pragma once
#include "main.h"
#include "Component.h"
#include <string>
class StaticModelDrawer :public Drawer
{
public:
	virtual void SetModel(std::string filename);

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;


private:
	D3DXVECTOR3 m_offsetPosition, m_offsetScale;
	D3DXQUATERNION m_offseRotation;

	class StaticModel* m_model;
};

