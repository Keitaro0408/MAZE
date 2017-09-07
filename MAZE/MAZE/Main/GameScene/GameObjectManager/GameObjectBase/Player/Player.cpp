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
#include "Sound\DSoundManager.h"
#include "SceneManager\SceneManager.h"
#include "Window\Window.h"


Player::Player() :
m_IsSky(false),
m_UseLadder(false),
m_MoveSpeed(3.f),
m_Angle(0),
m_Animation(RIGHT_WALK_ANIM),
m_IsRightDir(false),
m_IsStart(false),
m_IsEnd(false),
m_IsDangle(false),
m_DangleEnable(true),
m_IsJump(false),
m_FrameCount(180),
m_Scale(0.5f),
m_OldHeight(0.f),
m_JumpPower(15.f)
{
	InitializeTask(3, 3);

	LoadAnimation(RIGHT_WALK_ANIM, "PlayerRightWalk",5);
	LoadAnimation(LEFT_WALK_ANIM, "PlayerLeftWalk", 5);
	LoadAnimation(WAIT_ANIM, "PlayerWait", 0);
	LoadAnimation(RIGHT_FALL_ANIM, "PlayerRightFall", 0);
	LoadAnimation(LEFT_FALL_ANIM, "PlayerLeftFall", 0);
	LoadAnimation(LADDER_UP_DOWN_ANIM, "PlayerLadder", 8);
	LoadAnimation(LADDER_DANGLE, "LadderDangle", 8);
	LoadAnimation(DOOR_OPEN, "PlayerDoor", 20);
	LoadAnimation(TRAMPOLINE_JUMP_ANIM, "PlayerTrampoline", 15);
	

	m_AddScaleValue = (1.f - m_Scale) / 60;
	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Initialize(Lib::VECTOR2(64, 64),
		m_pUvController[WAIT_ANIM]->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));
	SetStartPos();

	pUpdate = &Player::StartUpdate;
	InitializeEvent();
}

Player::~Player()
{
	m_pVertex->Finalize();
	FinalizeTask();
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Player::Update()
{
	(this->*pUpdate)();
}

void Player::Draw()
{
	SINGLETON_INSTANCE(Lib::DX11Manager).SetDepthStencilTest(false);
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));

	if (m_FrameCount >= 180)
	{
		m_pVertex->Draw(m_Pos, m_pUvController[m_Animation]->GetUV(),1.f,Lib::VECTOR2(m_Scale,m_Scale));
	}
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void Player::StartUpdate()
{
	if (m_Scale < 1.f)
	{
		SINGLETON_INSTANCE(Lib::EventManager).CallEvent("OpenStartDoor");
		m_Scale += m_AddScaleValue;
	}
	m_pUvController[DOOR_OPEN]->Control(false, Lib::ANIM_NORMAL);

	if (m_IsStart)
	{
		pUpdate = &Player::NormalUpdate;
	}
}

void Player::NormalUpdate()
{
	// 回転中ならプレイヤー操作を受け付けない
	if (SINGLETON_INSTANCE(GamePlayManager).GetIsSpin())
	{
		StageSpinUpdate();
		return;
	}

	GamePlayManager::SELECT_STAGE stage;
	stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();
	int posArrayX = static_cast<int>((m_Pos.x - 480) / 64);
	int leftPosArrayX = static_cast<int>(((m_Pos.x - 480) - 20) / 64);
	int rightPosArrayX = static_cast<int>(((m_Pos.x - 480) + 20) / 64);
	int posArrayY = static_cast<int>((m_Pos.y - 60) / 64);

	// ゴール処理------------------------------------------------------------------------
	if ((stage.Data[posArrayY][leftPosArrayX] % 10) == Stage::GOAL_DOOR_OBJECT &&
		(stage.Data[posArrayY][rightPosArrayX] % 10) == Stage::GOAL_DOOR_OBJECT &&
		SINGLETON_INSTANCE(GamePlayManager).CheckEnableGimmick(leftPosArrayX, posArrayY))
	{
		if (!m_IsEnd &&
			SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("Up", Lib::KEY_PUSH))
		{
			m_pUvController[DOOR_OPEN]->SetAnimCount(0);
			SINGLETON_INSTANCE(Lib::EventManager).CallEvent("OpenGoalDoor");
			m_IsEnd = true;
			return;
		}
		else if (m_IsEnd)
		{
			m_Animation = DOOR_OPEN;
			m_Scale -= m_AddScaleValue;
			if (m_Scale < 0.5f)
			{
				m_Scale = 0.5f;
			}
			if (m_pUvController[DOOR_OPEN]->Control(false, Lib::ANIM_NORMAL))
			{
				SINGLETON_INSTANCE(Lib::SceneManager).ChangeScene("TitleScene");
			}
			return;
		}
	}
	//----------------------------------------------------------------------------------

	MoveUpdate();
	CheckCollision();

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("A", Lib::KEY_PUSH) &&
		!m_IsSky || 
		SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("A", Lib::KEY_PUSH) && 
		m_UseLadder)
	{
		SINGLETON_INSTANCE(Lib::EventManager).CallEvent("LeftSpin");
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("D", Lib::KEY_PUSH) &&
		!m_IsSky || 
		SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("D", Lib::KEY_PUSH) && 
		m_UseLadder)
	{
		SINGLETON_INSTANCE(Lib::EventManager).CallEvent("RightSpin");
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("W", Lib::KEY_PUSH) &&
		!m_IsSky ||
		SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("W", Lib::KEY_PUSH) &&
		m_UseLadder)
	{
		SINGLETON_INSTANCE(Lib::EventManager).CallEvent("ReversalSpin");
	}

	LadderControl();
}

