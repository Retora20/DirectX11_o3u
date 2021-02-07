//---------------------------------------------------------
//	Game							Date	2020/7/18
//									Author	�{�����		
//	�Q�[���S�̂̊Ǘ��N���X
//---------------------------------------------------------
#pragma once
class Scene_Base;

class Game
{
public:
	//main�ł̂݌Ăяo���܂�
	static bool Init();
	static bool UnInit();
	static bool Mainloop();

	//�Q�[�����I�����܂�
	static void ExitGame();
	static Scene_Base* GetScene() { return m_currentScene; }

	//���̃V�[���֐؂�ւ��܂�
	template<class T>
	static void NextScene()
	{
		if (!m_nextScene)
		{
			m_nextScene = new T;
		}
	}

private:
	static void Update();
	static void Draw();

	static float	m_refreshRate;
	static bool		m_exitFlag;


	static Scene_Base* m_currentScene;
	static Scene_Base* m_nextScene;
};