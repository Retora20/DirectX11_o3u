#pragma once
#include "Component.h"
class BillboordDrawer :
    public Drawer
{
public:
    // Drawer ����Čp������܂���
    virtual void Init() override;
    virtual void Update() override;
    virtual void Draw() override;

protected:
    class VPoint* m_vpoint;
    class CameraComponent* camera;
};

