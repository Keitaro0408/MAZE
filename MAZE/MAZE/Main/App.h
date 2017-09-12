#ifndef APP_H
#define APP_H
#include "Application\ApplicationBase.h"

#include <array>
#include "SceneManager\SceneManager.h"
#include "SceneManager\SceneBase\SceneBase.h"
#include "SmartPointer\UniquePtr.h"


class App : public Lib::ApplicationBase
{
public:
	enum Scene
	{
		TITLE_SCENE,
		GAME_SCENE,
		NEXT_STAGE_SCENE,
		SCENE_MAX
	};

	App();
	~App() = default;

	void Initialize() override;
	void Finalize() override;

private:
	std::array<Lib::UniquePtr<Lib::SceneBase>, SCENE_MAX> m_pScene;

} App;


#endif
