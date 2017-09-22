/**
 * @file   TimerUI.h
 * @brief  TimerUIクラスのヘッダファイル
 * @author kotani
 */
#ifndef TIMER_H 
#define TIMER_H
#include "../UIObjectBase.h"
#include <array>
#include "Animation\AnimUvController.h"
#include "SmartPointer\UniquePtr.h"
#include "Animation\AnimUvController.h"
#include "Vertex2D\Vertex2D.h"

class TimerUIEventListener;

class TimerUI : public UIObjectBase
{
	friend TimerUIEventListener;
public:
	TimerUI();
	virtual ~TimerUI();

	void Update() override;
	void Draw() override;

private:
	bool								  m_IsStart;
	Lib::VECTOR2						  m_Pos; //!< 数字の1桁目の描画する位置
	Lib::UniquePtr<Lib::Vertex2D>		  m_pVertex;
	Lib::UniquePtr<Lib::AnimUvController> m_pUvController; 
	Lib::UniquePtr<TimerUIEventListener>  m_pTimerUIEventListener;
	int									  m_Count;
	int									  m_Time; //!< ステージ開始から何秒経ったか?

};


#endif
