#include "AudioManeger.h"

AudioManager* AudioManager::instance = nullptr;

AudioManager::~AudioManager()
{
	UnInitSound();
}

HRESULT AudioManager::InitSound(HWND hWnd)
{
	// COMライブラリの初期化
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);


	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&m_pXAudio2, 0);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// マスターボイスの生成
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if (m_pXAudio2)
		{
			// XAudio2オブジェクトの開放
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}
	return S_OK;
}

void AudioManager::UnInitSound(void)
{
	// マスターボイスの破棄
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;

	if (m_pXAudio2)
	{
		// XAudio2オブジェクトの開放
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}

	// COMライブラリの終了処理
	CoUninitialize();
}

AudioManager* AudioManager::GetInstance()
{
	if (!instance)
	{
		instance = new AudioManager();
		instance->InitSound();
	}
	return instance;
}

void AudioData_Asset::Load(std::string filename)
{
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	HWND hWnd = GetWindow();

	// バッファのクリア
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// サウンドデータファイルの生成
	hFile = CreateFile(filename.data(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
		return;
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
		return;
	}

	// WAVEファイルのチェック
	HRESULT hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
		return;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
		return;
	}
	if (dwFiletype != 'EVAW')
	{
		MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
		return;
	}

	// フォーマットチェック
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
		return;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
		return;
	}

	// オーディオデータ読み込み
	hr = CheckChunk(hFile, 'atad', &m_aSizeAudio, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
		return;
	}
	m_apDataAudio = new BYTE[m_aSizeAudio];
	hr = ReadChunkData(hFile, m_apDataAudio, m_aSizeAudio, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
		return;
	}

	// ソースボイスの生成
	hr = AudioManager::GetInstance()->GetXAudio2IF()->CreateSourceVoice(&m_apSourceVoice, &(wfx.Format), 0, 2.0f /*&callback*/);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
		return;
	}
}

void AudioData_Asset::Unload()
{
	// 一時停止
	m_apSourceVoice->Stop(0);

	// ソースボイスの破棄
	m_apSourceVoice->DestroyVoice();

	// オーディオデータの開放
	delete m_apDataAudio;
}

void AudioData_Asset::Play(float Volume, float start, int loopcnt, float loopbegin)
{
	//本来はちゃんとオーディオデータのメタデータを参照して
	//データサイズを計算するべき
	if (start * 44100 * 4 >= m_aSizeAudio)
	{
		return;
	}


	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio;
	buffer.pAudioData = m_apDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = loopcnt;
	buffer.PlayBegin = start * 44100;
	buffer.LoopBegin = loopbegin * 44100;


	// 状態取得
	m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		m_apSourceVoice->Stop(0);

		// オーディオバッファの削除
		m_apSourceVoice->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_apSourceVoice->SubmitSourceBuffer(&buffer);

	// 再生
	m_apSourceVoice->SetVolume(Volume);
	m_apSourceVoice->Start(0);
}

void AudioData_Asset::Stop()
{
	m_apSourceVoice->Stop(0);
}


void AudioData_Asset::Resume()
{
	XAUDIO2_VOICE_STATE xa2state;
	// 状態取得
	m_apSourceVoice->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
		m_apSourceVoice->Start(0);
	}
}

float AudioData_Asset::GetCurentTime()
{
	XAUDIO2_VOICE_STATE xa2state;
	m_apSourceVoice->GetState(&xa2state);

	return (float)xa2state.SamplesPlayed / 44100.0f;
}

HRESULT AudioData_Asset::CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

HRESULT AudioData_Asset::ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}
