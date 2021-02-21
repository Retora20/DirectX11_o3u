#include <Windows.h>
#include "main.h"
#include"input.h"
#include "Time.h"
#include "imgui.h"
#include "Scene_Base.h"
#include "Renderer.h"
#include "AudioManeger.h"
#include "Game.h"

#include "Scene_Test.h"
#include "Scene_Play_o3u.h"
#include "Scene_Title_o3u.h"
#include "Scene_Edit_o3u.h"
#include "Scene_None.h"

float	        Game::m_refreshRate;
bool            Game::m_exitFlag;

Scene_Base*     Game::m_currentScene = nullptr;
Scene_Base*     Game::m_nextScene = nullptr;



bool Game::Init()
{
    //各メンバ変数初期化
    m_exitFlag = false;

    srand((unsigned int)time(0));
    //モニターのリフレッシュレート取得
    auto hdc = GetDC(GetWindow());
    m_refreshRate = (float)GetDeviceCaps(hdc, VREFRESH);

    Input::Init(GetWindow());
    Time::Init();

    

    m_currentScene = new Scene_Title_o3u;

    m_currentScene->CreateGameObject();



    return false;
}

bool Game::UnInit()
{
    delete m_currentScene;

    AssetsManager::Unload();
    Input::Uninit();

    AudioManager::GetInstance()->UnInitSound();
    return false;
}

bool Game::Mainloop()
{
    //とりあえずモニターのリフレッシュレートの二倍でUpDate
   // if (1 / m_refreshRate * 2 <= Time::GetRawDeltaTime())
    {
        //入力更新
        Input::Update();
        //タイム更新
        Time::Update();

        //更新と描画を同期的に処理、将来的に非同期で行いたい
        Update();
        Draw();

        //シーン遷移
        if (m_nextScene)
        {
            delete m_currentScene;
            m_currentScene = m_nextScene;
            m_currentScene->CreateGameObject();
            m_nextScene = nullptr;
        }
    }

    return m_exitFlag;
}

void Game::ExitGame()
{
    m_exitFlag = true;
}

void Game::Update()
{
    Renderer::ImguiBegin();
    m_currentScene->Update();
}

void Game::Draw()
{
    //シェーダーに渡すタイム
    Renderer::UpdateTime();
    Renderer::UpdateVariable();

    Renderer::Begin();

    m_currentScene->Draw();


    Renderer::ImguiEnd();

    Renderer::End();
}