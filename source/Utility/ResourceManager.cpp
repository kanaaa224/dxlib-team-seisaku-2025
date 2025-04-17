#include "ResourceManager.h"
#include "DxLib.h"

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager* ResourceManager::GetInstance()
{
	if (instance == nullptr) instance = new ResourceManager();

	return instance;
}

void ResourceManager::DeleteInstance()
{
	if (instance != nullptr) {
		instance->UnLoadImages();
		instance->UnLoadSounds();

		delete instance;

		instance = nullptr;
	}
}

const std::vector<int>& ResourceManager::GetImages(std::string file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	if (images_container.count(file_name) == NULL) {
		if (all_num == 1) {
			CreateImagesResource(file_name);
		}
		else {
			CreateImagesResource(file_name, all_num, num_x, num_y, size_x, size_y);
		}
	}

	return images_container[file_name];
}

const std::vector<int>& ResourceManager::GetImages(const char* file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	return GetImages(std::string(file_name), all_num, num_x, num_y, size_x, size_y);
}

int ResourceManager::GetSounds(std::string file_path)
{
	if (sounds_container.count(file_path) == NULL) CreateSoundsResource(file_path);

	return sounds_container[file_path];
}

int ResourceManager::GetSounds(const char* file_path)
{
	return GetSounds(std::string(file_path));
}

void ResourceManager::UnLoadImages()
{
	if (images_container.size() == NULL) return;

	for (std::pair<std::string, std::vector<int>> value : images_container) {
		DeleteSharingGraph(value.second[0]);

		value.second.clear();
	}

	images_container.clear();
}

void ResourceManager::UnLoadSounds()
{
	if (sounds_container.size() == NULL) return;

	for (std::pair<std::string, int> value : sounds_container) {
		DeleteSoundMem(value.second);
	}

	sounds_container.clear();
}

void ResourceManager::CreateImagesResource(std::string file_path)
{
	int handle = LoadGraph(file_path.c_str());

	if (handle == -1) throw (file_path + " の読み込みに失敗\n");

	images_container[file_path].push_back(handle);
}

void ResourceManager::CreateImagesResource(std::string file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	int* handle = new int[all_num];

	int result = LoadDivGraph(file_name.c_str(), all_num, num_x, num_y, size_x, size_y, handle);

	if (result == -1) throw (file_name + " の読み込みに失敗\n");

	for (int i = 0; i < all_num; i++) {
		images_container[file_name].push_back(handle[i]);
	}

	delete[] handle;
}

void ResourceManager::CreateSoundsResource(std::string file_path)
{
	int handle = LoadSoundMem(file_path.c_str());

	if (handle == -1) throw (file_path + " の読み込みに失敗\n");

	sounds_container[file_path] = handle;
}