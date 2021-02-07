#include "Rand.h"

FloatRand FloatRand::m_instance;

float FloatRand::Get()
{
	return m_instance.range(m_instance.mt);
}

FloatRand::FloatRand():mt(),range(0.0f,1.0f)
{
	std::random_device rnd;
	mt.seed(rnd());
}