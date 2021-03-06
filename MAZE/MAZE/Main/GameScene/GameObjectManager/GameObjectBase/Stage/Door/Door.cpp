﻿/**
 * @file   Door.cpp
 * @brief  Doorクラスの実装
 * @author kotani
 */
#include "Door.h"
#include "Window\Window.h"
#include "Event\EventManager.h"
#include "Texture\TextureManager.h"
#include "..\..\..\..\..\ResourceId.h"
#include "Math\Math.h"


Door::Door()
{
	m_Stage = SINGLETON_INSTANCE(GamePlayManager).GetSelectStage();

	m_pStartDoorUv = Lib::MakeUnique<Lib::AnimUvController>();
	m_pStartDoorUv->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "DoorObj");
	m_pGoalDoorUv = Lib::MakeUnique<Lib::AnimUvController>();
	m_pGoalDoorUv->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim", "DoorObj");

	m_pVertex = Lib::MakeUnique<Lib::Vertex2D>(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());

	m_pVertex->Initialize(Lib::VECTOR2(64, 64),
		m_pStartDoorUv->GetUV());
	m_pVertex->SetTexture(
		SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));
	InitializeEvent();
}

Door::~Door()
{
	m_pVertex->Finalize();
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Door::Update()
{
}

void Door::Draw()
{
	Lib::VECTOR2 pos;
	Lib::VECTOR2 windowSize;
	windowSize.x = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().right);
	windowSize.y = static_cast<float>(SINGLETON_INSTANCE(Lib::Window).GetWindowSize().bottom);

	pos.x = static_cast<float>((windowSize.x / 2) - (64 * (STAGE_WIDTH / 2)));
	pos.y = static_cast<float>((windowSize.y / 2) - (64 * (STAGE_HEIGHT / 2)));

	auto DoorDraw = [&](int _x, int _y)
	{
		if (m_Stage.Data[_y][_x] == Stage::START_DOOR_OBJECT)
		{
			m_pVertex->Draw(pos, m_pStartDoorUv->GetUV(), 1.f, Lib::VECTOR2(1, 1));
		}
		else if ((m_Stage.Data[_y][_x] % 10) == Stage::GOAL_DOOR_OBJECT &&
			((m_Stage.Data[_y][_x] / 10) % 10) == 0)
		{
			m_pVertex->Draw(pos, m_pGoalDoorUv->GetUV(), 1.f, Lib::VECTOR2(1, 1));
		}
		else if ((m_Stage.Data[_y][_x] % 10) == Stage::GOAL_DOOR_OBJECT &&
			((m_Stage.Data[_y][_x] / 10) % 10) == 1)
		{
			m_pVertex->Draw(pos, m_pGoalDoorUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 90);
		}
		else if ((m_Stage.Data[_y][_x] % 10) == Stage::GOAL_DOOR_OBJECT &&
			((m_Stage.Data[_y][_x] / 10) % 10) == 2)
		{
			m_pVertex->Draw(pos, m_pGoalDoorUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), 180);
		}
		else if ((m_Stage.Data[_y][_x] % 10) == Stage::GOAL_DOOR_OBJECT &&
			((m_Stage.Data[_y][_x] / 10) % 10) == 3)
		{
			m_pVertex->Draw(pos, m_pGoalDoorUv->GetUV(), 1.f, Lib::VECTOR2(1, 1), -90);
		}
	};

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		pos.x = static_cast<float>((windowSize.x / 2) - (64 * (STAGE_WIDTH / 2)));
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			DoorDraw(j,i);
			pos.x += 64.f;
		}
		pos.y += 64.f;
	}
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

void Door::InitializeEvent()
{
	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("OpenStartDoor", [this]()
	{
		m_pStartDoorUv->SetAnimCount(1);
	});

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("CloseStartDoor", [this]()
	{
		m_pStartDoorUv->SetAnimCount(0);
	});

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("OpenGoalDoor", [this]()
	{
		m_pGoalDoorUv->SetAnimCount(1);
	});

	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("CloseGoalDoor", [this]()
	{
		m_pGoalDoorUv->SetAnimCount(0);
	});
}
