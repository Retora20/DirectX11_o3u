#pragma once
#include "main.h"
#include "Asset.h"
class VPoint : public IAsset
{
public:
	ID3D11Buffer* m_VertexBuffer;

	// IAsset を介して継承されました
	virtual void Load(std::string filename) override;
	virtual void Unload() override;
};