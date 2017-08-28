/**
 * @file   Window.cpp
 * @brief  Windowクラスの実装
 * @author kotani
 */
#include "Window.h"

LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_CLOSE:
		if (MessageBox(_hwnd, TEXT("終わりますか？"), TEXT("終了"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(_hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_KEYDOWN:
		switch (static_cast<CHAR>(_wParam))
		{
		case VK_ESCAPE:
			if (MessageBox(_hwnd, TEXT("終わりますか？"), TEXT("終了"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				DestroyWindow(_hwnd);
			}
			break;
		}
		break;
	default:
		return DefWindowProc(_hwnd, _message, _wParam, _lParam);
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

HRESULT Lib::Window::DispWindow(INT _width, INT _height, LPCTSTR _windowName)
{
	m_WindowSize.right = _width;
	m_WindowSize.bottom = _height;

	// ウィンドウの定義
	WNDCLASSEX  Wndclass;
	ZeroMemory(&Wndclass, sizeof(Wndclass));
	Wndclass.cbSize = sizeof(Wndclass);
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WindowProc;
	Wndclass.hInstance = m_hInstance;
	Wndclass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	Wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	Wndclass.lpszClassName = TEXT(_windowName);
	Wndclass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	RegisterClassEx(&Wndclass);

	
	//ウィンドウの作成
	m_hWnd = CreateWindow(
		_windowName,
		_windowName,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME | WS_VISIBLE,
		0,
		0,
		_width,
		_height,
		nullptr,
		nullptr,
		m_hInstance,
		nullptr);

	if (!m_hWnd)
	{
		return E_FAIL;
	}

	RECT rw, rc;
	GetWindowRect(m_hWnd, &rw); // ウィンドウ全体のサイズ
	GetClientRect(m_hWnd, &rc); // クライアント領域のサイズ

	int new_width = (rw.right - rw.left) - (rc.right - rc.left) + _width;
	int new_height = (rw.bottom - rw.top) - (rc.bottom - rc.top) + _height;

	SetWindowPos(m_hWnd, nullptr, 0, 0, new_width, new_height, SWP_NOMOVE | SWP_NOZORDER);
	//ウインドウの表示
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

HRESULT Lib::Window::DispWindow(INT _width, INT _height, LPCTSTR _windowName, LPCTSTR _iconName)
{
	m_hInstance = GetModuleHandle(nullptr);

	// ウィンドウの定義
	WNDCLASSEX  Wndclass;
	ZeroMemory(&Wndclass, sizeof(Wndclass));
	Wndclass.cbSize = sizeof(Wndclass);
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = WindowProc;
	Wndclass.hInstance = m_hInstance;
	//アイコン読み込み
	Wndclass.hIcon = (HICON)LoadImage(nullptr, _iconName, IMAGE_ICON, 0, 0, LR_SHARED | LR_LOADFROMFILE);
	Wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	Wndclass.lpszClassName = _windowName;
	Wndclass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	RegisterClassEx(&Wndclass);

	//ウィンドウの作成
	m_hWnd = CreateWindow(
		_windowName,
		_windowName,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME | WS_VISIBLE,
		0,
		0,
		_width,
		_height,
		nullptr,
		nullptr,
		m_hInstance,
		nullptr);

	if (!m_hWnd)
	{
		return E_FAIL;
	}
	//ウインドウの表示
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

void Lib::Window::ChangeWindowSize(int _width, int _hight)
{
	RECT rw, rc;
	GetWindowRect(m_hWnd, &rw); // ウィンドウ全体のサイズ
	GetClientRect(m_hWnd, &rc); // クライアント領域のサイズ

	int new_width = (rw.right - rw.left) - (rc.right - rc.left) + _width;
	int new_height = (rw.bottom - rw.top) - (rc.bottom - rc.top) + _hight;

	SetWindowPos(m_hWnd, nullptr, 0, 0, new_width, new_height, SWP_NOMOVE | SWP_NOZORDER);
}
