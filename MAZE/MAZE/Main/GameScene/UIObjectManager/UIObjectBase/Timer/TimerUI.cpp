/**
 * @file   TimerUI.cpp
 * @brief  TimerUIクラスの実装
 * @author kotani
 */
#include "TimerUI.h"
#include "Texture\TextureManager.h"
#include "..\..\..\..\ResourceId.h"

#include "Dx11\DX11Manager.h"
#include "Window\Window.h"
#include "Event\EventManager.h"


TimerUI::TimerUI() :
m_Pos(Lib::VECTOR2(1700,120)),
m_Time(0),
m_Count(0),
m_IsStart(false)
{
	m_pUvController = new Lib::AnimUvController();
	m_pUvController->LoadAnimation("Resource\\GameScene\\Texture\\Texture.anim","Number");
	m_pVertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	m_pVertex->Initialize(Lib::VECTOR2(41, 64), m_pUvController->GetUV());
	m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(ResourceId::Game::UNITY_TEX));
	
	SINGLETON_INSTANCE(Lib::EventManager).AddEvent("GameStart", [this]()
	{
		m_IsStart = true;
	});

	InitializeTask();
}

TimerUI::~TimerUI()
{
	FinalizeTask();
	m_pVertex->Finalize();
}

void TimerUI::Update()
{
	if (!m_IsStart) return;
	if (m_Count == 60)
	{
		m_Time++;
		m_Count = 0;
	}
	m_Count++;
}

void TimerUI::Draw()
{
	auto Multiply10 = [](int _num)
	{
		int num = 1;
		for (int i = 0; i < _num; i++)
		{
			num *= 10;
		}
		return num;
	};

	auto GetDigit = [](int _num)
	{
		int digit = 0;
		while (_num != 0)
		{
			_num /= 10;
			digit++;
		}
		return digit;
	};

	auto NumDraw = [this](int _num, const Lib::VECTOR2& _pos)
	{
		m_pUvController->SetAnimCount(_num);
		m_pVertex->Draw(_pos, m_pUvController->GetUV());
	};

	int num = 0;

	for (int i = 1; i <= GetDigit(m_Time); i++)
	{
		num = (m_Time / Multiply10(i - 1)) % 10;
		NumDraw(num, Lib::VECTOR2(m_Pos.x - (41 * (i - 1)), m_Pos.y));
	}
}
