#pragma once
#include "GameObject.h"
class ElementLogo :
    public GameObject
{
public:
    virtual void Init() override;
    virtual void Uninit() override;
};

