#include"DxLib.h"
#include"Scene/SceneManager.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCm)
{
	SceneManager* scene_manager = nullptr;

	int result = 0;

	try {
		scene_manager = new SceneManager();

		scene_manager->WakeUp();
		scene_manager->Run();
		scene_manager->Shutdown();
	}
	catch (const char* error_log) {
		OutputDebugString(error_log);

		result = -1;
	}

	if (scene_manager != nullptr) {
		scene_manager->Shutdown();

		delete scene_manager;

		scene_manager = nullptr;
	}

	return result;
}