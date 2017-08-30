/**
 * @file   GameBackGround.cpp
 * @brief  GameBackGroundクラスの実装
 * @author kotani
 */
#include "GameBackGround.h"
#include "Dx11\DX11Manager.h"
#include "Window\Window.h"
#include "Texture\TextureManager.h"
#include "..\..\..\..\ResourceId.h"


GameBackGround::GameBackGround()
{
	InitializeTask(0, 0);

	m_Uv[0] = Lib::VECTOR2(0, 0);
	m_Uv[1] = Lib::VECTOR2(1, 0);
	m_Uv[2] = Lib::VECTOR2(0, 1);
	m_Uv[3] = Lib::VECTOR2(1, 1);

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Initialize(Lib::VECTOR2(1920, 1080),m_Uv);
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::BACKGROUND_TEX));
}

GameBackGround::~GameBackGround()
{
	FinalizeTask();
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void GameBackGround::Update()
{
}

void GameBackGround::Draw()
{
	m_pVertex->Draw(Lib::VECTOR2(960,540),m_Uv);
}
