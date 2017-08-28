/**
 * @file   DXInputDevice.cpp
 * @brief  DXInputDeviceクラスの実装
 * @author kotani
 */
#include "DXInputDevice.h"


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool Lib::DXInputDevice::Initialize(HWND _hWnd)
{
	if (m_pDInput8 != nullptr)
	{
		MessageBox(_hWnd, TEXT("m_pDInput8の中身は空ではありません"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (FAILED(DirectInput8Create(
		GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		reinterpret_cast<void**>(&m_pDInput8),
		nullptr)))
	{
		MessageBox(_hWnd, TEXT("DirectInput8オブジェクトの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	m_hWnd = _hWnd;

	OutputDebugString(TEXT("DirectInput8オブジェクトの生成に成功\n"));

	return true;
}

void Lib::DXInputDevice::Finalize()
{
	if (m_pDInput8 != nullptr)
	{
		m_pDInput8->Release();
		m_pDInput8 = nullptr;
	}
}
