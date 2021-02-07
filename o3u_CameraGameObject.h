#pragma once
#include "GameObject.h"
class o3u_CameraGameObject :
    public GameObject
{
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Uninit() override;

    void SetCurTime(float curtime) { m_curtime = curtime; }
private:
    float m_curtime;
};

