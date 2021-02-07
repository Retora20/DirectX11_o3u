#include "SkinAnimationModel.h"

#include "model.h"

#include "Renderer.h"
#include <filesystem>

void SkinAnimationModel::Load(std::string filename)
{
	m_scene = aiImportFile(filename.data(),
		aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded);
	assert(m_scene);


	//ここでバッファサイズ決定
	m_vertexBuffer.resize(m_scene->mNumMeshes);
	m_indexBuffer.resize(m_scene->mNumMeshes);

	CreateBone(m_scene->mRootNode);


	for (unsigned int m = 0; m < m_scene->mNumMeshes; m++)	//各メッシュループ
	{
		aiMesh* mesh = m_scene->mMeshes[m];


		// 頂点バッファ生成
		{
			std::vector<VERTEX_SKIN3D> vertex(mesh->mNumVertices);

			for (unsigned int v = 0; v < mesh->mNumVertices; v++)
			{
				vertex[v].Position = D3DXVECTOR3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);
				vertex[v].Normal = D3DXVECTOR3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z);
				vertex[v].Diffuse = D3DXVECTOR4(1, 1, 1, 1);
				vertex[v].TexCoord = D3DXVECTOR2(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y);	//複数テクスチャ

				for (size_t i = 0; i < 4; i++)	//ウエイト初期化
				{
					vertex[v].BoneIndex[i] = 0;
					vertex[v].BoneWeight[i] = 0.0f;
				}
			}

			//ボーンデータ初期化とウェイト情報を
			std::vector<UINT> bonenum(mesh->mNumVertices, 0);
			for (size_t b = 0; b < mesh->mNumBones; b++)
			{
				aiBone* bone = mesh->mBones[b];

				m_Bone[bone->mName.C_Str()].OffsetMatrix = bone->mOffsetMatrix;
				m_Bone[bone->mName.C_Str()].Index = b;

				for (size_t w = 0; w < bone->mNumWeights; w++)
				{
					aiVertexWeight weight = bone->mWeights[w];

					UINT num = bonenum[weight.mVertexId];

					vertex[weight.mVertexId].BoneWeight[num] = weight.mWeight;
					vertex[weight.mVertexId].BoneIndex[num] = b;

					bonenum[weight.mVertexId]++;

					assert(bonenum[weight.mVertexId] <= 4);
				}
			}


			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(VERTEX_SKIN3D) * mesh->mNumVertices;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = vertex.data();

			Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer[m]);
		}

		// インデックスバッファ生成
		{
			std::vector<unsigned int> index(mesh->mNumFaces * 3);

			for (size_t f = 0; f < mesh->mNumFaces; f++)
			{
				const aiFace* face = &mesh->mFaces[f];

				assert(face->mNumIndices == 3);

				index[f * 3 + 0] = face->mIndices[0];
				index[f * 3 + 1] = face->mIndices[1];
				index[f * 3 + 2] = face->mIndices[2];
			}

			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(unsigned int) * mesh->mNumFaces * 3;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = index.data();

			Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_indexBuffer[m]);
		}

		//テクスチャ読み込み
		{
			for (unsigned int m = 0; m < m_scene->mNumMaterials; m++)
			{
				aiString path;

				if (m_scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
				{
					if (path.data[0] == '*')//モデル内蔵なのでFBXから読み込み
					{
						if (m_Texture[path.data] == NULL)
						{
							ID3D11ShaderResourceView* texture;
							int id = atoi(&path.data[1]);

							D3DX11CreateShaderResourceViewFromMemory(
								Renderer::GetDevice(),
								(const unsigned char*)m_scene->mTextures[id]->pcData,	//これが実際のデータ
								m_scene->mTextures[id]->mWidth,
								NULL,
								NULL,
								&texture,
								NULL);

							m_Texture[path.data] = texture;
						}
					}
					else
					{
						std::filesystem::path tmp = filename;
						tmp.remove_filename();
						tmp += path.C_Str();

						ID3D11ShaderResourceView* texture;
						D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
							tmp.string().c_str(),
							NULL,
							NULL,
							&texture,
							NULL);
						m_Texture[path.data] = texture;
					}
				}
				else
				{
					m_Texture[path.data] = NULL;
				}
			}
		}
	}
}

