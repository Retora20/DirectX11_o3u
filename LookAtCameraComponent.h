#pragma once
#include "Component.h"
class LookAtCameraComponent :
    public Component
{
public:
    // Component ����Čp������܂���
    virtual void Init() override;
    virtual void UnInit() override;
    virtual void Update() override;
protected:
    GameObject* camera = nullptr;
};