void Player::RespawnUpdate()
{
	m_FrameCount++;
	SetStartPos();
	if (m_FrameCount < 180) return;

	m_Animation = DOOR_OPEN;

	if (m_Scale < 1.f)
	{
		SINGLETON_INSTANCE(Lib::EventManager).CallEvent("OpenStartDoor");
		m_Scale += m_AddScaleValue;
	}
	else
	{
		pUpdate = &Player::NormalUpdate;
	}

	m_pUvController[DOOR_OPEN]->Control(false, Lib::ANIM_NORMAL);
}

void Player::InitializeEvent()
{
	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("LeftSpin", [this]()
	{
		int posArrayX = static_cast<int>((m_Pos.x - 480) / 64);
		int posArrayY = static_cast<int>((m_Pos.y - 60) / 64);
		m_Angle = 0;

		m_Pos.x = static_cast<float>((posArrayX * 64 + 480) + 32);
		m_Pos.y = static_cast<float>((posArrayY * 64 + 60) + 32);
		m_SpinType = LEFT_SPIN;
		m_SpinSpeed = -2;
	});

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("RightSpin", [this]()
	{
		int posArrayX = static_cast<int>((m_Pos.x - 480) / 64);
		int posArrayY = static_cast<int>((m_Pos.y - 60) / 64);
		m_Angle = 0;

		m_Pos.x = static_cast<float>((posArrayX * 64 + 480) + 32);
		m_Pos.y = static_cast<float>((posArrayY * 64 + 60) + 32);
		m_SpinType = RIGHT_SPIN;
		m_SpinSpeed = 2;
	});

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("ReversalSpin", [this]()
	{
		int posArrayX = static_cast<int>((m_Pos.x - 480) / 64);
		int posArrayY = static_cast<int>((m_Pos.y - 60) / 64);
		m_Angle = 0;

		m_Pos.x = static_cast<float>((posArrayX * 64 + 480) + 32);
		m_Pos.y = static_cast<float>((posArrayY * 64 + 60) + 32);
		m_SpinType = REVERSAL_SPIN;
		m_SpinSpeed = 4;
	});


	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("GameStart", [this]()
	{
		m_IsStart = true;
	});
}

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
			if (stage.Data[i][j] == Stage::START_DOOR_OBJECT)
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
	m_Angle += m_SpinSpeed;

	GamePlayManager::SELECT_STAGE stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();

	int posArrayX = static_cast<int>((m_Pos.x - 480) / 64);
	int posArrayY = static_cast<int>((m_Pos.y - 60) / 64);
	auto CheckLadder = [&](int _x, int _y)
	{
		if (stage.Data[_y][_x] == Stage::END_LADDER_OBJECT ||
			stage.Data[_y][_x] == Stage::LADDER_OBJECT)
		{
			return true;
		}
		return false;
	};

	if (abs(m_Angle) >= 90.f - abs(m_SpinSpeed))
	{
		m_pUvController[LADDER_DANGLE]->SetAnimCount(0);
		if (CheckLadder(posArrayX, posArrayY))
		{
			m_pUvController[LADDER_UP_DOWN_ANIM]->Control(false, Lib::ANIM_LOOP);
			m_UseLadder = true;
			m_Animation = LADDER_UP_DOWN_ANIM;
			m_Pos.x = static_cast<float>((posArrayX * 64 + 480) + 32);
			if (CheckLadder(posArrayX - 1, posArrayY) ||
				CheckLadder(posArrayX + 1, posArrayY))
			{
				if (m_DangleEnable &&
					!SINGLETON_INSTANCE(GamePlayManager).CheckGround(posArrayX, posArrayY + 1))
				{
					m_UseLadder = true;
					m_IsDangle = true;
					m_Animation = LADDER_DANGLE;
					m_pUvController[LADDER_DANGLE]->Control(false, Lib::ANIM_NORMAL);
					m_Pos.y += 25.f;
				}
			}
		}
	}
}

