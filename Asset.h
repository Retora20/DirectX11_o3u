//---------------------------------------------------------
//	Asset							Date	2020/7/19
//									Author	�{�����		
//	Asset��IF�Ƃ�����i�[�Ǘ�����AssetManager
//---------------------------------------------------------
#pragma once
#include <unordered_map>
#include <string>
#include "main.h"

//�S�ẴA�Z�b�g�R���e�i�͂�����p�����č��
class IAsset
{
public:
	//Assign�֐���ʂ��ČĂяo����܂�
	virtual void Load(std::string filename) = 0;

	//�����AssetManager��ʂ��ČĂяo����܂�
	//�����ŌĂяo���Ȃ��ł�������
	virtual void Unload() = 0;
};

//�A�Z�b�g�̃|�C���^���i�[���Ǘ�
class AssetsManager
{
public:
	AssetsManager(){}
	~AssetsManager() { Unload(); }

	//AssetsManager�ɖ₢���킹�ĂȂ���������Ԃ��A�Ȃ��ꍇ�̓t�@�C������ǂݍ��݂܂�
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

	//�o�^���ꂽ�A�Z�b�g��S�ĊJ�����܂�
	static void Unload();

	//�w�肵���A�Z�b�g���J�����܂�
	static void Unload(std::string filename);

private:
	//�|�C���^��Ԃ��܂��A�Ȃ��ꍇ��null��Ԃ��܂�
	static IAsset* Find(std::string filename);

	//�|�C���^��o�^�A���ɂ���ꍇ��assert���o���܂�
	static void Register(std::string filename, IAsset* inPtr);

	static std::unordered_map<std::string, IAsset*> m_data;
};