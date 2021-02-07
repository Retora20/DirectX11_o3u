
#include "main.h"
#include "input.h"


BYTE  Input::m_OldKeyState[256];
BYTE  Input::m_KeyState[256];
HWND  Input::m_hwnd;
POINT Input::m_mousePos;

void Input::Init(HWND hwnd)
{
	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );
	m_mousePos = { 0,0 };
	m_hwnd = hwnd;
}

void Input::Uninit() 
{
}

void Input::Update()
{

	memcpy( m_OldKeyState, m_KeyState, 256 );
	GetKeyboardState( m_KeyState );

	GetCursorPos(&m_mousePos);
	ScreenToClient(m_hwnd, &m_mousePos);
}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

bool Input::GetKeyRelease(BYTE KeyCode)
{
	return (!(m_KeyState[KeyCode] & 0x80) && (m_OldKeyState[KeyCode] & 0x80));
}

POINT Input::GetMousePos()
{
	return m_mousePos;
}

void Input::SetMousePos(int x, int y)
{
	POINT pos = { x,y };
	ClientToScreen(m_hwnd, &pos);
	SetCursorPos(pos.x, pos.y);
}