void Player::MoveUpdate()
{
	// 空中にいるときは移動出来ない
	if (m_IsSky && !m_UseLadder && !m_IsJump)
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

	if (!m_IsJump)
	{
		m_Animation = WAIT_ANIM;
	}

	GamePlayManager::SELECT_STAGE stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();
	int leftPosArrayX = static_cast<int>(((m_Pos.x - 480) - 14) / 64);
	int rightPosArrayX = static_cast<int>(((m_Pos.x - 480) + 14) / 64);
	int posArrayY = static_cast<int>((m_Pos.y - 60) / 64);

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("RightMove", Lib::KEY_ON))
	{
		if (!m_IsDangle && !m_UseLadder && !m_IsJump)
		{
			m_Pos.x += m_MoveSpeed;
			m_Animation = RIGHT_WALK_ANIM;
			m_IsRightDir = true;
			m_pUvController[RIGHT_WALK_ANIM]->Control(false, Lib::ANIM_LOOP);
			if (SINGLETON_INSTANCE(GamePlayManager).CheckGround(rightPosArrayX, posArrayY) ||
				SINGLETON_INSTANCE(GamePlayManager).CheckRightCover(rightPosArrayX, posArrayY))
			{
				m_Pos.x -= m_MoveSpeed;
			}

		}
		else if (m_UseLadder)
		{
			m_UseLadder = false;
			m_IsRightDir = true;
		}
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("LeftMove", Lib::KEY_ON))
	{
		if (!m_IsDangle && !m_UseLadder && !m_IsJump)
		{
			m_Pos.x -= m_MoveSpeed;
			m_Animation = LEFT_WALK_ANIM;
			m_IsRightDir = false;
			m_pUvController[LEFT_WALK_ANIM]->Control(false, Lib::ANIM_LOOP);
			if (SINGLETON_INSTANCE(GamePlayManager).CheckGround(leftPosArrayX, posArrayY) ||
				SINGLETON_INSTANCE(GamePlayManager).CheckLeftCover(leftPosArrayX, posArrayY))
			{
				m_Pos.x += m_MoveSpeed;
			}
		}
		else if (m_UseLadder)
		{
			m_UseLadder = false;
			m_IsRightDir = false;
		}
	}

	if (m_UseLadder && !m_IsDangle)
	{
		m_Animation = LADDER_UP_DOWN_ANIM;
	}
}

