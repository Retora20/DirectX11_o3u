#pragma once
#include"main.h"
#include "Asset.h"
class VS_Asset :public IAsset
{
public:
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	virtual void Unload() override { m_vs->Release(); }
	virtual void Load(std::string filename) override;
};

class VSSKIN_Asset :public VS_Asset
{
public:
	virtual void Load(std::string filename) override;
};

class VSPosition_Asset :public VS_Asset
{
public:
	virtual void Load(std::string filename) override;
};
class HS_Asset :public IAsset
{
public:
	ID3D11HullShader* m_hs = nullptr;
	virtual void Unload() override { m_hs->Release(); }
	virtual void Load(std::string filename) override;
};

class DS_Asset :public IAsset
{
public:
	ID3D11DomainShader* m_ds = nullptr;
	virtual void Unload() override { m_ds->Release(); }
	virtual void Load(std::string filename) override;
};

class GS_Asset :public IAsset
{
public:
	ID3D11GeometryShader* m_gs = nullptr;
	virtual void Unload() override { m_gs->Release(); }
	virtual void Load(std::string filename) override;
};

class PS_Asset : public IAsset
{
public:
	ID3D11PixelShader* m_ps = nullptr;
	virtual void Unload() override { m_ps->Release(); }
	virtual void Load(std::string filename) override;
};