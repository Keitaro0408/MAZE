/**
 * @file   KeyDevice.cpp
 * @brief  KeyDeviceクラスの実装
 * @author kotani
 */
#include "KeyDevice.h"


Lib::KeyDevice::KeyDevice()
{
	for (int i = 0; i < 256; i++)
	{
		m_pDIKeyState[i] = 0;
		m_pOldDIKeyState[i] = 0;
	}
}

//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool Lib::KeyDevice::Initialize(LPDIRECTINPUT8 _pDInput8, HWND _hWnd)
{
	if (m_pDInput8 != nullptr)
	{
		MessageBox(_hWnd, TEXT("KeyDeviceクラスは既に初期化されています"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	m_pDInput8 = _pDInput8;
	m_hWnd = _hWnd;

	if (m_pDInput8 == nullptr)
	{
		MessageBox(m_hWnd, TEXT("DirectInput8オブジェクトが有効ではありません"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (FAILED(m_pDInput8->CreateDevice(GUID_SysKeyboard, &m_pDInputDevice8, nullptr)))
	{
		MessageBox(m_hWnd, TEXT("DirectInput8キーデバイスの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (FAILED(m_pDInputDevice8->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(m_hWnd, TEXT("DirectInput8キーデバイスのデータフォーマットの設定に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDInputDevice8->Release();
		return false;
	}

	DIPROPDWORD DiProp;
	DiProp.diph.dwSize = sizeof(DiProp);
	DiProp.diph.dwHeaderSize = sizeof(DiProp.diph);
	DiProp.diph.dwObj = 0;
	DiProp.diph.dwHow = DIPH_DEVICE;
	DiProp.dwData = 1000;
	if (FAILED(m_pDInputDevice8->SetProperty(DIPROP_BUFFERSIZE, &DiProp.diph)))
	{
		MessageBox(m_hWnd, TEXT("DirectInput8キーデバイスのバッファ設定に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDInputDevice8->Release();
		return false;
	}

	if (FAILED(m_pDInputDevice8->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		MessageBox(m_hWnd, TEXT("DirectInput8キーデバイスの協調レベルの設定に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDInputDevice8->Release();
		return false;
	}

	m_pDInputDevice8->Acquire();

	OutputDebugString(TEXT("DirectInputのKeyDeviceの初期化に成功した\n"));

	return true;
}

void Lib::KeyDevice::Finalize()
{
	if (m_pDInputDevice8 != nullptr)
	{
		m_pDInputDevice8->Release();
		m_pDInputDevice8 = nullptr;
		m_pDInput8 = nullptr;
		OutputDebugString(TEXT("DirectInputのKeyDeviceを解放しました\n"));
	}
}

void Lib::KeyDevice::Update()
{
	HRESULT hr = m_pDInputDevice8->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		m_pDInputDevice8->GetDeviceState(sizeof(m_pDIKeyState), &m_pDIKeyState);
		
		for (auto itr = m_SetKeyState.begin(); itr != m_SetKeyState.end(); itr++)
		{
			for (auto itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++)
			{
				if (m_pDIKeyState[itr2->DIKeyState] & 0x80)
				{
					if (m_pOldDIKeyState[itr2->DIKeyState] == KEY_OFF)
					{
						itr2->KeyData = KEY_PUSH;
					}
					else
					{
						itr2->KeyData = KEY_ON;
					}
					m_pOldDIKeyState[itr2->DIKeyState] = KEY_ON;
				}
				else
				{
					if (m_pOldDIKeyState[itr2->DIKeyState] == KEY_ON)
					{
						itr2->KeyData = KEY_RELEASE;
					}
					else
					{
						itr2->KeyData = KEY_OFF;
					}
					m_pOldDIKeyState[itr2->DIKeyState] = KEY_OFF;
				}
			}
		}
	}
}

void Lib::KeyDevice::KeyCheckEntry(std::string _keyName, int _dik)
{
	KEYDATA keyData;
	keyData.DIKeyState = _dik;
	keyData.KeyData = Lib::KEY_OFF;
	m_SetKeyState[_keyName].push_back(keyData);
}

bool Lib::KeyDevice::AllMatchKeyCheck(std::string _keyName, KEYSTATE _keyState)
{
	for (auto itr = m_SetKeyState[_keyName].begin(); itr != m_SetKeyState[_keyName].end(); itr++)
	{
		if (itr->KeyData != _keyState)
		{
			return false;
		}
	}
	return true;
}

bool Lib::KeyDevice::AnyMatchKeyCheck(std::string _keyName, KEYSTATE _keyState)
{
	for (auto itr = m_SetKeyState[_keyName].begin(); itr != m_SetKeyState[_keyName].end(); itr++)
	{
		if (itr->KeyData == _keyState)
		{
			return true;
		}
	}
	return false;
}
