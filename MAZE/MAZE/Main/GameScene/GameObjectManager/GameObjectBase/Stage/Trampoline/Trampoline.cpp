/**
 * @file   Trampoline.cpp
 * @brief  Trampolineクラスの実装
 * @author kotani
 */
#include "Trampoline.h"
#include "Window\Window.h"
#include "Texture\TextureManager.h"
#include "..\..\..\..\..\ResourceId.h"
#include "Math\Math.h"

Trampoline::Trampoline()
{
	m_Stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();

	m_pUvController = Lib::MakeUnique<Lib::AnimUvController>();
	m_pUvController->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "TrampolineObj");

	m_pVertex = Lib::MakeUnique<Lib::Vertex2D>(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Initialize(Lib::VECTOR2(64, 64),
		m_pUvController->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));
}

Trampoline::~Trampoline()
{
	m_pVertex->Finalize();
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Trampoline::Update()
{

}

void Trampoline::Draw()
{
	Lib::VECTOR2 pos;
	Lib::VECTOR2 windowSize;
	windowSize.x = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().right);
	windowSize.y = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().bottom);

	pos.x = static_cast<float>((windowSize.x / 2) - (64 * (STAGE_WIDTH / 2)));
	pos.y = static_cast<float>((windowSize.y / 2) - (64 * (STAGE_HEIGHT / 2)));

	auto TrampolineDraw = [&](int _x, int _y)
	{
		if ((m_Stage.Data[_y][_x] % 10) == Stage::TRAMPOLINE_OBJECT &&
			((m_Stage.Data[_y][_x] / 10) % 10) == 0)
		{
			m_pVertex->Draw(pos, m_pUvController->GetUV());
		}
		else if ((m_Stage.Data[_y][_x] % 10) == Stage::TRAMPOLINE_OBJECT &&
			((m_Stage.Data[_y][_x] / 10) % 10) == 1)
		{
			m_pVertex->Draw(pos, m_pUvController->GetUV(), 1.f, Lib::VECTOR2(1, 1), 90);
		}
		else if ((m_Stage.Data[_y][_x] % 10) == Stage::TRAMPOLINE_OBJECT &&
			((m_Stage.Data[_y][_x] / 10) % 10) == 2)
		{
			m_pVertex->Draw(pos, m_pUvController->GetUV(), 1.f, Lib::VECTOR2(1, 1), 180);
		}
		else if ((m_Stage.Data[_y][_x] % 10) == Stage::TRAMPOLINE_OBJECT &&
			((m_Stage.Data[_y][_x] / 10) % 10) == 3)
		{
			m_pVertex->Draw(pos, m_pUvController->GetUV(), 1.f, Lib::VECTOR2(1, 1), -90);
		}
	};

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		pos.x = static_cast<float>((windowSize.x / 2) - (64 * (STAGE_WIDTH / 2)));
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			TrampolineDraw(j,i);
			pos.x += 64.f;
		}
		pos.y += 64.f;
	}
}
