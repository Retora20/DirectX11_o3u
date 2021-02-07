#pragma once
#include "Component.h"
#include <deque>
#include <vector>
#include "MapAsset.h"

class MapObjectManager_Component:public Component
{
public:
	MapObjectManager_Component();
	virtual void Init() override;
	virtual void UnInit() override;
	virtual void Update() override;

	const float& GetStarTime() { return m_startTime; }
protected:
	enum keyState
	{
		None = 0,
		Triger,
		Press,
		Max
	};


	static constexpr float ApproachTime = 0.8f;
	static constexpr float ACSize = 2.0f;

	//îªíËÇÃíËêî
	static constexpr float Grate = 0.05f;
	static constexpr float Good = 0.1f;
	static constexpr float Bad = 0.2f;
	static constexpr float Miss = 0.3f;


	std::deque<class NoteDrawer*> m_curNote ,m_AllNote;
	class MapAsset* m_map =nullptr;
	class o3u_CameraGameObject* m_camera = nullptr;
	class Score_Drawer* m_score = nullptr;

	class AudioData_Asset* m_HS;
	class AudioData_Asset* m_clap;

	float m_startTime = 0.0f;
	float m_beatCount = 0.0f;
	float m_playEndTimeCount = 0.0f;

	bool m_once = false;


	void BeatPlaySound(float curTime);
	void NoteEnable(float curTime);
	bool CountPlayEnd();
	void CheckCircle(float curTime);
	void CheckSlider(float curTime);
	keyState GetKeyState();
	Judge TimingJudge(float Ans, float cur);
	bool HitCheck(const D3DXVECTOR3& pos, float size = 0.5f);
	D3DXVECTOR3 CalcBezierPoint(std::vector<D3DXVECTOR3>positions ,float t);
	void CurrentNotesUpdate(float curTime);
	void CreateJudgeGameObject(Judge judge,const D3DXVECTOR3& pos);
	void AddScore(Judge judge ,bool hold = false);

};