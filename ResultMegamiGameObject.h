#pragma once
#include "GameObject.h"
class ResultMegamiGameObject :
    public GameObject
{
public:

    // GameObject ����Čp������܂���
    virtual void Init() override;
    virtual void Uninit() override;
};

