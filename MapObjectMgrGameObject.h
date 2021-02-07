#pragma once
#include "GameObject.h"
class MapObjectMgrGameObject :
    public GameObject
{
public:
    virtual void Init() override;
    virtual void Uninit() override;
};

