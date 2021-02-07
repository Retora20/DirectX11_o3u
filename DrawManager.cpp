#include <algorithm>
#include "Component.h"
#include "DrawManager.h"

void DrawManager::Register(Drawer* in)
{
	if (m_drawlist.empty())
	{
		m_drawlist.emplace_front(in);
	}
	else
	{
		//ここでは常にソート済みコンテナとして挿入します
		auto it = std::lower_bound(m_drawlist.begin(), m_drawlist.end(), in,
			[](Drawer* a, Drawer* b) {return a->GetRQ() < b->GetRQ(); });
		m_drawlist.emplace(it, in);
	}
}

void DrawManager::Unregister()
{
	m_drawlist.clear();
}

void DrawManager::Unregister(Drawer* in)
{
	m_drawlist.remove(in);
}

void DrawManager::Draw()
{
	for (const auto p : m_drawlist)	p->Draw();
}