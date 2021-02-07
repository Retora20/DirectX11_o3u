#pragma once
#include "StaticModelDrawer.h"
#include "SkinAnimationModel.h"
#include "Time.h"
class SkinMeshDrawer :
    public StaticModelDrawer
{
public:
    virtual void SetModel(std::string filename) override
    {
        m_skinModel = AssetsManager::Assign<SkinAnimationModel>(filename);
    }

    virtual void Init() override
    {
        DrawerRegister();

        m_vs = AssetsManager::Assign<VSSKIN_Asset>(std::string("VSSkinning.cso"));
        //m_vs = AssetsManager::Assign<VSSKIN_Asset>(std::string("VSSample.cso"));
        m_ps = AssetsManager::Assign<PS_Asset>(std::string("PSSample.cso"));
    }

    virtual void Update() override
    {
        int f = Time::GetTime() * 60;
        m_skinModel->Update(f, animeName);
    }

    virtual void Draw() override
    {
        SetShader();
        CreateAndSetWorldMatrix();

        m_skinModel->Draw();
    }

    virtual SkinAnimationModel* GetModel()
    {
        return m_skinModel;
    }

    std::string animeName = "";
private:
    SkinAnimationModel* m_skinModel;
};