void Player::CheckCollision()
{
	GamePlayManager::SELECT_STAGE stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();
	int leftPosArrayX = static_cast<int>(((m_Pos.x - 480) - 14) / 64);
	int rightPosArrayX = static_cast<int>(((m_Pos.x - 480) + 14) / 64);
	int posArrayX = static_cast<int>((m_Pos.x - 480) / 64);
	int posArrayY = static_cast<int>((m_Pos.y - 60) / 64);
	int bottomPosArrayY = static_cast<int>((m_Pos.y - 60 + 32) / 64);
	int topPosArrayY = static_cast<int>(((m_Pos.y - 60) - 32) / 64);


	if (stage.Data[posArrayY][posArrayX] == Stage::COIN_OBJECT)
	{
		GamePlayManager::SELECT_STAGE tmpStage = stage;
		tmpStage.Data[posArrayY][posArrayX] = 0;
		SINGLETON_INSTANCE(GamePlayManager).SetSelectStage(tmpStage);
		SINGLETON_INSTANCE(Lib::EventManager).CallEvent("CoinGet");
	}
	else if (SINGLETON_INSTANCE(GamePlayManager).CheckEnableGimmick(posArrayX, posArrayY) &&
		(stage.Data[posArrayY][posArrayX] % 10) == Stage::TRAMPOLINE_OBJECT)
	{
		m_Acceleration = -15;
		m_Pos.y += m_Acceleration;
		m_Animation = TRAMPOLINE_JUMP_ANIM;
		m_pUvController[TRAMPOLINE_JUMP_ANIM]->SetAnimCount(0);
		m_IsJump = true;
	}


	if (!SINGLETON_INSTANCE(GamePlayManager).CheckGround(rightPosArrayX, bottomPosArrayY) &&
		!SINGLETON_INSTANCE(GamePlayManager).CheckGround(leftPosArrayX, bottomPosArrayY) &&
		!SINGLETON_INSTANCE(GamePlayManager).CheckUnderCover(rightPosArrayX, bottomPosArrayY) &&
		!SINGLETON_INSTANCE(GamePlayManager).CheckUnderCover(leftPosArrayX, bottomPosArrayY))
	{
		if (!m_UseLadder)
		{
			m_Pos.y += m_Acceleration;
			m_Acceleration += 0.7f;
			m_pUvController[LADDER_DANGLE]->SetAnimCount(0);

			m_IsSky = true;
			if (m_IsRightDir)
			{
				m_pUvController[RIGHT_FALL_ANIM]->Control(false, Lib::ANIM_LOOP);
			}
			else
			{
				m_pUvController[LEFT_FALL_ANIM]->Control(false, Lib::ANIM_LOOP);
			}
		}
	}
	else
	{
		if (m_IsSky)
		{
			SINGLETON_INSTANCE(Lib::DSoundManager).
				SoundOperation(ResourceId::Game::LANDING_SE, Lib::DSoundManager::SOUND_STOP_RESET);
			SINGLETON_INSTANCE(Lib::DSoundManager).
				SoundOperation(ResourceId::Game::LANDING_SE,Lib::DSoundManager::SOUND_PLAY);
		}
		m_IsSky = false;
	}


	// 地面に足が付いているか
	if (SINGLETON_INSTANCE(GamePlayManager).CheckGround(rightPosArrayX, bottomPosArrayY) &&
		SINGLETON_INSTANCE(GamePlayManager).CheckGround(leftPosArrayX, bottomPosArrayY) || 
		SINGLETON_INSTANCE(GamePlayManager).CheckUnderCover(rightPosArrayX, bottomPosArrayY) &&
		SINGLETON_INSTANCE(GamePlayManager).CheckUnderCover(leftPosArrayX, bottomPosArrayY))
	{
		m_Pos.y -= (m_Pos.y + 32) - (bottomPosArrayY * 64 + 60);
		m_UseLadder = false;
		m_Acceleration = 0;
	}


	if (m_IsJump)
	{
		m_pUvController[TRAMPOLINE_JUMP_ANIM]->Control(false, Lib::ANIM_NORMAL);
		if (SINGLETON_INSTANCE(GamePlayManager).CheckGround(rightPosArrayX, topPosArrayY ||
			SINGLETON_INSTANCE(GamePlayManager).CheckGround(leftPosArrayX, topPosArrayY)))
		{
			m_IsJump = false;
			m_Pos.y += (m_Pos.y - 32) - (topPosArrayY * 64 + 60 + 32);
			m_Acceleration = 0;
		}
	}


	if ((stage.Data[posArrayY][posArrayX] % 10) == Stage::NEEDLE_OBJECT &&
		SINGLETON_INSTANCE(GamePlayManager).CheckEnableGimmick(posArrayX, bottomPosArrayY))
	{
		m_Scale = 0.5;
		SINGLETON_INSTANCE(Lib::EventManager).CallEvent("PlayerRespawn");
		m_pUvController[DOOR_OPEN]->SetAnimCount(0);
		m_FrameCount = 0;
		pUpdate = &Player::RespawnUpdate;
	}

}

bool Player::CheckGrabLadder()
{
	return false;
}

