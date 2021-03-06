#pragma once
#include "main.h"
#include "Asset.h"
class TextureAsset :public IAsset
{
public:
	ID3D11ShaderResourceView* m_texture;

	// IAsset を介して継承されました
	virtual void Load(std::string filename) override;
	virtual void Unload() override;
};