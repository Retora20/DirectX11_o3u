#pragma once
#include "StaticModel.h"
#include "Renderer.h"

struct VERTEX_SKIN3D
{
    D3DXVECTOR3 Position;
    D3DXVECTOR3 Normal;
    D3DXVECTOR4 Diffuse;
    D3DXVECTOR2 TexCoord;
    UINT        BoneIndex[4];
    float       BoneWeight[4];
};

struct BONE_ID
{
	aiMatrix4x4 Matrix;
	aiMatrix4x4 AnimationMatrix;
	aiMatrix4x4 OffsetMatrix;
	UINT		Index = -1;
};


class SkinAnimationModel :public IAsset
{
public:
	// IAsset ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
	virtual void Load(std::string filename) override;
	virtual void LoadAnimation(std::string filename, std::string animationname);
	virtual void Unload() override;
	virtual void Update(int Frame, std::string animationname = "");
	virtual void Draw();
	virtual void Assgin(std::string filename);

private:
	void CreateBone(aiNode* node);
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);


	const aiScene* m_scene = nullptr;
	std::unordered_map < std::string, const aiScene* > m_Animation;


	std::vector<ID3D11Buffer*> m_vertexBuffer;
	std::vector<ID3D11Buffer*> m_indexBuffer;

	std::unordered_map < std::string, ID3D11ShaderResourceView* > m_Texture;

	std::unordered_map<std::string, BONE_ID>			m_Bone;

	BONE_BUFFER m_bone_buffer;
};

D3DXMATRIX ConvertMatrix(const aiMatrix4x4& aimtx);