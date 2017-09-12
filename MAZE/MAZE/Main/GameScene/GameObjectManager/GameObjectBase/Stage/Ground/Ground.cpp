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

	m_pGreenUv = Lib::MakeUnique<Lib::AnimUvController>();
	m_pGreenUv->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "GreenGround");
	m_pBlueUv = Lib::MakeUnique<Lib::AnimUvController>();
	m_pBlueUv->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "BlueGround");
	m_pGreyUv = Lib::MakeUnique<Lib::AnimUvController>();
	m_pGreyUv->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "GreyGround");

	m_pVertex = Lib::MakeUnique<Lib::Vertex2D>(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Initialize(Lib::VECTOR2(64,64),
		m_pGreenUv->GetUV());
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

	auto GroundDraw = [&](int _x, int _y)
	{
		if ((m_Stage.Data[_y][_x] % 10) == Stage::GROUND_OBJECT &&
			((m_Stage.Data[_y][_x] / 10) % 10) == BLUE)
		{
			m_pVertex->Draw(pos, m_pBlueUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 0);
		}
		else if ((m_Stage.Data[_y][_x] % 10) == Stage::GROUND_OBJECT &&
			((m_Stage.Data[_y][_x] / 10) % 10) == GREEN)
		{
			m_pVertex->Draw(pos, m_pGreenUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 0);
		}
		else if ((m_Stage.Data[_y][_x] % 10) == Stage::GROUND_OBJECT &&
			((m_Stage.Data[_y][_x] / 10) % 10) == GREY)
		{
			m_pVertex->Draw(pos, m_pGreyUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 0);
		}
	};

	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		pos.x = static_cast<float>((windowSize.x / 2) - (64 * (STAGE_WIDTH / 2)));
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			GroundDraw(j,i);
			pos.x += 64.f;
		}
		pos.y += 64.f;
	}
}
