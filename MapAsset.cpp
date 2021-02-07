#include "MapAsset.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Asset.h"

#define MAPOBJFILE ("/obj.txt")
#define MAPAUDIO ("/audio.wav")
#define MAPMETA ("/meta.txt")


void MapAsset::Load(std::string filename)
{
	//曲読み込み
	m_audio = AssetsManager::Assign<AudioData_Asset>(filename + MAPAUDIO);

	//メタデータ読み込み
	ReadMetaData(filename + MAPMETA);

	//譜面オブジェクト読み込み
	ReadMapObject(filename + MAPOBJFILE);
	//CreateTestMapData();
}

void MapAsset::Unload()
{
	//無し
}

void MapAsset::Save(std::string filename)
{
	SaveMapObject(filename);
}

void MapAsset::ReadMapObject(std::string filename)
{
	std::ifstream ifs(filename);
	std::string line;				//1ライン

	while (getline(ifs, line))//1ラインずつ
	{
		NOTE_OBJECT obj;
		std::vector<std::string> str;

		{//単語に分けてstrに代入
			std::stringstream ss{line};
			std::string tmp;
			while (getline(ss, tmp,','))
			{
				str.push_back(tmp);
			}
		}

		//Type判別
		if (str[0] == "C") obj.type = obj.CIRCLE;
		if (str[0] == "S") obj.type = obj.SLIDER;

		//サークル
		if (obj.type == obj.CIRCLE)
		{
			obj.StartTime = obj.EndTime = (float)std::stof(str[1]) / 1000.0f;
			str.erase(str.begin(), str.begin() + 2);
			obj.Positions = ReadPos(str);
			obj.CpNum = obj.Positions.size();
		}

		//スライダー
		if (obj.type == obj.SLIDER)
		{
			obj.StartTime = (float)std::stof(str[1]) / 1000.0f;
			obj.EndTime = (float)std::stof(str[2]) / 1000.0f;
			str.erase(str.begin(), str.begin() + 3);
			obj.Positions = ReadPos(str);
			obj.CpNum = obj.Positions.size();
		}



		m_object.emplace_back(obj);
	}

}

void MapAsset::ReadMetaData(std::string filename)
{
	std::ifstream ifs(filename);
	std::string line;				//1ライン

	getline(ifs, line);
	m_metaData.Title = line;

	getline(ifs, line);
	m_metaData.Artist = line;

	getline(ifs, line);
	m_metaData.Diffname = line;

	getline(ifs, line);
	m_metaData.BPM = std::stof(line);

	getline(ifs, line);
	m_metaData.Offset = std::stof(line) / 1000;

	getline(ifs, line);
	m_metaData.Volume = std::stof(line);

	m_metaData.BeatLength = 60.0f / m_metaData.BPM;

	m_metaData.SongFileLength = m_audio->GetLength();
}

void MapAsset::CreateTestMapData()
{
	for (size_t i = 1; i < 500; i += 4)
	{
		NOTE_OBJECT obj;
		obj.type = obj.CIRCLE;
		obj.StartTime = obj.EndTime = m_metaData.Offset + i * m_metaData.BeatLength;
		obj.Positions.emplace_back(D3DXVECTOR3(cos(i * 0.1)*10, sinf(i * 0.1f)*10, i * 0.05f));
		m_object.emplace_back(obj);
	}


}

std::vector<D3DXVECTOR3> MapAsset::ReadPos(std::vector<std::string>& strPoss)
{
	std::vector<D3DXVECTOR3> buf;

	for (auto i : strPoss)
	{
		std::stringstream ss{ i };
		std::string tmp;

		getline(ss, tmp, ':');
		float x = std::stof(tmp);

		getline(ss, tmp, ':');
		float y = std::stof(tmp);

		getline(ss, tmp, ':');
		float z = std::stof(tmp);

		buf.emplace_back(x, y, z);
	}
	return buf;
}

void MapAsset::SaveMapObject(std::string filename)
{
	std::ofstream file(filename + MAPOBJFILE);

	for (auto& i : m_object)
	{
		//NoteType
		if		(i.type == i.CIRCLE)file << "C";
		else if (i.type == i.SLIDER)file << "S";

		file << ",";

		//Time
		file << int(i.StartTime * 1000);
		if (i.type == i.SLIDER)	file <<"," << int(i.EndTime * 1000);

		//position
		for (auto& pos : i.Positions)
		{
			file <<"," << pos.x << ":" << pos.y << ":" << pos.z;
		}

		file << "\n";
	}
	file.close();
}