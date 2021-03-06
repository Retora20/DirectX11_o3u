#include "Asset.h"

std::unordered_map<std::string, IAsset*> AssetsManager::m_data;

void AssetsManager::Register(std::string filename, IAsset* inPtr)
{
	auto itr = m_data.find(filename);
	assert(itr == m_data.end());		//既にある場合はエラー

	m_data[filename] = inPtr;
}

IAsset* AssetsManager::Find(std::string filename)
{
	auto itr = m_data.find(filename);
	return (itr != m_data.end()) ? itr->second : nullptr;	//見つからない場合はNULLを返す;
}

//削除する際メモリをここで開放する

void AssetsManager::Unload()
{
	for (auto& i : m_data)
	{
		i.second->Unload();
		delete i.second;
	}
	m_data.clear();	
}

void AssetsManager::Unload(std::string filename)
{
	 m_data[filename]->Unload();
	 delete m_data[filename];
	 m_data.erase(filename);
}