#pragma once
#include "main.h"
#include "Asset.h"
class VPoint : public IAsset
{
public:
	ID3D11Buffer* m_VertexBuffer;

	// IAsset ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void Load(std::string filename) override;
	virtual void Unload() override;
};