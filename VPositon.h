#pragma once
#include "main.h"
#include "Asset.h"
class VPosition : public IAsset
{
public:
	ID3D11Buffer* m_VertexBuffer;

	// IAsset ����Čp������܂���
	virtual void Load(std::string filename) override;
	virtual void Unload() override;
};