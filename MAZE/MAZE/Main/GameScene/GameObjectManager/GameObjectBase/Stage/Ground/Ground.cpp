/**
 * @file   Ground.cpp
 * @brief  Groundクラスの実装
 * @author kotani
 */
#include "Ground.h"
#include "Dx11\DX11Manager.h"
#include "Window\Window.h"
#include "Texture\TextureManager.h"
#include "..\..\..\..\..\ResourceId.h"

Ground::Ground()
{
	InitializeTask(1, 1);
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
}

Ground::~Ground()
{
	FinalizeTask();
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Ground::Update()
{
}

void Ground::Draw()
{
	Lib::VECTOR2 pos;
	RECT windowSize = SINGLETON_INSTANCE(Lib::Window).GetWindowSize();
	pos.x = static_cast<float>((windowSize.right / 2) - (64 * (STAGE_WIDTH / 2)));
	pos.y = static_cast<float>((windowSize.bottom / 2) - (64 * (STAGE_HEIGHT / 2)));

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		pos.x = static_cast<float>((windowSize.right / 2) - (64 * (STAGE_WIDTH / 2)));
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if (m_Stage.Data[i][j] == 1)
			{
				m_pVertex->Draw(pos,m_pUvController->GetUV());
			}
			pos.x += 64.f;
		}
		pos.y += 64.f;
	}
}
