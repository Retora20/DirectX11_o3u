#pragma once
#include "GameObject.h"
class SkyboxGameObject :
    public GameObject
{
public:

    // GameObject を介して継承されました
    virtual void Init() override;
    virtual void Uninit() override;
};

