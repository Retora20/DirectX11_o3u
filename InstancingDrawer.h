#pragma once
#include "Component.h"
class InstancingDrawer :
    public Drawer
{
public:

    // Drawer を介して継承されました
    virtual void Init() override;
    virtual void UnInit() override;
    virtual void Update() override;
    virtual void Draw() override;
protected:
    ID3D11Buffer* m_VertexBuffer;


    ID3D11Buffer* m_positionBuffer;
    ID3D11ShaderResourceView* m_positionSRV;
};

