/**
 * @file   Ground.cpp
 * @brief  Groundクラスの実装
 * @author kotani
 */
#include "Ground.h"
#include "Window\Window.h"
#include "Texture\TextureManager.h"
#include "..\..\..\..\..\ResourceId.h"
#include "Math\Math.h"

Ground::Ground()
{
	m_Stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();

	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim","GreenGround");

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
	m_pVertex->Finalize();
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
	Lib::VECTOR2 windowSize;
	windowSize.x = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().right);
	windowSize.y = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().bottom);

	pos.x = static_cast<float>((windowSize.x / 2) - (64 * (STAGE_WIDTH / 2)));
	pos.y = static_cast<float>((windowSize.y / 2) - (64 * (STAGE_HEIGHT / 2)));

	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		pos.x = static_cast<float>((windowSize.x / 2) - (64 * (STAGE_WIDTH / 2)));
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if ((m_Stage.Data[i][j] % 10) == 1)
			{
				m_pVertex->Draw(pos, m_pUvController->GetUV(), 1.f, Lib::VECTOR2(1, 1), 0);
			}
			pos.x += 64.f;
		}
		pos.y += 64.f;
	}
}
