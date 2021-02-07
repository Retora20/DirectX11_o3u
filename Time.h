//---------------------------------------------------------
//	Time							Date	2020/7/18
//									Author	本多玲虎		
//	Unity参考
//---------------------------------------------------------
#pragma once
#include <chrono>
class Time
{
public:

	//ゲームを起動してからの時間を取得します
	//この値は同フレーム内で同じ値を返します
	static float	GetTime(/*必要になったらunScale実装*/);

	//前有効フレームからの経過時間を返します
	//unScaledをtrueにするとTimeScaleの影響を受けません
	static float	GetDeltaTime(bool unScaled = false);

	//ゲームを起動してからの時間を取得します
	//この関数が呼ばれた瞬間に計測した値を返します
	static float	GetRawTime();

	//最後にUpdate()やInit()を呼ばれてからの経過時間を返します
	//この関数が呼ばれた瞬間に計測した値を返します
	static float	GetRawDeltaTime();

	//時間の速度倍率を変更します
	static void		SetTimeScale(float scale);

	//プログラム開始時に呼び出します
	static void		Init();

	//有効フレーム時の最初に呼び出します
	static void		Update();

private:
	static constexpr float m_MaxDeltaTime = 1.0f / 10;	//最低10fps

	static float m_time, m_deltaTime;	//これを返す
	static float m_timeScale;
	static std::chrono::high_resolution_clock::time_point m_start, m_last;
};