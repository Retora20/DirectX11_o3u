#pragma once
#include "Asset.h"

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"

#pragma comment(lib,"assimp.lib")

#include <vector>
#include <unordered_map>
#include <string>
#include <array>

class StaticModel :
	public IAsset
{
public:
	// IAsset ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void Load(std::string filename) override;
	virtual void Unload() override;
	virtual void Draw();

private:
	const aiScene* m_scene = nullptr;

	std::vector<ID3D11Buffer*> m_vertexBuffer;
	std::vector<ID3D11Buffer*> m_indexBuffer;

	std::unordered_map < std::string, ID3D11ShaderResourceView* > m_Texture;

};

