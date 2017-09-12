#include "SceneBase.h"
#include "..\SceneManager.h"

namespace Lib
{
	SceneBase::SceneBase(std::string _sceneName) :
		m_SceneName(_sceneName)
	{
		SINGLETON_INSTANCE(SceneManager).AddScene(this);
	}
}