void Player::LadderControl()
{
	GamePlayManager::SELECT_STAGE stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();

	int posArrayX = static_cast<int>((m_Pos.x - 480) / 64);
	int posArrayY = static_cast<int>((m_Pos.y - 60) / 64);
	int TopPosArrayY = static_cast<int>(((m_Pos.y - 60) - 32) / 64);

	auto CheckLadder = [&](int _x, int _y)
	{
		if (stage.Data[_y][_x] == Stage::END_LADDER_OBJECT ||
			stage.Data[_y][_x] == Stage::LADDER_OBJECT)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	if (!CheckLadder(posArrayX, posArrayY))
	{
		m_UseLadder = false;
	}

	// 梯子にななめにぶら下がる処理
	if (CheckLadder(posArrayX, TopPosArrayY))
	{
		if (CheckLadder(posArrayX - 1, TopPosArrayY) ||
			CheckLadder(posArrayX + 1, TopPosArrayY))
		{
			if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("Down", Lib::KEY_PUSH))
			{
				m_UseLadder = false;
				m_DangleEnable = false;
			}
			else if (m_DangleEnable && 
				(stage.Data[posArrayY + 1][posArrayX] % 10) != Stage::GROUND_OBJECT &&
				m_Acceleration >= 0)
			{
				m_UseLadder = true;
				m_IsJump = false;
				m_IsDangle = true;
				m_Pos.x = static_cast<float>((posArrayX * 64 + 480) + 32);
				m_Pos.y = static_cast<float>((TopPosArrayY * 64 + 60) + 32);
				m_Pos.y += 25.f;
				m_Animation = LADDER_DANGLE;
				m_pUvController[LADDER_DANGLE]->Control(false, Lib::ANIM_NORMAL);
				m_Acceleration = 0;
			}
			else
			{
				m_IsDangle = false;
			}
		}
	}
	else
	{
		m_DangleEnable = true;
		m_IsDangle = false;
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("Up", Lib::KEY_ON))
	{
		if (!m_IsDangle)
		{
			if (CheckLadder(posArrayX, TopPosArrayY - 1) &&
				stage.Data[TopPosArrayY][posArrayX] == Stage::LADDER_OBJECT ||
				stage.Data[TopPosArrayY][posArrayX] == Stage::END_LADDER_OBJECT)
			{
				m_Acceleration = 0;
				m_Pos.x = static_cast<float>((posArrayX * 64 + 480) + 32);
				m_pUvController[LADDER_UP_DOWN_ANIM]->Control(false, Lib::ANIM_LOOP);
				m_UseLadder = true;
				m_Pos.y -= m_MoveSpeed;
			}
			else if (m_UseLadder &&
				CheckLadder(posArrayX, TopPosArrayY))
			{
				m_Animation = LADDER_UP_DOWN_ANIM;
				m_Pos.x = static_cast<float>((posArrayX * 64 + 480) + 32);
				m_pUvController[LADDER_UP_DOWN_ANIM]->Control(false, Lib::ANIM_LOOP);
				m_UseLadder = true;
				m_Pos.y -= m_MoveSpeed;
			}
		}
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("Down", Lib::KEY_ON))
	{
		if (!m_IsDangle && m_DangleEnable)
		{
			if (CheckLadder(posArrayX, posArrayY + 1) &&
				stage.Data[posArrayY][posArrayX] == Stage::LADDER_OBJECT ||
				stage.Data[posArrayY][posArrayX] == Stage::END_LADDER_OBJECT)
			{
				m_Acceleration = 0;
				m_Pos.x = static_cast<float>((posArrayX * 64 + 480) + 32);
				m_pUvController[LADDER_UP_DOWN_ANIM]->Control(false, Lib::ANIM_LOOP);
				m_UseLadder = true;
				m_Pos.y += m_MoveSpeed;
				m_Animation = LADDER_UP_DOWN_ANIM;
			}
			else if (m_UseLadder &&
				CheckLadder(posArrayX, posArrayY))
			{
				m_Animation = LADDER_UP_DOWN_ANIM;
				m_Pos.x = static_cast<float>((posArrayX * 64 + 480) + 32);
				m_pUvController[LADDER_UP_DOWN_ANIM]->Control(false, Lib::ANIM_LOOP);
				m_UseLadder = true;
				m_Pos.y += m_MoveSpeed;
			}
		}
	}
}
