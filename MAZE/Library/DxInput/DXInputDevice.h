/**
 * @file   DXInputDevice.h
 * @brief  DXInputDeviceクラスのヘッダファイル
 * @author kotani
 */
#ifndef DXINPUTDEVICE_H
#define DXINPUTDEVICE_H
#include "Mouse/MouseDevice.h"
#include "KeyBoard/KeyDevice.h"
#include "..\Singleton.h"

namespace Lib
{
	class DXInputDevice
	{
		friend Singleton<DXInputDevice>;
	public:
		/**
		 * 初期化処理
		 */
		bool Initialize(HWND _hWnd);

		/**
		 * 開放処理
		 */
		void Finalize();

		inline LPDIRECTINPUT8 GetInputDevice()
		{
			return m_pDInput8;
		}

	private:
		DXInputDevice() :
			m_pDInput8(nullptr),
			m_hWnd(nullptr){};

		~DXInputDevice(){};

		LPDIRECTINPUT8	m_pDInput8;
		HWND			m_hWnd;

	};
}


#endif
