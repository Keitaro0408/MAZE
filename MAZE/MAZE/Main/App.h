#ifndef APP_H
#define APP_H
#include "Application\ApplicationBase.h"
#include "SceneManager\SceneManager.h"
#include "SceneManager\SceneBase\SceneBase.h"
#include <vector>

class App : public Lib::ApplicationBase
{
public:
	enum Scene
	{
		TITLE_SCENE,
		GAME_SCENE,
		SCENE_MAX
	};

	App();
	~App() = default;

	void Initialize() override;
	void Finalize() override;

private:
	std::vector<Lib::SceneBase*> m_pScene;

} App;


#endif
