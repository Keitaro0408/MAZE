/**
 * @file   Ladder.cpp
 * @brief  Ladderクラスの実装
 * @author kotani
 */
#include "Ladder.h"
#include "..\..\..\..\..\ResourceId.h"

#include "Window\Window.h"
#include "Texture\TextureManager.h"
#include "Math\Math.h"


Ladder::Ladder()
{
	m_Stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();

	m_pTopLadderUv = new Lib::AnimUvController();
	m_pTopLadderUv->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "TopLadder");

	m_pMiddleLadderUv = new Lib::AnimUvController();
	m_pMiddleLadderUv->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "MiddleLadder");

	m_pBottomLadderUv = new Lib::AnimUvController();
	m_pBottomLadderUv->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "BottomLadder");

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Initialize(Lib::VECTOR2(64, 64),
		m_pTopLadderUv->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));
}

Ladder::~Ladder()
{
	m_pVertex->Finalize();
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Ladder::Update()
{
}

void Ladder::Draw()
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
			if (m_Stage.Data[i][j] == Stage::TOP_LADDER_OBJECT)
			{
				m_pVertex->Draw(pos, m_pTopLadderUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 0);
			}
			if (m_Stage.Data[i][j] == Stage::MIDDLE_LADDER_OBJECT)
			{
				m_pVertex->Draw(pos, m_pMiddleLadderUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 0);
			}
			if (m_Stage.Data[i][j] == Stage::BOTTOM_LADDER_OBJECT)
			{
				m_pVertex->Draw(pos, m_pBottomLadderUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 0);
			}
			pos.x += 64.f;
		}
		pos.y += 64.f;
	}
}
