#pragma once
#include "Component.h"
class LookAtCameraComponent :
    public Component
{
public:
    // Component ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override;
    virtual void UnInit() override;
    virtual void Update() override;
protected:
    GameObject* camera = nullptr;
};

