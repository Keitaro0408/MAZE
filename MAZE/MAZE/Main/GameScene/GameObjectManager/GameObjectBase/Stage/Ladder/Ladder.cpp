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

	m_pEndLadderUv = Lib::MakeUnique<Lib::AnimUvController>();
	m_pEndLadderUv->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "EndLadder");

	m_pMiddleLadderUv = Lib::MakeUnique<Lib::AnimUvController>();
	m_pMiddleLadderUv->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "MiddleLadder");

	m_pVertex = Lib::MakeUnique<Lib::Vertex2D>(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Initialize(Lib::VECTOR2(64, 64),
		m_pEndLadderUv->GetUV());
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

	auto LadderDraw = [&](int _x, int _y)
	{
		// 縦チェック-------------------------------------------------------------------------------
		if (m_Stage.Data[_y + 1][_x] == Stage::END_LADDER_OBJECT &&
			m_Stage.Data[_y - 1][_x] == Stage::END_LADDER_OBJECT &&
			m_Stage.Data[_y][_x] == Stage::LADDER_OBJECT)
		{
			m_pVertex->Draw(pos, m_pMiddleLadderUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 0);
		}
		if (m_Stage.Data[_y + 1][_x] == Stage::END_LADDER_OBJECT &&
			m_Stage.Data[_y - 1][_x] == Stage::LADDER_OBJECT &&
			m_Stage.Data[_y][_x] == Stage::LADDER_OBJECT)
		{
			m_pVertex->Draw(pos, m_pMiddleLadderUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 0);
		}
		if (m_Stage.Data[_y + 1][_x] == Stage::LADDER_OBJECT &&
			m_Stage.Data[_y - 1][_x] == Stage::END_LADDER_OBJECT &&
			m_Stage.Data[_y][_x] == Stage::LADDER_OBJECT)
		{
			m_pVertex->Draw(pos, m_pMiddleLadderUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 0);
		}
		if (m_Stage.Data[_y + 1][_x] == Stage::LADDER_OBJECT &&
			m_Stage.Data[_y - 1][_x] == Stage::LADDER_OBJECT &&
			m_Stage.Data[_y][_x] == Stage::LADDER_OBJECT)
		{
			m_pVertex->Draw(pos, m_pMiddleLadderUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 0);
		}
		// 横チェック-------------------------------------------------------------------------------
		else if (m_Stage.Data[_y][_x + 1] == Stage::END_LADDER_OBJECT &&
			m_Stage.Data[_y][_x - 1] == Stage::END_LADDER_OBJECT &&
			m_Stage.Data[_y][_x] == Stage::LADDER_OBJECT)
		{
			m_pVertex->Draw(pos, m_pMiddleLadderUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 90);
		}
		else if (m_Stage.Data[_y][_x + 1] == Stage::END_LADDER_OBJECT &&
			m_Stage.Data[_y][_x - 1] == Stage::LADDER_OBJECT &&
			m_Stage.Data[_y][_x] == Stage::LADDER_OBJECT)
		{
			m_pVertex->Draw(pos, m_pMiddleLadderUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 90);
		}
		else if (m_Stage.Data[_y][_x + 1] == Stage::LADDER_OBJECT &&
			m_Stage.Data[_y][_x - 1] == Stage::END_LADDER_OBJECT &&
			m_Stage.Data[_y][_x] == Stage::LADDER_OBJECT)
		{
			m_pVertex->Draw(pos, m_pMiddleLadderUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 90);
		}
		else if (m_Stage.Data[_y][_x + 1] == Stage::LADDER_OBJECT &&
			m_Stage.Data[_y][_x - 1] == Stage::LADDER_OBJECT &&
			m_Stage.Data[_y][_x] == Stage::LADDER_OBJECT)
		{
			m_pVertex->Draw(pos, m_pMiddleLadderUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 90);
		}
		else if (m_Stage.Data[_y][_x] == Stage::END_LADDER_OBJECT && 
			m_Stage.Data[_y][_x + 1] == Stage::LADDER_OBJECT)
		{
			m_pVertex->Draw(pos, m_pEndLadderUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 90);
		}
		else if (m_Stage.Data[_y][_x] == Stage::END_LADDER_OBJECT && 
			m_Stage.Data[_y][_x - 1] == Stage::LADDER_OBJECT)
		{
			m_pVertex->Draw(pos, m_pEndLadderUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), -90);
		}
		else if (m_Stage.Data[_y][_x] == Stage::END_LADDER_OBJECT && 
			m_Stage.Data[_y + 1][_x] == Stage::LADDER_OBJECT)
		{
			m_pVertex->Draw(pos, m_pEndLadderUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 180);
		}
		else if (m_Stage.Data[_y][_x] == Stage::END_LADDER_OBJECT && 
			m_Stage.Data[_y - 1][_x] == Stage::LADDER_OBJECT)
		{
			m_pVertex->Draw(pos, m_pEndLadderUv->GetUV(), 1.f, Lib::VECTOR2(1, 1));
		}
	};

	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));
	for (int i = 0; i < STAGE_HEIGHT - 1; i++)
	{
		pos.x = static_cast<float>((windowSize.x / 2) - (64 * (STAGE_WIDTH / 2)));
		for (int j = 0; j < STAGE_WIDTH - 1; j++)
		{
			LadderDraw(j,i);
			pos.x += 64.f;
		}
		pos.y += 64.f;
	}
}
