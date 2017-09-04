/**
 * @file   UIObjectManager.cpp
 * @brief  UIObjectManagerクラスの実装
 * @author kotani
 */
#include "UIObjectManager.h"
#include "UIObjectBase\Timer\TimerUI.h"


UIObjectManager::UIObjectManager()
{
	m_pUIObjectBase[0] = new TimerUI();
}


UIObjectManager::~UIObjectManager()
{
}
