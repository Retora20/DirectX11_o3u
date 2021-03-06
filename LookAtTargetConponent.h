#pragma once
#include "Component.h"
class LookAtTargetConponent :
    public Component
{
public:

    // Component を介して継承されました
    virtual void Init() override;
    virtual void UnInit() override;
    virtual void Update() override;

    void SetTarget(GameObject* target);
protected:
    GameObject* m_target = nullptr;
};

