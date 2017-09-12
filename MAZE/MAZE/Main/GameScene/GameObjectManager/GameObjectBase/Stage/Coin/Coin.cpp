/**
 * @file   Coin.cpp
 * @brief  Coinクラスの実装
 * @author kotani
 */
#include "Coin.h"

#include "Event\EventManager.h"
#include "Window\Window.h"
#include "Texture\TextureManager.h"
#include "Sound\DSoundManager.h"
#include "..\..\..\..\..\ResourceId.h"
#include "Math\Math.h"

Coin::Coin()
{
	m_Stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();

	m_pUvController = Lib::MakeUnique<Lib::AnimUvController>();
	m_pUvController->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "Coin");

	m_pVertex = Lib::MakeUnique<Lib::Vertex2D>(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Initialize(Lib::VECTOR2(64, 64),
		m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("CoinGet", [this]()
	{
		// 各オブジェクトの描画に使っている配列データは回転を反映していないのでここで合わせる
		m_Stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();
		float stageAngle = SINGLETON_INSTANCE(GamePlayManager).GetStageAngle();
		while (stageAngle != 0)
		{
			if (stageAngle < 0)
			{
				stageAngle += 90;
				m_Stage = SINGLETON_INSTANCE(GamePlayManager).RightSpin(m_Stage);
			}
			else if (stageAngle > 0)
			{
				stageAngle -= 90;
				m_Stage = SINGLETON_INSTANCE(GamePlayManager).LeftSpin(m_Stage);
			}
		}
		
		SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(ResourceId::Game::COIN_SE, Lib::DSoundManager::SOUND_STOP_RESET);
		SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(ResourceId::Game::COIN_SE, Lib::DSoundManager::SOUND_PLAY);
	});
}

Coin::~Coin()
{
	m_pVertex->Finalize();
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Coin::Update()
{
}

void Coin::Draw()
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
			if (m_Stage.Data[i][j] == Stage::COIN_OBJECT)
			{
				m_pVertex->Draw(pos,m_pUvController->GetUV(),1.f,Lib::VECTOR2(0.8f,0.8f));
			}
			pos.x += 64.f;
		}
		pos.y += 64.f;
	}
}
