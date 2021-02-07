#pragma once
#include "main.h"
#include "Component.h"
class UIDrawer : public Drawer
{
public:
    UIDrawer() { m_renderQueue = RQ::Overlay; }
    virtual ~UIDrawer() {}

    // Component ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override;
    virtual void Update() override;
    virtual void Draw() override;

    class VPoint* m_Vertexpoint;
};