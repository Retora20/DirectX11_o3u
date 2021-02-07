#include "MapObjectManager.h"
#include "Asset.h"
#include "MapAsset.h"
#include "Game.h"
#include "NoteGameObject.h"
#include "SliderDrawer.h"
#include "CircleDrawer.h"
#include "Time.h"
#include "AC_Drawer.h"
#include "CameraGameObject.h"
#include "CameraComponent.h"
#include "TapJudgeDrawer.h"
#include "input.h"
#include "Scene_Play_o3u.h"
#include "Score_Drawer.h"
#include "Scene_Title_o3u.h"
#include "o3u_CameraGameObject.h"

MapObjectManager_Component::MapObjectManager_Component()
{
	m_map = new MapAsset;
	m_map->Load("Asset/map/ENGRAM");
	auto objs = m_map->GetMapObject();

	for (const auto& i : objs)
	{
		//ゲームオブジェクト作成
		auto o = Game::GetScene()->AddGameObject<NoteGameObject>(UpdateLayer::LAST);
		o->AddCompoent<AC_Drawer>()->SetObjectData(i);
		NoteDrawer* comp;

		//Todo:コンポーネント付与
		if (i.type == i.CIRCLE)
		{
			comp = o->AddCompoent<CircleDrawer>();
			comp->SetObjectData(i);
		}
		else if (i.type == i.SLIDER)
		{
			comp = o->AddCompoent<SliderDrawer>();
			comp->SetObjectData(i);
		}
		else if (i.type == i.SPIN)
		{
			;//未実装
		}

		m_AllNote.push_back(comp);
	}
	m_AllNote.shrink_to_fit();

	m_clap = AssetsManager::Assign<AudioData_Asset>("Asset/audio/clap.wav");
	m_HS = AssetsManager::Assign<AudioData_Asset>("Asset/audio/clap.wav");

	MATERIAL mt;
	mt.Diffuse = D3DXCOLOR(0,1,1,1);
	Renderer::SetMaterial(mt);

	float col[4] = { 0.2f,0.2f, 0.2f, 1.0f };
	Renderer::SetClearColor(col);

}

void MapObjectManager_Component::Init()
{
	m_camera= Game::GetScene()->GetGameObject<o3u_CameraGameObject>();
	m_score = GetOwnGameObject()->GetCompoent<Score_Drawer>();

	m_startTime = Time::GetRawTime();
	float start = -2.5f;

	m_map->GetAudio()->Play(0.1f, start);
}

void MapObjectManager_Component::UnInit()
{
	delete m_map;
}

void MapObjectManager_Component::Update()
{

	if (Input::GetKeyTrigger('R')) Game::NextScene<Scene_Play_o3u>();


	//初期化が終わってない場合リターン 要改善
	if (!m_AllNote.empty())
	{
		if (!m_AllNote[0]->GetOwnGameObject()) return;
	}

	//ノーツを全て処理した場合は2秒待ってからシーン遷移
	if (CountPlayEnd())	return;

	//現在時刻
	float curTime = Time::GetRawTime() - m_startTime;

	m_camera->SetCurTime(curTime);

	//ビート再生
	//BeatPlaySound(curTime);

	//時間が来たらノーツを表示
	NoteEnable(curTime);
	
	//現在表示されてるノーツの一個目だけ判定
	if (!m_curNote.empty() &&
		GetKeyState())
	{
		auto type = m_curNote[0]->GetData().type;
		if		(type == NOTE_OBJECT::CIRCLE)	CheckCircle(curTime);
		else if (type == NOTE_OBJECT::SLIDER)	CheckSlider(curTime);
	}

	//現在ノーツの更新
	CurrentNotesUpdate(curTime);
}

void MapObjectManager_Component::BeatPlaySound(float curTime)
{
	auto meta = m_map->GetMapMetaData();
	//ビート再生
	if (curTime >= meta.BeatLength * m_beatCount)
	{
		m_clap->Play(0.1f);
		m_beatCount += 1.0f;
	}
}

