#pragma once

#include "GameObjectBase.h"
#include "../Scene/SceneBase.h"
#include "../Utility/Vector2D.h"

class GameObject : public GameObjectBase
{
public:
	template <class OBJECT>
	OBJECT* CreateObject(const Vector2D& generate_location)
	{
		return owner_scene->CreateObject<OBJECT>(generate_location);
	}

	void DestroyObject(GameObjectBase* target)
	{
		owner_scene->DestroyObject(target);
	}

	const Vector2D GetScreenOffset() const
	{
		return owner_scene->GetScreenOffset();
	}
};