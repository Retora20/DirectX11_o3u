#include "Asset.h"

std::unordered_map<std::string, IAsset*> AssetsManager::m_data;

void AssetsManager::Register(std::string filename, IAsset* inPtr)
{
	auto itr = m_data.find(filename);
	assert(itr == m_data.end());		//Šù‚É‚ ‚éê‡‚ÍƒGƒ‰[

	m_data[filename] = inPtr;
}

IAsset* AssetsManager::Find(std::string filename)
{
	auto itr = m_data.find(filename);
	return (itr != m_data.end()) ? itr->second : nullptr;	//Œ©‚Â‚©‚ç‚È‚¢ê‡‚ÍNULL‚ð•Ô‚·;
}

//íœ‚·‚éÛƒƒ‚ƒŠ‚ð‚±‚±‚ÅŠJ•ú‚·‚é

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