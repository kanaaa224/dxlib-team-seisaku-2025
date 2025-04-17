#pragma once

#include "SceneBase.h"

class SceneManager
{
private:
	SceneBase* current_scene;

public:
	SceneManager();
	~SceneManager();

	void WakeUp();
	void Run();
	void Shutdown();

private:
	void Graph() const;
	void ChangeScene(eSceneType next_type);
	SceneBase* CreateScene(eSceneType next_type);
};