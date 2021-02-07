#pragma once
#include "Component.h"
//#include "main.h"
class FieldDrawer :
	public Drawer
{
public:
	// Drawer ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	virtual float GetHeight(D3DXVECTOR3 position);
protected:
	//class VPoint* m_vpoint;
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;

	VERTEX_3D m_vertex[21][21];
};

