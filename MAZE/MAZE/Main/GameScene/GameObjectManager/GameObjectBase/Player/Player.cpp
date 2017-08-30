/**
 * @file   Player.cpp
 * @brief  Playerクラスの実装
 * @author kotani
 */
#include "Player.h"
#include "..\..\..\..\ResourceId.h"
#include "..\..\..\..\GamePlayManager\GamePlayManager.h"
#include "Math\Math.h"
#include "Event\EventManager.h"
#include "DxInput\KeyBoard\KeyDevice.h"
#include "Dx11\DX11Manager.h"
#include "Texture\TextureManager.h"
#include "Window\Window.h"

Player::Player() :
m_IsSky(false),
m_MoveSpeed(3.f),
m_Animation(RIGHT_WALK_ANIM),
m_IsRightDir(false)
{
	InitializeTask(3, 3);

	LoadAnimation(RIGHT_WALK_ANIM, "PlayerRightWalk",5);
	LoadAnimation(LEFT_WALK_ANIM, "PlayerLeftWalk", 5);
	LoadAnimation(WAIT_ANIM, "PlayerWait", 0);
	LoadAnimation(RIGHT_FALL_ANIM, "PlayerRightFall", 0);
	LoadAnimation(LEFT_FALL_ANIM, "PlayerLeftFall", 0);

	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Initialize(Lib::VECTOR2(64, 64),
		m_pUvController[WAIT_ANIM]->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));
	SetStartPos();

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("LeftSpin", [this]()
	{
		m_SpinType = LEFT_SPIN;
		m_SpinSpeed = -2;
	});

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("RightSpin", [this]()
	{
		m_SpinType = RIGHT_SPIN;
		m_SpinSpeed = 2;
	});
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
		StageSpinUpdate();
		return;
	}


	MoveUpdate();



	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("A", Lib::KEY_PUSH))
	{
		SINGLETON_INSTANCE(Lib::EventManager).CallEvent("LeftSpin");
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("D", Lib::KEY_PUSH))
	{
		SINGLETON_INSTANCE(Lib::EventManager).CallEvent("RightSpin");
	}

	CollisionCheck();
}

void Player::Draw()
{
	SINGLETON_INSTANCE(Lib::DX11Manager).SetDepthStencilTest(false);
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));

	m_pVertex->Draw(m_Pos, m_pUvController[m_Animation]->GetUV());
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void Player::LoadAnimation(ANIMATION _animEnum, std::string _animName, int _setAnimFrame)
{
	m_pUvController[_animEnum] = new Lib::AnimUvController();
	m_pUvController[_animEnum]->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", _animName.c_str());
	m_pUvController[_animEnum]->SetAnimFrame(_setAnimFrame);
}

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
			if (stage.Data[i][j] == Stage::SPAWN_OBJECT)
			{
				m_Pos = pos;
				return;
			}
			pos.x += 64.f;
		}
		pos.y += 64.f;
	}
}

void Player::StageSpinUpdate()
{
	// 回転補正処理
	Lib::VECTOR2 windowSize;
	windowSize.x = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().right);
	windowSize.y = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().bottom);
	float cx = windowSize.x / 2;
	float cy = windowSize.y / 2;
	float dinstance = Lib::Math::GetDistance(Lib::VECTOR2(cx,cy),m_Pos);
	float angle = Lib::Math::GetAngle(Lib::VECTOR2(cx, cy), m_Pos);
	m_Pos.x = cx + dinstance * cos(Lib::Math::ToRadian(m_SpinSpeed + angle));
	m_Pos.y = cy + dinstance * sin(Lib::Math::ToRadian(m_SpinSpeed + angle));
}

void Player::MoveUpdate()
{
	// 空中にいるときは移動出来ない
	if (m_IsSky)
	{
		if (m_IsRightDir)
		{
			m_Animation = RIGHT_FALL_ANIM;
		}
		else
		{
			m_Animation = LEFT_FALL_ANIM;
		}
		return;
	}

	// 逆再生するか
	bool isAnimReverse = false;

	m_Animation = WAIT_ANIM;

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("RightMove", Lib::KEY_ON))
	{
		m_Pos.x += m_MoveSpeed;
		m_Animation = RIGHT_WALK_ANIM;
		m_IsRightDir = true;
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("LeftMove", Lib::KEY_ON))
	{
		m_Pos.x -= m_MoveSpeed;
		m_Animation = LEFT_WALK_ANIM;
		m_IsRightDir = false;
	}
	m_pUvController[m_Animation]->Control(false,Lib::ANIM_LOOP);
}

void Player::CollisionCheck()
{
	GamePlayManager::SELECT_STAGE stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();

	int leftPosArrayX = static_cast<int>(((m_Pos.x - 512) + 14) / 64);
	int rightPosArrayX = static_cast<int>(((m_Pos.x - 512) + 40) / 64);
	int posArrayX = static_cast<int>((m_Pos.x - 512) / 64);
	int posArrayY = static_cast<int>((m_Pos.y - 92) / 64);
	int bottomPosArrayY = static_cast<int>((m_Pos.y - 92 + 64) / 64);

	if (stage.Data[posArrayY][leftPosArrayX] == Stage::GROUND_OBJECT)
	{
		m_Pos.x += m_MoveSpeed;
	}
	else if (stage.Data[posArrayY][rightPosArrayX] == Stage::GROUND_OBJECT)
	{
		m_Pos.x -= m_MoveSpeed;
	}

	if (stage.Data[bottomPosArrayY][rightPosArrayX] != Stage::GROUND_OBJECT &&
		stage.Data[bottomPosArrayY][leftPosArrayX] != Stage::GROUND_OBJECT)
	{
		m_Acceleration += 1;
		m_Pos.y += m_Acceleration;
		m_IsSky = true;
	}
	else
	{
		m_IsSky = false;
	}

	if (stage.Data[bottomPosArrayY][rightPosArrayX] == Stage::GROUND_OBJECT &&
		stage.Data[bottomPosArrayY][leftPosArrayX] == Stage::GROUND_OBJECT)
	{
		float test = (m_Pos.y + 64) - (bottomPosArrayY * 64 + 96);
		m_Pos.y -= (m_Pos.y + 68) - (bottomPosArrayY * 64 + 96);
		m_IsSky = false;
		m_Acceleration = 0;
	}

}
