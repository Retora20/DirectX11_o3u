#pragma once
#include "GameObject.h"
#include "input.h"
#include "Game.h"
#include "TransitionDrawer.h"
#include "FadeEffect.h"
#include <vector>
template<class NextScene>
class EnterNextScene : public GameObject
{
public:

    // GameObject を介して継承されました
    virtual void    Init() override  {}
    virtual void    Uninit() override {}

    std::vector<BYTE>& GetKey() { return m_keys; }

    virtual void Update() override
    {
        if (m_once)
        {
            m_time += Time::GetDeltaTime();
            if (m_time > m_fadetime)
            {
                Game::NextScene<NextScene>();
                Destroy();
            }
        }
        if (CheckKey())
        {
            Fade();
        }
        ComponentsUpdate();
    }

    //手動実行
    void Fade()
    {
        if (m_once) return;

        m_once = true;
        auto obj = Game::GetScene()->AddGameObject<FadeEffectGameObject>();

        obj->m_start = 1.0f;
        obj->m_end = 0.0f;
        obj->m_speed = m_fadetime;
    }


private:
    bool CheckKey()
    {
        for (BYTE key : m_keys) 
        {
            if (Input::GetKeyTrigger(key)) return true;
        }
        return false;
    }

    std::vector<BYTE> m_keys;

    //タイマー
    float m_fadetime = 2.0f;
    float m_time = 0.0f;
    bool m_once = false;

};