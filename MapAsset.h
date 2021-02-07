#pragma once
#include "Asset.h"
#include <vector>
#include "AudioManeger.h"

enum class Judge
{
    None,
    Grate,
    Good,
    Bad,
    Miss,
    MAX
};


struct NOTE_OBJECT
{
    enum OBJECT_TYPE
    {
        CIRCLE, SLIDER, SPIN, MAX
    };
    OBJECT_TYPE type;
    float StartTime = -1.0f;
    float EndTime = -1.0f;
    int CpNum = -1;
    std::vector<D3DXVECTOR3> Positions;
    Judge judge = Judge::None;
};

struct MAP_METADATA
{
    std::string Title;
    std::string Artist;
    std::string Diffname;
    float       BPM;
    float       Offset;
    float       SongFileLength;
    float       BeatLength;
    float       Volume;
};


class MapAsset :
    public IAsset
{
public:
    virtual void Load(std::string filename) override;
    virtual void Unload() override;
    void Save(std::string filename);
    class AudioData_Asset* GetAudio() { return m_audio; }
    std::vector<NOTE_OBJECT>& GetMapObject() { return m_object; }
    MAP_METADATA& GetMapMetaData() { return m_metaData; }

private:
    //Load
    void ReadMapObject(std::string filename);
    void ReadMetaData(std::string filename);
    void CreateTestMapData();
    std::vector<D3DXVECTOR3> ReadPos(std::vector<std::string>& strPoss);

    //Save
    void SaveMapObject(std::string filename);


    std::vector<NOTE_OBJECT> m_object;
    class AudioData_Asset* m_audio;
    MAP_METADATA m_metaData;
};