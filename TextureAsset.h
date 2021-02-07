#pragma once
#include "main.h"
#include "Asset.h"
class TextureAsset :public IAsset
{
public:
	ID3D11ShaderResourceView* m_texture;

	// IAsset ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void Load(std::string filename) override;
	virtual void Unload() override;
};