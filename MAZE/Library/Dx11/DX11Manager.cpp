/**
 * @file   DX11Manager.cpp
 * @brief  DX11Managerクラスの実装
 * @author kotani
 */
#include "DX11Manager.h"

Lib::DX11Manager* Lib::DX11Manager::m_pDX11Manager = nullptr;
float Lib::DX11Manager::m_ClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };


Lib::DX11Manager::DX11Manager() :
m_pDevice(nullptr),
m_pDeviceContext(nullptr),
m_pDXGI(nullptr),
m_pAdapter(nullptr),
m_pDXGIFactory(nullptr),
m_pDXGISwapChain(nullptr),
m_pBackBuffer(nullptr),
m_pRenderTargetView(nullptr),
m_pDepthStencilBuffer(nullptr),
m_pDepthStencilView(nullptr),
m_pRasterizerState(nullptr),
m_hWnd(nullptr)
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool Lib::DX11Manager::Initialize(HWND _hWnd, RECT _windowSize)
{
	if (m_pDevice != nullptr)
	{
		OutputDebugString(TEXT("m_pDeviceDX11Managerクラスはすでに初期化されています"));
		return false;
	}

	m_hWnd = _hWnd;
	m_WindowRect.right = _windowSize.right;
	m_WindowRect.bottom = _windowSize.bottom;

	if (!InitDevice())
	{
		OutputDebugString(TEXT("InitDeviceに失敗しました"));
		return false;
	}

	if (!InitDisplay())
	{
		OutputDebugString(TEXT("InitDisplayに失敗しました"));
		ReleaseDevice();
		return false;
	}
	OutputDebugString(TEXT("DX11Managerの初期化に成功\n"));

	return true;
}

void Lib::DX11Manager::Finalize()
{
	ReleaseDisplay();
	ReleaseDevice();
}

void Lib::DX11Manager::BeginScene()
{
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, m_ClearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Lib::DX11Manager::EndScene()
{
	m_pDXGISwapChain->Present(0, 0);
}

void Lib::DX11Manager::SetDepthStencilTest(bool _isStencil)
{
	if (_isStencil)
	{
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
	}
	else
	{
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);
	}
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

bool Lib::DX11Manager::InitDevice()
{
#ifdef	_DEBUG
	if (FAILED(D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&m_pDevice,
		nullptr,
		&m_pDeviceContext)))
	{
		OutputDebugString(TEXT("D3D11CreateDeviceに失敗しました"));
		return false;
	}
#else
	if (FAILED(D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&m_pDevice,
		nullptr,
		&m_pDeviceContext)))
	{
		OutputDebugString(TEXT("D3D11CreateDeviceに失敗しました"));
		return false;
	}
#endif
	return true;
}

