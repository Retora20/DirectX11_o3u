#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define	NOMINMAX
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <utility>
#include <algorithm>


#pragma warning(push)
#pragma warning(disable:4005)

#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>
#include <DirectXMath.h>

#pragma warning(pop)



#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")


#define SCREEN_WIDTH	(1280)			// ウインドウの幅
#define SCREEN_HEIGHT	(720)			// ウインドウの高さ


HWND GetWindow();


inline float lerp(float v0, float v1, float t) {
	return (1 - t) * v0 + t * v1;
}

//
