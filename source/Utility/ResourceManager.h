#pragma once

#include <map>
#include <string>
#include <vector>

class ResourceManager
{
private:
	static ResourceManager* instance;

	std::map<std::string, std::vector<int>> images_container;
	std::map<std::string, int> sounds_container;

private:
	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&) = delete;

public:
	~ResourceManager() = default;

	static ResourceManager* GetInstance();
	static void DeleteInstance();

public:
	const std::vector<int>& GetImages(std::string file_name, int all_num = 1, int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);
	const std::vector<int>& GetImages(const char* file_name, int all_num = 1, int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);

	int GetSounds(std::string file_path);
	int GetSounds(const char* file_path);

	void UnLoadImages();
	void UnLoadSounds();

private:
	void CreateImagesResource(std::string file_path);
	void CreateImagesResource(std::string file_name, int all_num, int num_x, int num_y, int size_x, int size_y);
	void CreateSoundsResource(std::string file_path);
};