void MapObjectManager_Component::NoteEnable(float curTime)
{
	if (!m_AllNote.empty())
	{
		while (curTime >= m_AllNote[0]->GetData().StartTime - ApproachTime)
		{
			auto note = m_AllNote[0];
			m_AllNote.pop_front();

			note->SetEnable();
			note->GetOwnGameObject()->GetCompoent<AC_Drawer>()->SetEnable();
			m_curNote.push_back(note);

			if (m_AllNote.empty())	break;
		}
	}

}

bool MapObjectManager_Component::CountPlayEnd()
{
	bool ret = false;
	if (m_curNote.empty()&& m_AllNote.empty())	
	{
		if (!m_once && m_playEndTimeCount >= 1.0f)
		{
			//Game::NextScene<Scene_Test_o3u>();
			//return ret;

			m_once = true;
			auto obj = Game::GetScene()->AddGameObject<FadeEffectGameObject>();

			obj->m_start = 1.0f;
			obj->m_end = 0.0f;
			obj->m_speed = 1.0f;
		}


		m_playEndTimeCount += Time::GetDeltaTime();
		ret = true;

		if (m_playEndTimeCount>=2.0f)
		{
			m_map->GetAudio()->Stop();
			Game::NextScene<Scene_Title_o3u>();
		}
	}
	return ret;
}

void MapObjectManager_Component::CheckCircle(float curTime)
{
	//当たり判定
	auto data = m_curNote[0]->GetData();
	bool isHit = HitCheck(data.Positions[0]);

	if (isHit && GetKeyState() == keyState::Triger)
	{
		Judge j = TimingJudge(data.StartTime, curTime);
		if (j == Judge::None) return;

		CreateJudgeGameObject(j, data.Positions[0]);
		m_HS->Play(0.1f);

		//todo スコア加算処理
		AddScore(j);
		m_curNote[0]->GetOwnGameObject()->Destroy();
		m_curNote.pop_front();
	}
}

void MapObjectManager_Component::CheckSlider(float curTime)
{
	auto data = m_curNote[0]->GetData();
	float slen = data.EndTime - data.StartTime;
	float curt = data.EndTime - curTime;
	float t = curt / slen;
	t = std::clamp((1 - t), 0.0f, 1.0f);

	bool isHit = HitCheck(CalcBezierPoint(data.Positions, t), 1.0f);

	if (isHit)
	{
		//初押し
		if (GetKeyState() == keyState::Triger &&
			data.judge == Judge::None)
		{
			Judge j = TimingJudge(data.StartTime, curTime);
			if (j == Judge::None) return;

			CreateJudgeGameObject(j, data.Positions[0]);
			m_HS->Play(0.1f);
			m_curNote[0]->SetJudge(j);
			AddScore(j);
		}
		else
		{
			AddScore(m_curNote[0]->GetData().judge,true);
		}
	}
}

MapObjectManager_Component::keyState MapObjectManager_Component::GetKeyState()
{
	if (!Input::GetKeyPress('Z')&&
		!Input::GetKeyPress('X')&& 
		!Input::GetKeyPress(VK_LBUTTON)&& 
		!Input::GetKeyPress(VK_RBUTTON) )
	{
		return keyState::None;
	}

	else if (Input::GetKeyTrigger('Z')		||
			 Input::GetKeyTrigger('X')		||
			 Input::GetKeyTrigger(VK_LBUTTON)||
			 Input::GetKeyTrigger(VK_RBUTTON))
	{
		return keyState::Triger;
	}

	else
	{
		return keyState::Press;
	}
}

Judge MapObjectManager_Component::TimingJudge(float Ans, float cur)
{
	Judge judge;

	if (cur < Ans + Grate&&
		cur > Ans - Grate)
	{
		judge = Judge::Grate;
	}
	else if	(cur < Ans + Good &&
		 	 cur > Ans - Good)
	{
		judge = Judge::Good;
	}
	else if (cur < Ans + Bad &&
			 cur > Ans - Bad)
	{
		judge = Judge::Bad;
	}
	else if (cur < Ans + Miss &&
			 cur > Ans - Miss)
	{
		judge = Judge::Miss;
	}
	else
	{
		judge = Judge::None;
	}
	return judge;
}

