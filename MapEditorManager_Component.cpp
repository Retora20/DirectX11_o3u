#include <algorithm>
#include "MapEditorManager_Component.h"
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
#include "imgui.h"
#include "ImGuizmo.h"
#include "EnterNextScene.h"

void MapEditorManager_Component::Init()
{
	m_clap = AssetsManager::Assign<AudioData_Asset>("Asset/audio/clap.wav");
	m_HS = AssetsManager::Assign<AudioData_Asset>("Asset/audio/clap.wav");

	MATERIAL mt;
	mt.Diffuse = D3DXCOLOR(0, 1, 1, 1);
	Renderer::SetMaterial(mt);

	float col[4] = { 0.2f,0.2f, 0.2f, 1.0f };
	Renderer::SetClearColor(col);

	m_startTime = Time::GetRawTime();

	m_camera = Game::GetScene()->GetGameObject<o3u_CameraGameObject>();
}

void MapEditorManager_Component::Update()
{
	DrawImgui();

	if (m_isPlay)
	{
		m_curtime = Time::GetRawTime() - m_startTime;
	}
	m_camera->SetCurTime(m_curtime);


	//初期化が終わってない場合はリターン
	if (!m_AllNote.empty())
	{
		if (!m_AllNote[0]->GetOwnGameObject()) return;
	}
	NoteEnable(m_curtime);
	UpdateNotes(m_curtime);
}

bool MapEditorManager_Component::LoadMap(std::string filename)
{
	//既にノーツがある場合クリア
	for (auto i : m_AllNote)
	{
		i->GetOwnGameObject()->Destroy();
	}
	m_AllNote.clear();
	m_curNote.clear();

	if (m_map)	delete m_map;
	
	//よみこみ

	m_map = new MapAsset;
	m_map->Load(filename);

	//ゲームオブジェクト配置
	auto objs = m_map->GetMapObject();
	for (const auto& i : objs)
	{
		//ゲームオブジェクト作成
		auto o = Game::GetScene()->AddGameObject<NoteGameObject>(UpdateLayer::LAST);
		o->AddCompoent<AC_Drawer>()->SetObjectData(i);
		NoteDrawer* comp;

		//コンポーネント付与
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

	return true;
}

bool MapEditorManager_Component::SaveMap(std::string filename)
{
	if (m_map)
	{
		SortNotes();
		m_map->Save(filename);
		return true;
	}
	return false;
}

bool MapEditorManager_Component::ReloadMap(void)
{
	//既にノーツがある場合クリア
	for (auto i : m_AllNote)
	{
		i->GetOwnGameObject()->Destroy();
	}
	m_AllNote.clear();
	m_curNote.clear();


	//ゲームオブジェクト配置
	auto objs = m_map->GetMapObject();
	for (const auto& i : objs)
	{
		//ゲームオブジェクト作成
		
		auto o = Game::GetScene()->AddGameObject<NoteGameObject>(UpdateLayer::LAST);
		o->AddCompoent<AC_Drawer>()->SetObjectData(i);
		NoteDrawer* comp;
		
		//コンポーネント付与
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

		m_AllNote.push_back(comp);
	}
	m_AllNote.shrink_to_fit();

	return true;
}

void MapEditorManager_Component::NoteEnable(float curTime)
{
	if (!m_AllNote.empty())
	{
		for (auto i : m_AllNote)
		{
			//表示
			if (curTime >= i->GetData().StartTime - ApproachTime &&
				curTime <= i->GetData().EndTime)
			{
				auto result = std::find(m_curNote.begin(), m_curNote.end(), i);
				if (result == m_curNote.end())
				{
					i->SetEnable();
					i->GetOwnGameObject()->GetCompoent<AC_Drawer>()->SetEnable();
					m_curNote.push_back(i);
				}
			}
			else //非表示
			{
				auto result = std::find(m_curNote.begin(), m_curNote.end(), i);
				if (result != m_curNote.end())
				{
					i->SetEnable(false);
					i->GetOwnGameObject()->GetCompoent<AC_Drawer>()->SetEnable(false);
					m_curNote.erase(result);
				}
			}
			if (m_AllNote.empty())	break;
		}
	}
}

void MapEditorManager_Component::UpdateNotes(float curTime)
{
	for (auto note : m_curNote)
	{
		auto data = note->GetData();
		if (data.CpNum == -1) continue;


		auto AC = note->GetOwnGameObject()->GetCompoent<AC_Drawer>();

		if (data.type == data.CIRCLE)
		{
			//ACの大きさ
			if (curTime > data.StartTime)
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
				t = std::clamp((1 - t), 0.0f, 1.0f);
				AC->SetPos(CalcBezierPoint(data.Positions, t));
			}
			else
			{
				float t = data.StartTime - curTime;
				AC->SetPos(data.Positions[0]);
				AC->SetScale(t * ACSize / ApproachTime + 1.0f);
			}
		}
	}
}

