#pragma once
#include "GameObject.h"
class UITest :
    public GameObject
{
public:
    UITest();
    // GameObject を介して継承されました
    virtual void Init() override;
    virtual void Update() override;
    virtual void Uninit() override;
};