/**
 * @file   UIObjectManager.h
 * @brief  UIObjectManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef UIOBJECTMANAGER_H
#define UIOBJECTMANAGER_H
#include <array>
#include "SmartPointer\UniquePtr.h"

class UIObjectBase;

class UIObjectManager
{
public:
	UIObjectManager();
	~UIObjectManager();

private:
	std::array<Lib::UniquePtr<UIObjectBase>, 2> m_pUIObjectBase;

};


#endif
