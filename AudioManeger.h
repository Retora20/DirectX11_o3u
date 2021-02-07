//---------------------------------------------------------
//
//	AudioManager				Date	2020/11/28
//
//	XAudio2のラッパー			Author	本多玲虎		
//
//---------------------------------------------------------
#pragma once
#include <Windows.h>
#include <XAudio2.h>
#include <mmsystem.h>
#include "Asset.h"
#pragma comment (lib, "xaudio2.lib") 
#pragma comment (lib, "winmm.lib") 


class AudioManager
{
public:
	~AudioManager();

	HRESULT InitSound(HWND hWnd = 0);
	void UnInitSound(void);

	static AudioManager* GetInstance();
	IXAudio2* GetXAudio2IF() { return m_pXAudio2; }

private:
	AudioManager() {}
	static AudioManager* instance;							

	IXAudio2* m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// マスターボイス

	//Xaudio2CallBack  callback;
	HANDLE hEvent = NULL;

};


class AudioData_Asset :public IAsset
{
public:
	AudioData_Asset() {}
	~AudioData_Asset() {}

	virtual void Load(std::string filename) override;
	virtual void Unload() override;
	void Play(float Volume = 1.0f, float start = 0.0f, int loopcnt = 0, float loopbegin = 0.0f);
	void Stop();
	void Resume();

	float GetCurentTime();
	float GetLength() { return m_aSizeAudio / 44100.0f; }

private:
	IXAudio2SourceVoice* m_apSourceVoice =nullptr;
	BYTE* m_apDataAudio = nullptr;
	DWORD m_aSizeAudio = 0;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
};