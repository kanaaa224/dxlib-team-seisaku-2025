#pragma once

#include "../Utility/Vector2D.h"
#include "../Utility/Collision.h"

#define D_OBJECT_SIZE (32.0f)

enum eMobilityType
{
	stationary,
	movable,
};

enum class eCollisionSide
{
	top,
	bottom,
	left,
	right,
	none
};

enum eType
{
	player,
	enemy
};

class GameObjectBase
{
protected:
	class SceneBase* owner_scene;

	Vector2D location;
	Vector2D velocity;

	Collision collision;

	int image;
	int z_layer;
	int type;

	eMobilityType mobility;

	bool flip_flag;
	bool draw_collision_box;
	bool flag;

public:
	GameObjectBase();
	virtual ~GameObjectBase();

	virtual void Initialize();

	virtual void Update(float delta_second);

	virtual void Draw(const Vector2D& screen_offset) const;

	virtual void DrawCollision(const Vector2D& screen_offset) const;

	virtual void Finalize();


public:
	virtual void OnHitCollision(GameObjectBase* hit_object);

	eCollisionSide GetCollisionSide(const GameObjectBase& other) const;

public:
	void SetOwnerScene(class SceneBase* scene);

	const Vector2D& GetLocation() const;

	void SetLocation(const Vector2D& location);

	Collision GetCollision() const;

	const int GetZLayer() const;

	const eMobilityType GetMobility() const;

	void SetDrawCollisionBox(bool flag);
};