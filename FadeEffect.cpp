#include "FadeEffect.h"
#include "TransitionDrawer.h"
#include "Renderer.h"
#include "Time.h"
void FadeEffectGameObject::Init()
{
	AddCompoent<TransitionDrawer>();

	m_scale.x = SCREEN_WIDTH;
	m_scale.y = SCREEN_HEIGHT;
}

void FadeEffectGameObject::Uninit()
{

}

void FadeEffectGameObject::Update()
{
	ComponentsUpdate();

	Renderer::m_shaderVariable._1 = lerp(m_start, m_end, m_time);

	m_time += Time::GetDeltaTime() / m_speed;

	if (m_time > 1.0f && m_isDeleat) 
		Destroy();
}