bool Lib::DX11Manager::InitDisplay()
{
	if (FAILED(m_pDevice->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&m_pDXGI))))
	{
		OutputDebugString(TEXT("DX11のインターフェイスの取得に失敗しました"));
		return false;
	}

	if (FAILED(m_pDXGI->GetAdapter(&m_pAdapter)))
	{
		OutputDebugString(TEXT("DX11のアダプターの取得に失敗しました"));
		m_pDXGI->Release();
		return false;
	}

	m_pAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&m_pDXGIFactory));
	if (m_pDXGIFactory == nullptr)
	{
		OutputDebugString(TEXT("DX11のファクトリーの取得に失敗しました"));
		m_pAdapter->Release();
		m_pDXGI->Release();
		return false;
	}

	if (FAILED(m_pDXGIFactory->MakeWindowAssociation(m_hWnd, 0)))
	{
		OutputDebugString(TEXT("フルスクリーン化に失敗しました"));
		m_pDXGIFactory->Release();
		m_pAdapter->Release();
		m_pDXGI->Release();
		return false;
	}

	m_DXGISwapChainDesc.BufferDesc.Width = m_WindowRect.right;
	m_DXGISwapChainDesc.BufferDesc.Height = m_WindowRect.bottom;
	m_DXGISwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	m_DXGISwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	m_DXGISwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_DXGISwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	m_DXGISwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	m_DXGISwapChainDesc.SampleDesc.Count = 1;
	m_DXGISwapChainDesc.SampleDesc.Quality = 0;
	m_DXGISwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_DXGISwapChainDesc.BufferCount = 1;
	m_DXGISwapChainDesc.OutputWindow = m_hWnd;
	m_DXGISwapChainDesc.Windowed = TRUE;
	m_DXGISwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	m_DXGISwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if (FAILED(m_pDXGIFactory->CreateSwapChain(m_pDevice, &m_DXGISwapChainDesc, &m_pDXGISwapChain)))
	{
		OutputDebugString(TEXT("スワップチェインの作成に失敗しました"));
		m_pDXGIFactory->Release();
		m_pAdapter->Release();
		m_pDXGI->Release();
		return false;
	}

	if (FAILED(m_pDXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_pBackBuffer))))
	{
		OutputDebugString(TEXT("スワップチェインのバックバッファ取得に失敗しました"));
		m_pDXGISwapChain->Release();
		m_pDXGIFactory->Release();
		m_pAdapter->Release();
		m_pDXGI->Release();
		return false;
	}

	OutputDebugString(TEXT("スワップチェインのバックバッファ取得に成功しました\n"));

	if (FAILED(m_pDevice->CreateRenderTargetView(m_pBackBuffer, nullptr, &m_pRenderTargetView)))
	{
		OutputDebugString(TEXT("描画ターゲット生成に失敗しました"));
		m_pBackBuffer->Release();
		m_pDXGISwapChain->Release();
		m_pDXGIFactory->Release();
		m_pAdapter->Release();
		m_pDXGI->Release();
		return false;
	}

	OutputDebugString(TEXT("描画ターゲット生成に成功しました\n"));


	m_DepthDesc.Width = m_WindowRect.right;
	m_DepthDesc.Height = m_WindowRect.bottom;
	m_DepthDesc.MipLevels = 1;
	m_DepthDesc.ArraySize = 1;
	m_DepthDesc.Format = DXGI_FORMAT_D32_FLOAT;
	m_DepthDesc.SampleDesc.Count = 1;
	m_DepthDesc.SampleDesc.Quality = 0;
	m_DepthDesc.Usage = D3D11_USAGE_DEFAULT;
	m_DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	m_DepthDesc.CPUAccessFlags = 0;
	m_DepthDesc.MiscFlags = 0;

	if (FAILED(m_pDevice->CreateTexture2D(&m_DepthDesc, nullptr, &m_pDepthStencilBuffer)))
	{
		OutputDebugString(TEXT("ステンシルビュー生成に失敗しました"));
		m_pRenderTargetView->Release();
		m_pBackBuffer->Release();
		m_pDXGISwapChain->Release();
		m_pDXGIFactory->Release();
		m_pAdapter->Release();
		m_pDXGI->Release();
		return false;
	}

	OutputDebugString(TEXT("ステンシルビュー生成に成功しました\n"));

	if (FAILED(m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, nullptr, &m_pDepthStencilView)))
	{
		OutputDebugString(TEXT("ステンシルバッファ生成に失敗しました"));
		m_pDepthStencilBuffer->Release();
		m_pRenderTargetView->Release();
		m_pBackBuffer->Release();
		m_pDXGISwapChain->Release();
		m_pDXGIFactory->Release();
		m_pAdapter->Release();
		m_pDXGI->Release();
		return false;
	}

	OutputDebugString(TEXT("ステンシルバッファ生成に成功しました\n"));

	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);


	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.Width = static_cast<float>(m_WindowRect.right);
	m_ViewPort.Height = static_cast<float>(m_WindowRect.bottom);
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
	m_pDeviceContext->RSSetViewports(1, &m_ViewPort);

	m_RasterizerDesc.FillMode = D3D11_FILL_SOLID;
	m_RasterizerDesc.CullMode = D3D11_CULL_BACK;
	m_RasterizerDesc.FrontCounterClockwise = FALSE;
	m_RasterizerDesc.DepthBias = 0;
	m_RasterizerDesc.DepthBiasClamp = 0.0f;
	m_RasterizerDesc.SlopeScaledDepthBias = 0.0f;
	m_RasterizerDesc.DepthClipEnable = FALSE;
	m_RasterizerDesc.ScissorEnable = FALSE;
	m_RasterizerDesc.MultisampleEnable = FALSE;
	m_RasterizerDesc.AntialiasedLineEnable = FALSE;

	if (FAILED(m_pDevice->CreateRasterizerState(&m_RasterizerDesc, &m_pRasterizerState)))
	{
		m_pDepthStencilView->Release();
		m_pDepthStencilBuffer->Release();
		m_pRenderTargetView->Release();
		m_pBackBuffer->Release();
		m_pDXGISwapChain->Release();
		m_pDXGIFactory->Release();
		m_pAdapter->Release();
		m_pDXGI->Release();
		OutputDebugString(TEXT("RasterizerStateの生成に失敗しました"));
		return false;
	}

	OutputDebugString(TEXT("RasterizerStateの状態の生成に成功しました\n"));
	m_pDeviceContext->RSSetState(m_pRasterizerState);

	return true;
}

void Lib::DX11Manager::ReleaseDevice()
{
	if (m_pDeviceContext != nullptr)
	{
		m_pDeviceContext->Release();
		m_pDeviceContext = nullptr;
	}

	if (m_pDevice != nullptr)
	{
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
}

void Lib::DX11Manager::ReleaseDisplay()
{
	if (m_pRasterizerState != nullptr)
	{
		m_pRasterizerState->Release();
		m_pRasterizerState = nullptr;
	}

	if (m_pDepthStencilView != nullptr)
	{
		m_pDepthStencilView->Release();
		m_pDepthStencilView = nullptr;
	}

	if (m_pDepthStencilBuffer != nullptr)
	{
		m_pDepthStencilBuffer->Release();
		m_pDepthStencilBuffer = nullptr;
	}

	if (m_pRenderTargetView != nullptr)
	{
		m_pRenderTargetView->Release();
		m_pRenderTargetView = nullptr;
	}

	if (m_pBackBuffer != nullptr)
	{
		m_pBackBuffer->Release();
		m_pBackBuffer = nullptr;
	}

	if (m_pDXGISwapChain != nullptr)
	{
		m_pDXGISwapChain->Release();
		m_pDXGISwapChain = nullptr;
	}

	if (m_pDXGIFactory != nullptr)
	{
		m_pDXGIFactory->Release();
		m_pDXGIFactory = nullptr;
	}

	if (m_pAdapter != nullptr)
	{
		m_pAdapter->Release();
		m_pAdapter = nullptr;
	}

	if (m_pDXGI != nullptr)
	{
		m_pDXGI->Release();
		m_pDXGI = nullptr;
	}
}
