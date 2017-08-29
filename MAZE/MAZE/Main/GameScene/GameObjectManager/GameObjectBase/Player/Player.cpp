/**
 * @file   Player.cpp
 * @brief  Playerクラスの実装
 * @author kotani
 */
#include "Player.h"
#include "Event\EventManager.h"
#include "..\..\..\..\GamePlayManager\GamePlayManager.h"
#include "DxInput\KeyBoard\KeyDevice.h"
#include "Dx11\DX11Manager.h"
#include "Texture\TextureManager.h"
#include "Window\Window.h"
#include "..\..\..\..\ResourceId.h"

Player::Player() :
m_IsRightDir(false),
m_MoveSpeed(3.f)
{
	InitializeTask(3, 3);

	m_pRightAnimation = new Lib::AnimUvController();
	m_pRightAnimation->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "PlayerRightWalk");
	m_pRightAnimation->SetAnimFrame(5);

	m_pLeftAnimation = new Lib::AnimUvController();
	m_pLeftAnimation->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "PlayerLeftWalk");
	m_pLeftAnimation->SetAnimFrame(5);

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Initialize(Lib::VECTOR2(64, 64),
		m_pLeftAnimation->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));
	SetStartPos();
}


Player::~Player()
{
	FinalizeTask();
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Player::Update()
{
	// 回転中ならプレイヤー操作を受け付けない事
	if (SINGLETON_INSTANCE(GamePlayManager).GetIsSpin())
	{
		// 回転補正処理
		return;
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("RightMove", Lib::KEY_ON))
	{
		m_IsRightDir = true;
		m_pRightAnimation->Control(false,Lib::ANIM_LOOP);
		m_Pos.x += m_MoveSpeed;
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("LeftMove", Lib::KEY_ON))
	{
		m_IsRightDir = false;
		m_pLeftAnimation->Control(false, Lib::ANIM_LOOP);
		m_Pos.x -= m_MoveSpeed;
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("W", Lib::KEY_PUSH))
	{
		SINGLETON_INSTANCE(Lib::EventManager).CallEvent("ReversalSpin");
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("A", Lib::KEY_PUSH))
	{
		SINGLETON_INSTANCE(Lib::EventManager).CallEvent("LeftSpin");
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("D", Lib::KEY_PUSH))
	{
		SINGLETON_INSTANCE(Lib::EventManager).CallEvent("RightSpin");
	}
}

void Player::Draw()
{
	SINGLETON_INSTANCE(Lib::DX11Manager).SetDepthStencilTest(false);
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));
	if (m_IsRightDir)
	{
		m_pVertex->Draw(m_Pos,m_pRightAnimation->GetUV());
	}
	else
	{
		m_pVertex->Draw(m_Pos, m_pLeftAnimation->GetUV());
	}
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void Player::SetStartPos()
{
	GamePlayManager::SELECT_STAGE stage;
	stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();

	Lib::VECTOR2 pos;
	Lib::VECTOR2 windowSize;
	windowSize.x = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().right);
	windowSize.y = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().bottom);

	pos.x = static_cast<float>((windowSize.x / 2) - (64 * (STAGE_WIDTH / 2)));
	pos.y = static_cast<float>((windowSize.y / 2) - (64 * (STAGE_HEIGHT / 2)));

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		pos.x = static_cast<float>((windowSize.x / 2) - (64 * (STAGE_WIDTH / 2)));
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if (stage.Data[i][j] == 3)
			{
				m_Pos = pos;
				return;
			}
			pos.x += 64.f;
		}
		pos.y += 64.f;
	}

}