void MapEditorManager_Component::SortNotes()
{
	auto &notes = m_map->GetMapObject();

	std::sort(notes.begin(), notes.end(),
		[](NOTE_OBJECT A, NOTE_OBJECT B)
		{
			return A.StartTime < B.StartTime;
		});
}

void MapEditorManager_Component::DrawImgui()
{
	  //menubar
	if (ImGui::BeginMainMenuBar())
	{
		//todo
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Load")) { LoadMap("Asset/map/ENGRAM"); }
			if (ImGui::MenuItem("Save")) { SaveMap("Asset/map/ENGRAM"); }
			if (ImGui::MenuItem("Exit")) 
			{ 
				m_map->GetAudio()->Stop();
				Game::GetScene()->AddGameObject<EnterNextScene<Scene_Title_o3u>>()->Fade();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	if (ImGui::Begin("Time"))
	{
		if (ImGui::DragFloat("Time",&m_curtime,0.1f,0.0f,0.0f, "%.3f"))
		{
			m_curtime = std::max(m_curtime, 0.0f);
			m_startTime = Time::GetRawTime() - m_curtime;
			if (m_isPlay)
			{
				m_map->GetAudio()->Play(0.1f, m_curtime);
			}
		}
		if (ImGui::Button("play/stop"))
		{
			if (m_isPlay)
			{
				m_map->GetAudio()->Stop();
			}
			else
			{
				m_startTime = Time::GetRawTime() - m_curtime;
				m_map->GetAudio()->Play(0.1f, m_curtime);
			}
			m_isPlay = !m_isPlay;
		}

		ImGui::SameLine();

		if (ImGui::Button("<"))
		{
			int snapdist = m_map->GetMapMetaData().BeatLength / m_beatSnap * 1000;
			int inttime = m_curtime * 1000;
			int offset = m_map->GetMapMetaData().Offset * 1000;

			//スナップ済みの場合
			if (!((inttime - offset) % snapdist))
				inttime -= snapdist;
			else//途中
				inttime = ((inttime - offset) / snapdist) * snapdist + offset;

			m_curtime = (float)inttime / 1000;
			m_curtime = std::max(m_curtime, (float)(offset / 1000));
			m_startTime = Time::GetRawTime() - m_curtime;
			if (m_isPlay)
			{
				m_map->GetAudio()->Play(0.1f, m_curtime);
			}
		}

		ImGui::SameLine();

		if (ImGui::Button(">"))
		{
			int snapdist = m_map->GetMapMetaData().BeatLength / m_beatSnap * 1000;
			int inttime = m_curtime * 1000;
			int offset = m_map->GetMapMetaData().Offset * 1000;

			//スナップ済みの場合
			if (!((inttime - offset) % snapdist))
				inttime += snapdist;
			else//途中
				inttime = ((inttime - offset) / snapdist) * snapdist + snapdist + offset;

			m_curtime = (float)inttime /1000;
			m_curtime = std::max(m_curtime, (float)(offset/1000));
			m_startTime = Time::GetRawTime() - m_curtime;
			if (m_isPlay)
			{
				m_map->GetAudio()->Play(0.1f, m_curtime);
			}
		}

		//BeatSnap 
		if (ImGui::DragInt("BeatSnap",&m_beatSnap,0.05,1,16))
		{
		}
	}
	ImGui::End();



	//ノーツデータ表示＆編集
	bool isReload = false;
	int openIdx = -1;
	auto& notes = m_map->GetMapObject();
	if (ImGui::Begin("Notes"))
	{
		if (ImGui::Button("Sort"))
		{
			SortNotes();
		}
		ImGui::SameLine();
		if (ImGui::Button("AddCircle"))
		{
			NOTE_OBJECT add;
			add.type = add.CIRCLE;
			add.Positions.push_back({ 0,0,0 });
			add.StartTime = add.EndTime = m_curtime;
			add.CpNum = add.Positions.size();

			notes.push_back(add);
			SortNotes();
			isReload = true;
		}
		ImGui::SameLine();

		if (ImGui::Button("AddSlider"))
		{
			NOTE_OBJECT add;
			add.type = add.SLIDER;
			add.Positions.push_back({ 0,0,0 });
			add.Positions.push_back({ 1,0,0 });
			add.StartTime = m_curtime;
			add.EndTime = m_curtime + m_map->GetMapMetaData().BeatLength;
			add.CpNum = add.Positions.size();

			notes.push_back(add);
			SortNotes();
			isReload = true;
		}

		//ノーツ編集
		for (size_t notecnt = 0; notecnt < m_AllNote.size(); notecnt++)
		{
			//ラベル文字列
			std::string name = "";
			name += std::to_string(notes[notecnt].StartTime);
			ImGui::Text(name.data());
			ImGui::SameLine();

			name = std::to_string(notecnt);
			if (notes[notecnt].type == NOTE_OBJECT::CIRCLE)
				name += "Circle";
			else if (notes[notecnt].type == NOTE_OBJECT::SLIDER)
				name += "Slider";

			if (ImGui::TreeNode(name.data()))
			{
				if (openIdx == -1)openIdx = notecnt;

				//Time
				ImGui::Text("time");
				float dist = m_map->GetMapMetaData().BeatLength / m_beatSnap;
				if (notes[notecnt].type == NOTE_OBJECT::SLIDER)
				{
					if (ImGui::InputFloat("start", &notes[notecnt].StartTime, dist))
					{
						isReload = true;
					}
					
				}
				if (ImGui::InputFloat("end", &notes[notecnt].EndTime, dist))
				{
					isReload = true;
				}

				//Position
				for (size_t idx = 0; idx < notes[notecnt].Positions.size(); idx++)
				{
					std::string label = "";
					label = "Pos";
					label += std::to_string(idx);


					if (ImGui::DragFloat3(label.data(), notes[notecnt].Positions[idx],0.01f))
					{
						isReload = true;
					};

					label = "G" + std::to_string(idx);
					if (ImGui::RadioButton(label.data(),idx == m_selectpos))
					{
						m_selectpos = idx;
					}



					if (notes[notecnt].type == NOTE_OBJECT::SLIDER)
					{
						ImGui::SameLine();

						label = "U";
						label += std::to_string(idx);
						if (ImGui::Button(label.data()))
						{

							if (idx > 0)
							{
								const D3DXVECTOR3 tmppos = notes[notecnt].Positions[idx];
								notes[notecnt].Positions.erase(notes[notecnt].Positions.begin() + idx);
								notes[notecnt].Positions.insert(notes[notecnt].Positions.begin() + idx - 1, tmppos);

								isReload = true;
							}
						}
						ImGui::SameLine();

						label = "D";
						label += std::to_string(idx);
						if (ImGui::Button(label.data()))
						{
							if (idx < notes[notecnt].Positions.size() -1)
							{
								const D3DXVECTOR3 tmppos = notes[notecnt].Positions[idx];
								notes[notecnt].Positions.erase(notes[notecnt].Positions.begin() + idx);
								notes[notecnt].Positions.insert(notes[notecnt].Positions.begin() + idx + 1, tmppos);

								isReload = true;

							}
						}

						label = "Delete";
						label += std::to_string(idx);
						ImGui::SameLine();
						if (ImGui::Button(label.data()))
						{
							if (notes[notecnt].CpNum > 2)
							{
								notes[notecnt].Positions.erase(notes[notecnt].Positions.begin() + idx);
								notes[notecnt].CpNum--;
								isReload = true;
							}
						}
					}

				}

				//SliderControllPoints
				if (notes[notecnt].type == NOTE_OBJECT::SLIDER)
				{
					if (ImGui::Button("AddCP"))
					{
						notes[notecnt].Positions.push_back({ 0, 0, 0 });
						notes[notecnt].CpNum++;
						isReload = true;
					}
				}

				ImGui::SameLine();

				//delete
				if (ImGui::Button("Delete Note"))
				{
					notes.erase(notes.begin() + notecnt);
					openIdx = std::min((int)notes.size() - 1, openIdx);

					isReload = true;
					ImGui::TreePop();
					m_selectpos = 0;
					break;
				}
				
				ImGui::TreePop();
			}

		}
	}	ImGui::End();


	if (openIdx != -1)
	{
		if (ImGuizmo::IsOver() && Input::GetKeyPress(VK_LBUTTON))
		{
			m_isUseGizumo = true;
		}
		else if (m_isUseGizumo)
		{
			m_isUseGizumo = false;
			isReload = true;
		}


		//PosGizumo
		auto camera = m_camera->GetCompoent<CameraComponent>();
		if (!camera) return;
		if (!camera->GetOwnGameObject()) return;
		ImGuiIO& io = ImGui::GetIO();
		ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
		m_selectpos = std::min(m_selectpos, (int)notes[openIdx].Positions.size() - 1);
		D3DXVECTOR3& pos = notes[openIdx].Positions[m_selectpos];
		static float rot[3] = {};
		static float scl[3] = { 1,1,1 };
		D3DXMATRIX world;
		D3DXMatrixIdentity(&world);

		ImGuizmo::RecomposeMatrixFromComponents(pos,
			rot, scl, world);

		D3DXMATRIX view = camera->GetViewMatrix();
		D3DXMATRIX proj = camera->GetProjectionMatrix();

		ImGuizmo::Manipulate(view, proj,
			ImGuizmo::OPERATION::TRANSLATE,
			ImGuizmo::MODE::WORLD,
			world

		);
		ImGuizmo::DecomposeMatrixToComponents(world, pos, rot, scl);

	}

	if (isReload)	ReloadMap();
}