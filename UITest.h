#pragma once
#include "GameObject.h"
class UITest :
    public GameObject
{
public:
    UITest();
    // GameObject ����Čp������܂���
    virtual void Init() override;
    virtual void Update() override;
    virtual void Uninit() override;
};