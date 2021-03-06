#pragma once
#include "main.h"
#include "Component.h"
class UIDrawer : public Drawer
{
public:
    UIDrawer() { m_renderQueue = RQ::Overlay; }
    virtual ~UIDrawer() {}

    // Component を介して継承されました
    virtual void Init() override;
    virtual void Update() override;
    virtual void Draw() override;

    class VPoint* m_Vertexpoint;
};