#pragma once
#include "Component.h"
#include "MapAsset.h"

class NoteDrawer :public Drawer
{
public:
	void SetObjectData(const NOTE_OBJECT& set) { m_data = set; }
	void SetEnable(bool set = true) { m_isUse = set; }
	const NOTE_OBJECT& GetData() { return m_data; }
	const void SetData(const NOTE_OBJECT& data) { m_data = data; }
	void SetJudge(Judge judge) { m_data.judge = judge; }
protected:
	class VPosition* m_vposition = nullptr;
	Shader_CP cp{};
	NOTE_OBJECT m_data{};
	bool m_isUse = false;
};


class SliderDrawer :public NoteDrawer
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
};

