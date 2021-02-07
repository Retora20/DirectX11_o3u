#pragma once
#include "Component.h"
class LookAtTargetConponent :
    public Component
{
public:

    // Component ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override;
    virtual void UnInit() override;
    virtual void Update() override;

    void SetTarget(GameObject* target);
protected:
    GameObject* m_target = nullptr;
};

