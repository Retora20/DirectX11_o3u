#include "model.h"
#include "StaticModel.h"
#include "Renderer.h"
#include <filesystem>

void StaticModel::Load(std::string filename)
{

	m_scene = aiImportFile(filename.data(),
		aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded );
	assert(m_scene);
	

	//ここでバッファサイズ決定
	m_vertexBuffer.resize(m_scene->mNumMeshes);
	m_indexBuffer.resize(m_scene->mNumMeshes);


	for (unsigned int m = 0; m < m_scene->mNumMeshes; m++)	//各メッシュループ
	{
		aiMesh* mesh = m_scene->mMeshes[m];


		// 頂点バッファ生成
		{
			//VERTEX_3D* vertex = new VERTEX_3D[mesh->mNumVertices];
			std::vector<VERTEX_3D> vertex(mesh->mNumVertices);

			for (unsigned int v = 0; v < mesh->mNumVertices; v++)
			{
				vertex[v].Position = D3DXVECTOR3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);
				vertex[v].Normal = D3DXVECTOR3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z);
				vertex[v].TexCoord = D3DXVECTOR2(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y);	//複数テクスチャ
				vertex[v].Diffuse = D3DXVECTOR4(1, 1, 1, 1);
			}

			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
	//		bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = sizeof(VERTEX_3D) * mesh->mNumVertices;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
		//	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = vertex.data();

			Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer[m]);

		//	delete[]	vertex;
		}


		
		// インデックスバッファ生成
		{

			std::vector<unsigned int> index(mesh->mNumFaces * 3);
			//UINT* index = new UINT[mesh->mNumFaces * 3];

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

			//delete[] index;

		
		}

		//テクスチャ読み込み
		{
			for (unsigned int m = 0; m < m_scene->mNumMaterials; m++)
			{
				aiString path;

				if (m_scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE,0,&path) == AI_SUCCESS)
				{
					if (path.data[0]=='*')//モデル内蔵なのでFBXから読み込み
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


void StaticModel::Unload()
{
	for (size_t m = 0; m < m_scene->mNumMeshes; m++)
	{
		m_vertexBuffer[m]->Release();
		m_indexBuffer[m]->Release();
	}

	m_vertexBuffer.clear();
	m_indexBuffer.clear();

	for (auto i : m_Texture)
	{
		i.second->Release();
	}

	aiReleaseImport(m_scene);

}

void StaticModel::Draw()
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

		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1,
			&m_vertexBuffer[i], &stride, &offset);

		Renderer::GetDeviceContext()->IASetIndexBuffer(m_indexBuffer[i], DXGI_FORMAT_R32_UINT, 0);

		Renderer::GetDeviceContext()->DrawIndexed(mesh->mNumFaces * 3, 0, 0);

	}
}