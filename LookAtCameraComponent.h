#pragma once
#include "Component.h"
class LookAtCameraComponent :
    public Component
{
public:
    // Component を介して継承されました
    virtual void Init() override;
    virtual void UnInit() override;
    virtual void Update() override;
protected:
    GameObject* camera = nullptr;
};

