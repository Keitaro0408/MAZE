/**
 * @file   Needle.cpp
 * @brief  Needleクラスの実装
 * @author kotani
 */
#include "Needle.h"
#include "Window\Window.h"
#include "Event\EventManager.h"
#include "Texture\TextureManager.h"
#include "..\..\..\..\..\ResourceId.h"
#include "Math\Math.h"


Needle::Needle()
{
	m_Stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();

	m_pGreenNeedle = Lib::MakeUnique<Lib::AnimUvController>();
	m_pGreenNeedle->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "GreenNeedle");
	m_pBlueNeedle = Lib::MakeUnique<Lib::AnimUvController>();
	m_pBlueNeedle->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "BlueNeedle");


	m_pVertex = Lib::MakeUnique<Lib::Vertex2D>(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());

	m_pVertex->Initialize(Lib::VECTOR2(64, 64),
		m_pGreenNeedle->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));
}

Needle::~Needle()
{
	m_pVertex->Finalize();
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Needle::Update()
{
}

void Needle::Draw()
{
	Lib::VECTOR2 pos;
	Lib::VECTOR2 windowSize;
	windowSize.x = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().right);
	windowSize.y = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().bottom);

	pos.x = static_cast<float>((windowSize.x / 2) - (64 * (STAGE_WIDTH / 2)));
	pos.y = static_cast<float>((windowSize.y / 2) - (64 * (STAGE_HEIGHT / 2)));

	auto NeedleDraw = [&](int _x, int _y)
	{
		if ((m_Stage.Data[_y][_x] % 10) == Stage::NEEDLE_OBJECT &&
			((m_Stage.Data[_y][_x] / 10) % 10) == 0)
		{
			if (((m_Stage.Data[_y][_x] / 100) % 10) == 1)
			{
				m_pVertex->Draw(pos, m_pBlueNeedle->GetUV());
			}
			else
			{
				m_pVertex->Draw(pos, m_pGreenNeedle->GetUV());
			}
		}
		else if ((m_Stage.Data[_y][_x] % 10) == Stage::NEEDLE_OBJECT &&
			((m_Stage.Data[_y][_x] / 10) % 10) == 1)
		{
			if (((m_Stage.Data[_y][_x] / 100) % 10) == 1)
			{
				m_pVertex->Draw(pos, m_pBlueNeedle->GetUV(), 1.f, Lib::VECTOR2(1, 1), 90);
			}
			else
			{
				m_pVertex->Draw(pos, m_pGreenNeedle->GetUV(), 1.f, Lib::VECTOR2(1, 1), 90);
			}
		}
		else if ((m_Stage.Data[_y][_x] % 10) == Stage::NEEDLE_OBJECT &&
			((m_Stage.Data[_y][_x] / 10) % 10) == 2)
		{
			if (((m_Stage.Data[_y][_x] / 100) % 10) == 1)
			{
				m_pVertex->Draw(pos, m_pBlueNeedle->GetUV(), 1.f, Lib::VECTOR2(1, 1), 180);
			}
			else
			{
				m_pVertex->Draw(pos, m_pGreenNeedle->GetUV(), 1.f, Lib::VECTOR2(1, 1), 180);
			}
		}
		else if ((m_Stage.Data[_y][_x] % 10) == Stage::NEEDLE_OBJECT &&
			((m_Stage.Data[_y][_x] / 10) % 10) == 3)
		{
			if (((m_Stage.Data[_y][_x] / 100) % 10) == 1)
			{
				m_pVertex->Draw(pos, m_pBlueNeedle->GetUV(), 1.f, Lib::VECTOR2(1, 1), -90);
			}
			else
			{
				m_pVertex->Draw(pos, m_pGreenNeedle->GetUV(), 1.f, Lib::VECTOR2(1, 1), -90);
			}
		}
	};

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		pos.x = static_cast<float>((windowSize.x / 2) - (64 * (STAGE_WIDTH / 2)));
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			NeedleDraw(j, i);
			pos.x += 64.f;
		}
		pos.y += 64.f;
	}
}
