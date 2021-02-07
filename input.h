#pragma once
class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];
	static POINT m_mousePos;
	static HWND m_hwnd;

public:
	static void Init(HWND hwnd);
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );
	static bool GetKeyRelease(BYTE KeyCode);

	static POINT GetMousePos();
	static void	 SetMousePos(int x, int y);

};
