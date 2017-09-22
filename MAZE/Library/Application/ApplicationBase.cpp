/**
 * @file   ApplicationBase.cpp
 * @brief  ApplicationBaseクラスの実装
 * @author kotani
 */
#include <crtdbg.h>
#include "ApplicationBase.h"
#include "../Window/Window.h"
#include "../Dx11/DX11Manager.h"
#include "../Sound/DSoundManager.h"
#include "../DxInput/DXInputDevice.h"
#include "../Texture/TextureManager.h"
#include "../Application/ApplicationBase.h"
#include "../Shader/ShaderManager.h"
#include "../Event/EventManager.h"
#include "../TaskManager/TaskManager.h"
#include "../XInput/XInput.h"
#include "../SceneManager/SceneManager.h"

Lib::ApplicationBase* Lib::ApplicationBase::m_pInstance = nullptr;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	return Lib::ApplicationBase::GetInstance()->Boot();
}

namespace Lib
{
	ApplicationBase::ApplicationBase(LPCTSTR _appName, int _windowWidth, int _windowHeight) :
		m_AppName(_appName),
		m_WindowWidth(_windowWidth),
		m_WindowHeight(_windowHeight),
		m_RefreshRate(60)
	{
		::ImmDisableIME(NULL);
		m_pInstance = this;
	}

	ApplicationBase::~ApplicationBase()
	{
		SINGLETON_DELETE(Lib::Window);
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	int ApplicationBase::Boot()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		SINGLETON_CREATE(Lib::Window);
		SINGLETON_INSTANCE(Lib::Window).DispWindow(m_WindowWidth,m_WindowHeight, m_AppName);

		InitLib();
		Initialize();

		MSG Msg;
		ZeroMemory(&Msg, sizeof(Msg));
		while (Msg.message != WM_QUIT)
		{

			if (PeekMessage(&Msg, nullptr, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
			else
			{
				if (MainLoop())
				{
					break;
				}
			}
		}
		/* 先にサブクラスからデストラクタが実行されるのでここで解放する */
		Finalize();
		ReleaseLib();
		return 0;
	}

	bool ApplicationBase::MainLoop()
	{
		static LARGE_INTEGER Time1;
		LARGE_INTEGER Frq, Time2;
		double TotalTime = 0;
		QueryPerformanceFrequency(&Frq);
		double MicroSec = 1000000 / (double)Frq.QuadPart;

		while (TotalTime<(1000000 / m_RefreshRate))
		{
			QueryPerformanceCounter(&Time2);
			TotalTime = (Time2.QuadPart - Time1.QuadPart)*MicroSec;
		}
		QueryPerformanceCounter(&Time1);
		return SINGLETON_INSTANCE(Lib::SceneManager).Execute();
	}

	void ApplicationBase::InitLib()
	{
		SINGLETON_CREATE(Lib::TaskManager);
		
		SINGLETON_CREATE(Lib::XInput);

		HWND hWnd = SINGLETON_INSTANCE(Lib::Window).GetWindowHandle();

		//Directx11関係
		SINGLETON_CREATE(Lib::DX11Manager);
		SINGLETON_INSTANCE(Lib::DX11Manager).Initialize(hWnd,
			SINGLETON_INSTANCE(Lib::Window).GetWindowSize());

		//DirectInput関係
		SINGLETON_CREATE(Lib::DXInputDevice);
		SINGLETON_INSTANCE(Lib::DXInputDevice).Initialize(hWnd);

		SINGLETON_CREATE(Lib::MouseDevice);
		SINGLETON_INSTANCE(Lib::MouseDevice).Initialize(
			SINGLETON_INSTANCE(Lib::DXInputDevice).GetInputDevice(), hWnd);

		SINGLETON_CREATE(Lib::KeyDevice);
		SINGLETON_INSTANCE(Lib::KeyDevice).Initialize(
			SINGLETON_INSTANCE(Lib::DXInputDevice).GetInputDevice(), hWnd);

		SINGLETON_CREATE(Lib::DSoundManager);
		SINGLETON_INSTANCE(Lib::DSoundManager).Initialize(hWnd);

		SINGLETON_CREATE(Lib::TextureManager);
		SINGLETON_INSTANCE(Lib::TextureManager).
			Initialize(SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice());

		SINGLETON_CREATE(Lib::ShaderManager);
		SINGLETON_INSTANCE(Lib::ShaderManager).
			Initialize(SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice());

		SINGLETON_CREATE(Lib::EventManager);

		SINGLETON_CREATE(Lib::SceneManager);
	}

	void ApplicationBase::ReleaseLib()
	{
		SINGLETON_DELETE(Lib::SceneManager);

		SINGLETON_DELETE(Lib::EventManager);

		SINGLETON_DELETE(Lib::ShaderManager);

		SINGLETON_DELETE(Lib::TextureManager);

		SINGLETON_INSTANCE(Lib::DSoundManager).Finalize();
		SINGLETON_DELETE(Lib::DSoundManager);

		SINGLETON_INSTANCE(Lib::KeyDevice).Finalize();
		SINGLETON_DELETE(Lib::KeyDevice);

		SINGLETON_INSTANCE(Lib::MouseDevice).Finalize();
		SINGLETON_DELETE(Lib::MouseDevice);

		SINGLETON_INSTANCE(Lib::DXInputDevice).Finalize();
		SINGLETON_DELETE(Lib::DXInputDevice);

		SINGLETON_INSTANCE(Lib::DX11Manager).Finalize();
		SINGLETON_DELETE(Lib::DX11Manager);

		SINGLETON_DELETE(Lib::XInput);

		SINGLETON_DELETE(Lib::TaskManager);

		SINGLETON_DELETE(Lib::Window);
	}
}

