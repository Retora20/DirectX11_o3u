#pragma once
#include "GameObject.h"
class TitleLogo_o3u_GameObject :
    public GameObject
{
public:


    // GameObject を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

};

