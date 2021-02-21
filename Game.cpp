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
    //�e�����o�ϐ�������
    m_exitFlag = false;

    srand((unsigned int)time(0));
    //���j�^�[�̃��t���b�V�����[�g�擾
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
    //�Ƃ肠�������j�^�[�̃��t���b�V�����[�g�̓�{��UpDate
   // if (1 / m_refreshRate * 2 <= Time::GetRawDeltaTime())
    {
        //���͍X�V
        Input::Update();
        //�^�C���X�V
        Time::Update();

        //�X�V�ƕ`��𓯊��I�ɏ����A�����I�ɔ񓯊��ōs������
        Update();
        Draw();

        //�V�[���J��
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
    //�V�F�[�_�[�ɓn���^�C��
    Renderer::UpdateTime();
    Renderer::UpdateVariable();

    Renderer::Begin();

    m_currentScene->Draw();


    Renderer::ImguiEnd();

    Renderer::End();
}