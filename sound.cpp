#include <XAudio2.h>
#include "sound.h"

typedef struct
{
	const char *pFilename;	
	int nCntLoop;		
} SOUNDPARAM;

HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

IXAudio2 *g_pXAudio2 = NULL;								
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			
IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	
BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					
DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					

SOUNDPARAM g_aParam[SOUND_LABEL_MAX] =
{
	{"resource/sound/Game_Bgm.wav", -1},		
	{"resource/sound/Start_Bgm.wav", -1},
	{"resource/sound/End_Bgm.wav", -1},
	{"resource/sound/Victory_Bgm.wav", -1},
	{"resource/sound/Boss_Bgm.wav", -1},

	{"resource/sound/shot000.wav", 0},			
	{"resource/sound/explosion000.wav", 0},
	{"resource/sound/get_item.wav", 0},
	{"resource/sound/bakuhatu.wav", 0},
	{"resource/sound/Ult_Create.wav", 0},
	{"resource/sound/Bullet_Enemy.wav", 0},
	{"resource/sound/Boss_Bullet_Player.wav", 0},
	{"resource/sound/Enemy_Bullet_Player.wav", 0},
	{"resource/sound/Boss_Distory.wav",0 },
	{"resource/sound/Enemy_3_Distory.wav",0 },
	{"resource/sound/Player_Distroy.wav",0 },
	{"resource/sound/Missile.wav",0 },
	{"resource/sound/Choice.wav",0 },
	{"resource/sound/Auto_Bullet_Shot.wav",0 },
	{"resource/sound/Auto_Bullet_Distory.wav",0 },
	{"resource/sound/Boss_Skill.wav",0 },
	{"resource/sound/Boss_Bullet.wav",0 },
	{"resource/sound/Enemy_Dis.wav",0 }








};

HRESULT InitSound(HWND hWnd)
{
	HRESULT hr;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "SoundError", "SoundError", MB_ICONWARNING);

		CoUninitialize();

		return E_FAIL;
	}
	
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "SoundError", "SoundError", MB_ICONWARNING);

		if(g_pXAudio2)
		{
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		CoUninitialize();

		return E_FAIL;
	}

	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		hFile = CreateFile(g_aParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "SoundError", "SoundError", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{
			MessageBox(hWnd, "SoundError", "SoundError", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
	
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "SoundError", "SoundError", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "SoundError", "SoundError", MB_ICONWARNING);
			return S_FALSE;
		}
		if(dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "SoundError", "SoundError", MB_ICONWARNING);
			return S_FALSE;
		}
	
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "SoundError", "SoundError", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "SoundError", "SoundError", MB_ICONWARNING);
			return S_FALSE;
		}

		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "SoundError", "SoundError", MB_ICONWARNING);
			return S_FALSE;
		}
		g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "SoundError", "SoundError", MB_ICONWARNING);
			return S_FALSE;
		}
	
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
		if(FAILED(hr))
		{
			MessageBox(hWnd, "SoundError", "SoundError", MB_ICONWARNING);
			return S_FALSE;
		}

		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = g_aSizeAudio[nCntSound];
		buffer.pAudioData = g_apDataAudio[nCntSound];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = g_aParam[nCntSound].nCntLoop;

		g_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);
	}

	return S_OK;
}

void UninitSound(void)
{
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			g_apSourceVoice[nCntSound]->Stop(0);
	
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;
	
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}
	
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	CoUninitialize();
}

HRESULT PlaySound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = g_aParam[label].nCntLoop;

	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{
		g_apSourceVoice[label]->Stop(0);

		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	g_apSourceVoice[label]->Start(0);

	return S_OK;
}

void StopSound(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{
		g_apSourceVoice[label]->Stop(0);

		g_apSourceVoice[label]->FlushSourceBuffers();
	}
}

void StopSound(void)
{
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			g_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}

HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

