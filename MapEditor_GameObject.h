#pragma once
#include "GameObject.h"
class MapEditor_GameObject :
    public GameObject
{
public:
    virtual void Init() override;
    virtual void Uninit() override;
};
