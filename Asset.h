//---------------------------------------------------------
//	Asset							Date	2020/7/19
//									Author	本多玲虎		
//	AssetのIFとそれを格納管理するAssetManager
//---------------------------------------------------------
#pragma once
#include <unordered_map>
#include <string>
#include "main.h"

//全てのアセットコンテナはこれを継承して作る
class IAsset
{
public:
	//Assign関数を通じて呼び出されます
	virtual void Load(std::string filename) = 0;

	//これはAssetManagerを通じて呼び出されます
	//自分で呼び出さないでください
	virtual void Unload() = 0;
};

//アセットのポインタを格納し管理
class AssetsManager
{
public:
	AssetsManager(){}
	~AssetsManager() { Unload(); }

	//AssetsManagerに問い合わせてないあったら返す、ない場合はファイルから読み込みます
	template<class T>
	static T* Assign(std::string filename) 
	{
		IAsset* asset = AssetsManager::Find(filename);

		if (!asset)
		{
			asset = new T;
			asset->Load(filename);
			Register(filename, asset);
		}
		return static_cast<T*>(asset);
	}

	//登録されたアセットを全て開放します
	static void Unload();

	//指定したアセットを開放します
	static void Unload(std::string filename);

private:
	//ポインタを返します、ない場合はnullを返します
	static IAsset* Find(std::string filename);

	//ポインタを登録、既にある場合はassertを出します
	static void Register(std::string filename, IAsset* inPtr);

	static std::unordered_map<std::string, IAsset*> m_data;
};