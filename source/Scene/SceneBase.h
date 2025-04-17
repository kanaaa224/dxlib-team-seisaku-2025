#pragma once

#include "../Objects/GameObjectBase.h"
#include <vector>
#include <string>

enum class eSceneType
{
	title,
	in_game,
	re_start,
	result,
	exit,
};

class SceneBase
{
protected:
	std::vector<GameObjectBase*> create_list;
	std::vector<GameObjectBase*> object_list;
	std::vector<GameObjectBase*> destroy_list;

	Vector2D screen_offset;

public:
	SceneBase() :
		create_list(),
		object_list(),
		destroy_list(),
		screen_offset(0.0f)
	{}

	virtual ~SceneBase()
	{
		Finalize();
	}

public:
	virtual void Initialize() {}

	virtual eSceneType Update(const float& delta_second)
	{
		if (!create_list.empty()) {
			for (GameObjectBase* obj : create_list) {
				int z_layer = obj->GetZLayer();

				std::vector<GameObjectBase*>::iterator itr = object_list.begin();

				for (; itr != object_list.end(); itr++) {
					if (z_layer < (*itr)->GetZLayer()) break;
				}

				object_list.insert(itr, obj);
			}

			create_list.clear();
		}

		for (GameObjectBase* obj : object_list) {
			obj->Update(delta_second);
		}

		for (int i = 0; i < object_list.size(); i++) {
			if (eMobilityType::stationary == object_list[i]->GetMobility()) continue;

			for (int j = 0; j < object_list.size(); j++) {
				if (i == j) continue;

				CheckCollision(object_list[i], object_list[j]);
			}
		}

		if (!destroy_list.empty()) {
			for (GameObjectBase* obj : destroy_list) {
				std::vector<GameObjectBase*>::iterator itr = object_list.begin();
				for (; itr != object_list.end(); itr++) {
					if ((*itr) == obj) {
						object_list.erase(itr);

						obj->Finalize();

						delete obj;

						break;
					}
				}
			}

			destroy_list.clear();
		}

		return GetNowSceneType();
	}

	virtual void Draw() const
	{
		for (GameObjectBase* obj : object_list) {
			obj->Draw(screen_offset);
		}
	}

	virtual void Finalize()
	{
		DestoryAllObject();

		if (!create_list.empty()) create_list.clear();
		if (!destroy_list.empty()) destroy_list.clear();
	}

	virtual const eSceneType GetNowSceneType() const = 0;

	virtual void CheckCollision(GameObjectBase* target, GameObjectBase* partner) {}

public:
	template <class OBJECT>
	OBJECT* CreateObject(const Vector2D& generate_location)
	{
		OBJECT* new_instance = new OBJECT();

		GameObjectBase* new_object = dynamic_cast<GameObjectBase*>(new_instance);

		if (new_object == nullptr) {
			delete new_instance;

			throw std::string("オブジェクトの作成に失敗\n");

			return nullptr;
		}

		new_object->SetOwnerScene(this);
		new_object->Initialize();
		new_object->SetLocation(generate_location);

		create_list.push_back(new_object);

		return new_instance;
	}

	void DestroyObject(GameObjectBase* target)
	{
		if (target == nullptr) return;

		for (GameObjectBase* obj : destroy_list) {
			if (obj == target) return;
		}

		destroy_list.push_back(target);
	}

	const Vector2D GetScreenOffset() const
	{
		return screen_offset;
	}

private:
	void DestoryAllObject()
	{
		if (object_list.empty()) return;

		for (GameObjectBase* obj : object_list) {
			obj->Finalize();

			delete obj;
		}

		object_list.clear();
	}
};