void SkinAnimationModel::LoadAnimation(std::string filename, std::string animationname)
{
	m_Animation[animationname] = aiImportFile(filename.c_str(), aiProcess_ConvertToLeftHanded);
	assert(m_Animation[animationname]);
}

void SkinAnimationModel::Unload()
{
}

void SkinAnimationModel::Update(int Frame, std::string animationname )
{
	if (!m_scene->HasAnimations())	return;

	const aiScene* scene = m_Animation[animationname];
	if (!scene)	scene = m_scene;

	aiAnimation* animation = scene->mAnimations[0];


	for (unsigned int c = 0; c < animation->mNumChannels; c++)
	{
		aiNodeAnim* nodeanim = animation->mChannels[c];
		BONE_ID* bone = &m_Bone[nodeanim->mNodeName.C_Str()];

		int f;
		f = Frame % nodeanim->mNumRotationKeys;
		aiQuaternion rot = nodeanim->mRotationKeys[f].mValue;

		f = Frame % nodeanim->mNumPositionKeys;
		aiVector3D pos = nodeanim->mPositionKeys[f].mValue;

		bone->AnimationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot, pos);
	}

	//再帰的にボーンマトリクスを更新
	UpdateBoneMatrix(m_scene->mRootNode, aiMatrix4x4());

	Renderer::UpdateBoneMatrix(&m_bone_buffer);

}

void SkinAnimationModel::Draw()
{
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	MATERIAL mat;
	ZeroMemory(&mat, sizeof(MATERIAL));

	mat.Diffuse = D3DXCOLOR(1, 1, 1, 1);
	mat.Ambient = D3DXCOLOR(1, 1, 1, 1);

	for (unsigned int i = 0; i < m_scene->mNumMeshes; i++)
	{
		aiMesh* mesh = m_scene->mMeshes[i];

		aiMaterial* mat = m_scene->mMaterials[mesh->mMaterialIndex];

		aiString path;
		mat->GetTexture(aiTextureType_DIFFUSE, 0, &path);
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[path.data]);

		UINT stride = sizeof(VERTEX_SKIN3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1,
			&m_vertexBuffer[i], &stride, &offset);

		Renderer::GetDeviceContext()->IASetIndexBuffer(m_indexBuffer[i], DXGI_FORMAT_R32_UINT, 0);

		Renderer::GetDeviceContext()->DrawIndexed(mesh->mNumFaces * 3, 0, 0);

	}
}

void SkinAnimationModel::Assgin(std::string filename)
{

}

void SkinAnimationModel::CreateBone(aiNode* node)
{
	BONE_ID bone;

	m_Bone[node->mName.C_Str()] = bone;

	for (unsigned i = 0; i < node->mNumChildren; i++)
	{
		CreateBone(node->mChildren[i]);
	}
}

void SkinAnimationModel::UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix)
{
	if (m_Bone.find(node->mName.C_Str()) != m_Bone.end())
	{
		BONE_ID* bone = &m_Bone[node->mName.C_Str()];


		//asiimpの行列は逆
		aiMatrix4x4 world;


		world = matrix;
		world *= bone->AnimationMatrix;

		bone->Matrix = world;
		bone->Matrix *= bone->OffsetMatrix;

		//constantBuffer書き換え
		if (bone->Index != -1)
		{
			m_bone_buffer.BoneMatrix[bone->Index] = ConvertMatrix(bone->Matrix);
		}


		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			UpdateBoneMatrix(node->mChildren[i], world);
		}
	}
	else
	{
		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			UpdateBoneMatrix(node->mChildren[i], matrix);
		}
	}
}

D3DXMATRIX ConvertMatrix(const aiMatrix4x4& aimtx)
{
	D3DXMATRIX d;
	aiMatrix4x4 a = aimtx;

	d._11 = a.a1;
	d._12 = a.a2;
	d._13 = a.a3;
	d._14 = a.a4;

	d._21 = a.b1;
	d._22 = a.b2;
	d._23 = a.b3;
	d._24 = a.b4;

	d._31 = a.c1;
	d._32 = a.c2;
	d._33 = a.c3;
	d._34 = a.c4;

	d._41 = a.d1;
	d._42 = a.d2;
	d._43 = a.d3;
	d._44 = a.d4;

	return d;
}
