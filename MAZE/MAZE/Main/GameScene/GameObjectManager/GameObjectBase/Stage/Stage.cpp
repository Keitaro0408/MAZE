/**
 * @file   Stage.cpp
 * @brief  Stageクラスの実装
 * @author kotani
 */
#include "Stage.h"
#include "StageEventListener.h"
#include "Ground\Ground.h"
#include "Ladder\Ladder.h"
#include "Door\Door.h"
#include "Needle\Needle.h"
#include "Coin\Coin.h"
#include "Cover\Cover.h"
#include "Trampoline\Trampoline.h"

#include "TaskManager\TaskManager.h"
#include "Window\Window.h"
#include "Texture\TextureManager.h"
#include "Event\EventManager.h"


Stage::Stage() :
m_SpinSpeed(0.f),
m_Angle(0.f),
m_SpinType(NON_SPIN),
m_TextureIndex(0)
{
	m_Uv[0] = Lib::VECTOR2(0, 0);
	m_Uv[1] = Lib::VECTOR2(1, 0);
	m_Uv[2] = Lib::VECTOR2(0, 1);
	m_Uv[3] = Lib::VECTOR2(1, 1);
	CreateShaderResorceView();
	
	m_pGameObjectBase[0] = Lib::MakeUnique<Ground>();
	m_pGameObjectBase[1] = Lib::MakeUnique<Ladder>();
	m_pGameObjectBase[2] = Lib::MakeUnique<Door>();
	m_pGameObjectBase[3] = Lib::MakeUnique<Needle>();
	m_pGameObjectBase[4] = Lib::MakeUnique<Coin>();
	m_pGameObjectBase[5] = Lib::MakeUnique<Cover>();
	m_pGameObjectBase[6] = Lib::MakeUnique<Trampoline>();

	m_pVertex = Lib::MakeUnique<Lib::Vertex2D>(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Initialize(Lib::VECTOR2(1920, 1080),
		m_Uv);
	
	m_pStageEventListener = Lib::MakeUnique<StageEventListener>(this);
	InitializeTask(2);
}

Stage::~Stage()
{
	FinalizeTask();
	m_pVertex->Finalize();
	m_pTex->Release();
	m_pTexRTV->Release();
	m_pTexSRV->Release();
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Stage::Update()
{
	for (unsigned i = 0; i < m_pGameObjectBase.size(); i++)
	{
		m_pGameObjectBase[i]->Update();
	}
	if (!SINGLETON_INSTANCE(GamePlayManager).GetIsSpin()) return;
	GamePlayManager::SELECT_STAGE stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();
	float stageAngle = SINGLETON_INSTANCE(GamePlayManager).GetStageAngle();
	//if (m_Angle <= -360 ||
	//	m_Angle >= 360)
	//{
	//	m_Angle = 0;
	//}

	switch (m_SpinType)
	{
	case RIGHT_SPIN:
		m_Angle += m_SpinSpeed;
		m_AddAngleCount += m_SpinSpeed;
		if ((static_cast<int>(m_AddAngleCount) % 90) == 0)
		{
			m_Angle = stageAngle;
			stage = SINGLETON_INSTANCE(GamePlayManager).RightSpin(stage);
			SINGLETON_INSTANCE(GamePlayManager).SetIsSpin(false);
		}
		break;
	case LEFT_SPIN:
		m_Angle += m_SpinSpeed;
		m_AddAngleCount += m_SpinSpeed;
		if ((static_cast<int>(m_AddAngleCount) % 90) == 0)
		{
			m_Angle = stageAngle;
			stage = SINGLETON_INSTANCE(GamePlayManager).LeftSpin(stage);
			SINGLETON_INSTANCE(GamePlayManager).SetIsSpin(false);
		}
		break;
	case REVERSAL_SPIN:
		m_Angle += m_SpinSpeed;
		m_AddAngleCount += m_SpinSpeed;

		if ((static_cast<int>(m_AddAngleCount) % 180) == 0)
		{
			m_Angle = stageAngle;
			stage = SINGLETON_INSTANCE(GamePlayManager).LeftSpin(stage);
			stage = SINGLETON_INSTANCE(GamePlayManager).LeftSpin(stage);
			SINGLETON_INSTANCE(GamePlayManager).SetIsSpin(false);
		}
		break;
	case INITIALIZE_SPIN:
		float tmpAngle = m_Angle;
		if (m_Angle < 0)
		{
			m_Angle += m_SpinSpeed;
		}
		else
		{
			m_Angle -= m_SpinSpeed;
		}
		if (m_Angle >= 0 && tmpAngle <= 0 || 
			m_Angle <= 0 && tmpAngle >= 0)
		{	
			m_Angle = 0;
			SINGLETON_INSTANCE(GamePlayManager).SetIsSpin(false);
		}
		break;
	}
}

void Stage::Draw()
{
	Lib::VECTOR2 windowSize;
	windowSize.x = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().right);
	windowSize.y = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().bottom);

	SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext()->OMSetRenderTargets(1, &m_pTexRTV, false);
	float ClearColor[4] = { 0, 0, 0, 0 };
	SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext()->ClearRenderTargetView(m_pTexRTV, ClearColor);

	for (unsigned i = 0; i < m_pGameObjectBase.size(); i++)
	{
		m_pGameObjectBase[i]->Draw();
	}

	SINGLETON_INSTANCE(Lib::DX11Manager).SetDepthStencilTest(false);
	m_pVertex->SetTexture(m_pTexSRV);
	m_pVertex->Draw(windowSize / 2, m_Uv, 1.f, Lib::VECTOR2(1, 1), m_Angle);
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void Stage::CreateShaderResorceView()
{
	ID3D11Device* device = SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice();

	//レンダリングターゲットになるテクスチャーを作成
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = 1920;
	desc.Height = 1080;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	device->CreateTexture2D(&desc, NULL, &m_pTex);

	D3D11_RENDER_TARGET_VIEW_DESC rdesc;
	ZeroMemory(&rdesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	rdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rdesc.Texture2DArray.MipSlice = 0;
	device->CreateRenderTargetView(m_pTex, &rdesc, &m_pTexRTV);

	//SRV作成
	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;
	device->CreateShaderResourceView(m_pTex, &SRVDesc, &m_pTexSRV);
}
