//---------------------------------------------------------
//	Game							Date	2020/7/18
//									Author	本多玲虎		
//	ゲーム全体の管理クラス
//---------------------------------------------------------
#pragma once
class Scene_Base;

class Game
{
public:
	//mainでのみ呼び出します
	static bool Init();
	static bool UnInit();
	static bool Mainloop();

	//ゲームを終了します
	static void ExitGame();
	static Scene_Base* GetScene() { return m_currentScene; }

	//次のシーンへ切り替えます
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