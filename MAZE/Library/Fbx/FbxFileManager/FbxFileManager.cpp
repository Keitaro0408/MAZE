/**
 * @file   FbxFileManager.cpp
 * @brief  FbxFileManagerクラスの実装
 * @author kotani
 */
#include "FbxFileManager.h"
#include "FbxLoader\FbxLoader.h"

const int Lib::FbxFileManager::m_InvalidIndex = 0;


Lib::FbxFileManager::FbxFileManager(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext) :
m_pDevice(_pDevice),
m_pDeviceContext(_pDeviceContext),
m_pFbxLoader(nullptr)
{
	m_pFbxModel.push_back(nullptr);	// 読み込みに失敗した際に参照する値としてnullptrを追加
}

Lib::FbxFileManager::FbxFileManager() :
m_pDevice(nullptr),
m_pDeviceContext(nullptr),
m_pFbxLoader(nullptr)
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool Lib::FbxFileManager::Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext)
{
	FbxFileManager(_pDevice, _pDeviceContext);
	if (m_pFbxLoader != nullptr)
	{
		MessageBox(nullptr, TEXT("既にFbxFileManagerクラスは初期化されています"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	m_pFbxLoader = new FbxLoader(m_pDevice);
	return m_pFbxLoader->Initialize();
}

void Lib::FbxFileManager::Finalize()
{
	if (m_pFbxLoader == nullptr)
	{
		MessageBox(nullptr, TEXT("FbxFileManagerクラスはすでに空です。"), TEXT("エラー"), MB_ICONSTOP);
		return;
	}

	m_pFbxLoader->Release();
	delete m_pFbxLoader;
	m_pFbxLoader = nullptr;
}

bool Lib::FbxFileManager::LoadFbxModel(LPCTSTR _pFileName, int* _pIndex)
{
	FbxModel* pModel = new FbxModel(m_pDevice, m_pDeviceContext);
	if (!m_pFbxLoader->LoadFbxModel(pModel, _pFileName))
	{
		OutputDebugString(TEXT("Fbxモデルの読み込みに失敗しました\n"));
		*_pIndex = m_InvalidIndex;
		delete pModel;
		return false;
	}

	pModel->Initialize();
	*_pIndex = m_pFbxModel.size();
	m_pFbxModel.push_back(pModel);

	return true;
}

void Lib::FbxFileManager::ReleaseFbxModel(int _index)
{
	if (m_pFbxModel[_index] != nullptr)
	{
		m_pFbxModel[_index]->Release();
		delete m_pFbxModel[_index];
		m_pFbxModel[_index] = nullptr;
	}
}
