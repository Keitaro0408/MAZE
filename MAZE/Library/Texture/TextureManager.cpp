/**
 * @file   TextureManager.cpp
 * @brief  TextureManagerクラスの実装
 * @author kotani
 */
#include "TextureManager.h"

Lib::TextureManager::~TextureManager()
{
}

void Lib::TextureManager::Initialize(ID3D11Device* _pDevice)
{
	m_pDevice = _pDevice;
}

bool Lib::TextureManager::Load(LPCTSTR _pFileName, int* _index)
{
	ID3D11ShaderResourceView* pResourceView = nullptr;
	D3DX11_IMAGE_LOAD_INFO LoadInfo;
	ZeroMemory(&LoadInfo, sizeof(LoadInfo));
	LoadInfo.Width = D3DX11_DEFAULT;
	LoadInfo.Height = D3DX11_DEFAULT;
	LoadInfo.Depth = D3DX11_DEFAULT;
	LoadInfo.FirstMipLevel = D3DX11_DEFAULT;
	LoadInfo.MipLevels = 1;
	LoadInfo.Usage = D3D11_USAGE_DEFAULT;
	LoadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	LoadInfo.CpuAccessFlags = 0;
	LoadInfo.MiscFlags = 0;
	LoadInfo.Format = DXGI_FORMAT_FROM_FILE;
	LoadInfo.Filter = D3DX11_FILTER_POINT;
	LoadInfo.MipFilter = D3DX11_FILTER_POINT;
	LoadInfo.pSrcInfo = nullptr;

	if (FAILED(D3DX11CreateShaderResourceViewFromFile(
		m_pDevice,
		_pFileName,
		&LoadInfo,
		nullptr,
		&pResourceView,
		nullptr)))
	{
		OutputDebugString(TEXT("テクスチャの読み込みに失敗しました\n"));
		return false;
	}

	*_index = m_pTextureResourceView.size();
	m_pTextureResourceView.push_back(pResourceView);	
	return true;
}

void Lib::TextureManager::ReleaseTexture(int _index)
{
	if (m_pTextureResourceView[_index] != nullptr)
	{
		m_pTextureResourceView[_index]->Release();
		m_pTextureResourceView[_index] = nullptr;
	}
}
