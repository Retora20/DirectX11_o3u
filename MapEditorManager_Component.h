#pragma once
#include "MapObjectManager.h"
#include <string>
class MapEditorManager_Component :
    public MapObjectManager_Component
{
public:
    void Init() override;
    void Update() override;

private:
    bool    m_isPlay = false;
    float   m_curtime = 0;
    int     m_beatSnap = 4;

    //�m�[�c�I��
    int m_selectpos = 0;
    bool m_isUseGizumo = false;

    void DrawImgui();

    bool LoadMap(std::string filename);
    bool SaveMap(std::string filename);

    bool ReloadMap(void);

    void NoteEnable(float curTime);
    void UpdateNotes(float curTime);


    //startTime�Ń\�[�g
    void SortNotes();

};

