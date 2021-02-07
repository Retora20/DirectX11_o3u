//---------------------------------------------------------
//	DrawManager						Date	2020/8/5
//									Author	本多玲虎		
//	Drawするものをソートして管理します
//---------------------------------------------------------
#pragma once
#include <list>

namespace RQ
{
	constexpr int Default		=   -1;
	constexpr int First			=  100;
	constexpr int BackGround	= 1000;
	constexpr int Opaque		= 2000;
	constexpr int AlphaTest		= 3000;
	constexpr int Transparent	= 4000;
	constexpr int Overlay		= 5000;
}

class DrawManager
{
public:

	void Register(class Drawer* in);

	void Unregister();
	void Unregister(class Drawer* in);

	void Draw();

private:
	 std::list<class Drawer*> m_drawlist;
};