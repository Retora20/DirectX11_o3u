#include "Time.h"

float Time::m_time;
float Time::m_deltaTime;
float Time::m_timeScale;
std::chrono::high_resolution_clock::time_point Time::m_start;
std::chrono::high_resolution_clock::time_point Time::m_last;

float Time::GetTime()
{
	return m_time;
}

float Time::GetDeltaTime(bool unScaled)
{
	return (unScaled)? m_deltaTime : m_deltaTime * m_timeScale;
}

float Time::GetRawDeltaTime()
{
	auto cur = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(cur - m_last).count() / 1000000000.0f;
}

void Time::SetTimeScale(float scale)
{
	m_timeScale = scale;
}

float Time::GetRawTime()
{
	auto cur = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(cur - m_start).count() / 1000000000.0f;
}

void Time::Init()
{
	m_start = m_last = std::chrono::high_resolution_clock::now();
	m_time = m_deltaTime = 0.0f;
	m_timeScale = 1.0f;
}

void Time::Update()
{
	auto cur = std::chrono::high_resolution_clock::now();

	m_time		= std::chrono::duration_cast<std::chrono::nanoseconds>(cur - m_start).count() / 1000000000.0f;
	m_deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(cur - m_last).count() / 1000000000.0f;

	m_deltaTime = fminf(m_deltaTime, m_MaxDeltaTime);

	m_last = cur;
}