bool MapObjectManager_Component::HitCheck(const D3DXVECTOR3& pos, float size)
{
	auto mouse = m_camera->GetCompoent<CameraComponent>()->GetMouseVector();

	//当たり判定
	D3DXVECTOR3 StP = pos - mouse.first;
	D3DXVECTOR3 mouselen = mouse.second * D3DXVec3Dot(&StP, &mouse.second);
	D3DXVECTOR3 lenvec;
	D3DXVec3Cross(&lenvec, &StP, &mouse.second);

	float l = fabsf(D3DXVec3Length(&lenvec));
	return (l <= size);
}

D3DXVECTOR3 MapObjectManager_Component::CalcBezierPoint(std::vector<D3DXVECTOR3> positions, float t)
{
	for (size_t i = 0; i < positions.size() - 1; i++)
	{
		for (size_t j = 0; j < positions.size() -1 -i ; j++)
		{
			D3DXVec3Lerp(&positions[j], &positions[j], &positions[j + 1], t);
		}
	}
	return positions[0];
}

void MapObjectManager_Component::CurrentNotesUpdate(float curTime)
{


	if (m_curNote.empty()) return;

	//時間経過削除
	while (curTime >= m_curNote[0]->GetData().EndTime)
	{
		auto data = m_curNote[0]->GetData();
		if (data.type == NOTE_OBJECT::CIRCLE
			&& curTime < data.EndTime + Miss)
		{
			break;
		}

		//スライダーの場合
		if (data.type == NOTE_OBJECT::SLIDER &&
			HitCheck(data.Positions[data.Positions.size() - 1], ACSize / 2) &&
			GetKeyState() >= keyState::Triger)
		{
			m_HS->Play(0.1f);
		}

		//BAD表示、スコア関連

		m_curNote[0]->GetOwnGameObject()->Destroy();

		Judge j = m_curNote[0]->GetData().judge;
		if (j==Judge::Miss|| j == Judge::None)
		{
			CreateJudgeGameObject(Judge::Miss, m_curNote[0]->GetData().Positions[0]);
		}
		m_curNote[0]->GetData();
		m_curNote.pop_front();
		if (m_curNote.empty()) return;
	}

	for (auto note : m_curNote)
	{
		auto data = note->GetData();
		auto AC = note->GetOwnGameObject()->GetCompoent<AC_Drawer>();

		if (data.type == data.CIRCLE)
		{
			//ACの大きさ
			if(curTime > data.StartTime)
			{
				AC->SetEnable(false);
			}
			else
			{
				float t = data.StartTime - curTime;
				AC->SetScale(t * ACSize / ApproachTime + 1.0f);
			}
		}

		else if (data.type == data.SLIDER)
		{
			if (curTime > data.StartTime)
			{
				AC->SetScale(2.0f);
				float slen = data.EndTime - data.StartTime;
				float curt = data.EndTime - curTime;
				float t = curt / slen;
				t = std::clamp((1 - t),0.0f,1.0f);
				AC->SetPos(CalcBezierPoint(data.Positions, t));


			}
			else
			{
				float t = data.StartTime - curTime;
				AC->SetScale(t * ACSize / ApproachTime + 1.0f);
			}
		}

	}
}

void MapObjectManager_Component::CreateJudgeGameObject(Judge judge, const D3DXVECTOR3& pos)
{
	auto gobj= Game::GetScene()->AddGameObject<NoteGameObject>();
	gobj->SetPosition(pos); 
	auto comp = gobj->AddCompoent<TapJudgeDrawer>();

	switch (judge)
	{
	case Judge::Grate:
		comp->AssignTexture("Asset/texture/300.png");	break;
	case Judge::Good:
		comp->AssignTexture("Asset/texture/100.png");	break;
	case Judge::Bad:
		comp->AssignTexture("Asset/texture/50.png");	break;
	case Judge::Miss:
	case Judge::None:
		comp->AssignTexture("Asset/texture/miss.png");	break;

	default:			break;
	}
	
}

void MapObjectManager_Component::AddScore(Judge judge, bool hold)
{
	float score = 0.0f;

	switch (judge)
	{
	case Judge::Grate:	score = 300;	break;
	case Judge::Good:	score = 100;	break;
	case Judge::Bad:	score = 50;		break;
	default:			break;
	}

	if (hold)	score *= Time::GetDeltaTime();
	m_score->AddScore(score);
}
