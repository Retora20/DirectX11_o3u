#pragma once
#include "GameObject.h"
class UITest :
    public GameObject
{
public:
    UITest();
    // GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override;
    virtual void Update() override;
    virtual void Uninit() override;
};