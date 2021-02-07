#pragma once
#include <random>
class FloatRand
{
public:
	static float Get();
private:
	FloatRand();
	static FloatRand m_instance;
	std::mt19937 mt;
	std::uniform_real_distribution<float> range;
};

