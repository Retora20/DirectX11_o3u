#pragma once
#include "Component.h"
#include "ShaderAseet.h"
#include "MapAsset.h"
class LineDrawer:public Drawer
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	void SetCP(Shader_CP& set) {cp = set;}
	Shader_CP* GetCP() { return &cp; }
	void Setcolor(D3DXCOLOR color) { m_color = color; }
	//void SetObjectData(const MAP_OBJECT& set) { m_data = set; }
protected:
	class VPosition* m_vposition;
	Shader_CP cp{};
	D3DXCOLOR m_color = D3DXCOLOR(1,1,1,1);
};
