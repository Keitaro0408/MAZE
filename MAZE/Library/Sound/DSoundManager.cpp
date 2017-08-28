/**
* @file   DSoundManager.cpp
* @brief  DSoundManagerクラスの実装
* @author kotani
*/
#include "DSoundManager.h"
#include <mmsystem.h>


Lib::DSoundManager::DSoundManager() :
m_pDSound8(nullptr),
m_hWnd(nullptr)
{
}

Lib::DSoundManager::~DSoundManager()
{
}

bool Lib::DSoundManager::Initialize(HWND _hWnd)
{
	if (m_pDSound8 != nullptr)
	{
		MessageBox(_hWnd, TEXT("DSoundManagerはすでに初期化されています"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	m_hWnd = _hWnd;

	if (FAILED(DirectSoundCreate8(nullptr, &m_pDSound8, nullptr)))
	{
		MessageBox(m_hWnd, TEXT("サウンドデバイスの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (FAILED(m_pDSound8->SetCooperativeLevel(m_hWnd, DSSCL_NORMAL)))
	{
		MessageBox(m_hWnd, TEXT("協調レベルの設定に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDSound8->Release();
		return false;
	}
	return true;
}

void Lib::DSoundManager::Finalize()
{
	if (m_pDSound8 != nullptr)
	{
		m_pDSound8->Release();
		m_pDSound8 = nullptr;
	}
}

void Lib::DSoundManager::SoundOperation(int _index, SOUND_OPERATION _operation)
{
	switch (_operation)
	{
	case SOUND_PLAY:
		m_pSound[_index]->Play(0, 0, 0);
		break;
	case SOUND_LOOP:
		m_pSound[_index]->Play(0, 0, DSBPLAY_LOOPING);
		break;
	case SOUND_STOP:
		m_pSound[_index]->Stop();
		break;
	case SOUND_RESET:
		m_pSound[_index]->SetCurrentPosition(0);
		break;
	case SOUND_STOP_RESET:
		m_pSound[_index]->Stop();
		m_pSound[_index]->SetCurrentPosition(0);
		break;
	}
}

void Lib::DSoundManager::SetSoundVolume(int _index, int _ratio)
{
	if (_ratio <= 0)
	{
		m_pSound[_index]->SetVolume(-10000);
	}
	else
	{
		int dB = ((int)(log10f((float)_ratio) * 5000.0f) - 10000);
		m_pSound[_index]->SetVolume(dB);
	}
	
}

bool Lib::DSoundManager::LoadSound(LPSTR _pFileName, int* _pIndex)
{
	WAVEFORMATEX WaveFormat;
	BYTE* pWaveData = nullptr;
	DWORD WaveSize = 0;

	if (!ReadWave(_pFileName, &WaveFormat, &pWaveData, &WaveSize))
	{
		MessageBox(m_hWnd, TEXT("waveファイルが開けませんでした"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	DSBUFFERDESC DSBufferDesc;
	DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	DSBufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	DSBufferDesc.dwBufferBytes = WaveSize;
	DSBufferDesc.dwReserved = 0;
	DSBufferDesc.lpwfxFormat = &WaveFormat;
	DSBufferDesc.guid3DAlgorithm = GUID_NULL;

	LPDIRECTSOUNDBUFFER8 pDSBuffer = nullptr;
	LPDIRECTSOUNDBUFFER pTmpBufer = nullptr;
	m_pDSound8->CreateSoundBuffer(&DSBufferDesc, &pTmpBufer, nullptr);
	pTmpBufer->QueryInterface(IID_IDirectSoundBuffer8, reinterpret_cast<void**>(&pDSBuffer));
	pTmpBufer->Release();
	
	if (pDSBuffer == nullptr)
	{
		m_pDSound8->Release();
		MessageBox(m_hWnd, TEXT("サウンドバッファ作成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	LPVOID pWriteData = 0;
	DWORD WriteDataLength = 0;
	if (FAILED(pDSBuffer->Lock(0, 0, &pWriteData, &WriteDataLength, nullptr, nullptr, DSBLOCK_ENTIREBUFFER)))
	{
		m_pDSound8->Release();
		delete[] pWaveData;
		MessageBox(m_hWnd, TEXT("サウンドバッファのロックに失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	memcpy(pWriteData, pWaveData, WriteDataLength);
	pDSBuffer->Unlock(pWriteData, WriteDataLength, nullptr, 0);
	delete[] pWaveData;

	*_pIndex = m_pSound.size();
	m_pSound.push_back(pDSBuffer);

	return true;
}

void Lib::DSoundManager::ReleaseSound(int _index)
{
	if (m_pSound[_index] != nullptr)
	{
		m_pSound[_index]->Release();
		m_pSound[_index] = nullptr;
	}
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

bool Lib::DSoundManager::ReadWave(LPSTR _pFileName, WAVEFORMATEX* _pWaveFormat, BYTE** _pWaveData, DWORD* _pWaveSize)
{
	if (_pFileName == nullptr)
	{
		return false;
	}

	HMMIO hMmio = nullptr;
	MMIOINFO MmioInfo;
	ZeroMemory(&MmioInfo, sizeof(MMIOINFO));
	hMmio = mmioOpen(_pFileName, &MmioInfo, MMIO_READ);
	if (!hMmio)
	{
		return false;
	}

	// RIFFチャンク検索
	MMRESULT Result;
	MMCKINFO RiffChunk;
	RiffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	Result = mmioDescend(hMmio, &RiffChunk, nullptr, MMIO_FINDRIFF);
	if (Result != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	// fmtチャンク検索
	MMCKINFO FormatChunk;
	FormatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	Result = mmioDescend(hMmio, &FormatChunk, &RiffChunk, MMIO_FINDCHUNK);
	if (Result != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	DWORD FormatSize = FormatChunk.cksize;
	DWORD WaveDataSize = mmioRead(hMmio, reinterpret_cast<HPSTR>(_pWaveFormat), FormatSize);
	if (WaveDataSize != FormatSize)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	mmioAscend(hMmio, &FormatChunk, 0);

	// dataチャンク検索
	MMCKINFO DataChunk;
	DataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	Result = mmioDescend(hMmio, &DataChunk, &RiffChunk, MMIO_FINDCHUNK);
	if (Result != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	*_pWaveData = new BYTE[DataChunk.cksize];
	WaveDataSize = mmioRead(hMmio, reinterpret_cast<HPSTR>(*_pWaveData), DataChunk.cksize);
	if (WaveDataSize != DataChunk.cksize)
	{
		delete[] * _pWaveData;
		mmioClose(hMmio, 0);
		return false;
	}

	*_pWaveSize = WaveDataSize;
	mmioClose(hMmio, 0);

	return true;
}
