/**
 * @file   Ground.cpp
 * @brief  Groundクラスの実装
 * @author kotani
 */
#include "Ground.h"
#include "Window\Window.h"
#include "Texture\TextureManager.h"
#include "..\..\..\..\..\ResourceId.h"
#include "Event\EventManager.h"
#include "Math\Math.h"

Ground::Ground() : 
m_SpinSpeed(0.f),
m_Angle(0.f),
m_SpinType(NON_SPIN)
{
	InitializeTask(1,1);
	CreateShaderResorceView();
	m_Uv[0] = Lib::VECTOR2(0, 0);
	m_Uv[1] = Lib::VECTOR2(1, 0);
	m_Uv[2] = Lib::VECTOR2(0, 1);
	m_Uv[3] = Lib::VECTOR2(1, 1);

	m_Stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();

	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim","Ground");

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Initialize(Lib::VECTOR2(64,64),
		m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));

	m_pGroundVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pGroundVertex->Initialize(Lib::VECTOR2(1920, 1080),
		m_Uv);

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("LeftSpin",[this]()
	{
		m_SpinType = LEFT_SPIN;
		m_SpinSpeed = -2;
	});

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("RightSpin", [this]()
	{
		m_SpinType = RIGHT_SPIN;
		m_SpinSpeed = 2;
	});

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("ReversalSpin", [this]()
	{
		m_SpinType = REVERSAL_SPIN;
		m_SpinSpeed = 4;
	});
}

Ground::~Ground()
{
	m_pTex->Release();
	m_pTexRTV->Release();
	m_pTexSRV->Release();

	FinalizeTask();
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Ground::Update()
{
	float stageAngle = SINGLETON_INSTANCE(GamePlayManager).GetStageAngle();
	switch (m_SpinType)
	{
	case RIGHT_SPIN:
		m_Angle += m_SpinSpeed;
		if (stageAngle < m_Angle)
		{
			m_Angle = stageAngle;
			SINGLETON_INSTANCE(GamePlayManager).SetIsSpin(false);
		}
		break;
	case LEFT_SPIN:
		m_Angle += m_SpinSpeed;
		if (stageAngle > m_Angle)
		{
			m_Angle = stageAngle;
			SINGLETON_INSTANCE(GamePlayManager).SetIsSpin(false);
		}
		break;
	case REVERSAL_SPIN:
		m_Angle += m_SpinSpeed * 2;
		if (stageAngle < m_Angle)
		{
			m_Angle = stageAngle;
			SINGLETON_INSTANCE(GamePlayManager).SetIsSpin(false);
		}
		break;
	}

}

void Ground::Draw()
{
	Lib::VECTOR2 pos;
	Lib::VECTOR2 windowSize;
	windowSize.x = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().right);
	windowSize.y = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().bottom);

	pos.x = static_cast<float>((windowSize.x / 2) - (64 * (STAGE_WIDTH / 2)));
	pos.y = static_cast<float>((windowSize.y / 2) - (64 * (STAGE_HEIGHT / 2)));

	SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext()->OMSetRenderTargets(1, &m_pTexRTV, false);
	float ClearColor[4] = { 0, 0, 0, 0 };
	SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext()->ClearRenderTargetView(m_pTexRTV, ClearColor);
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		pos.x = static_cast<float>((windowSize.x / 2) - (64 * (STAGE_WIDTH / 2)));
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if (m_Stage.Data[i][j] == 1)
			{
				m_pVertex->Draw(pos, m_pUvController->GetUV(), 1.f, Lib::VECTOR2(1, 1), 0);
			}
			pos.x += 64.f;
		}
		pos.y += 64.f;
	}

	SINGLETON_INSTANCE(Lib::DX11Manager).SetDepthStencilTest(false);
	m_pGroundVertex->SetTexture(m_pTexSRV);
	m_pGroundVertex->Draw(windowSize / 2, m_Uv, 1.f, Lib::VECTOR2(1, 1), m_Angle);
}

void Ground::CreateShaderResorceView()
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