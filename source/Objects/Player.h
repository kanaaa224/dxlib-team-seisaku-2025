#pragma once

#include "GameObject.h"
#include "../Utility/Vector2D.h"

enum ePlayerState
{
	idle,
	move,
	die,
	damage,
	jump,
};

class Player : public GameObject
{
private:
	enum eDirectionState : unsigned char
	{
		up,
		right,
		down,
		left,
		none,
	};

private:
	std::vector<int> move_animation;
	std::vector<int> jump_animation;
	std::vector<int> dying_animation;

	Vector2D old_location;
	Vector2D velocity;

	Vector2D jump_location;
	Vector2D jump_velocity;

	eDirectionState now_direction_state;
	eDirectionState next_direction_state;
	float animation_time;

	bool is_power_up;
	bool is_destroy;
	float scroll_offset;
	bool is_on_ground;
	float ground_y;

	const int animation_num[4] = { 1, 2, 3, 2, };
	const int jump_animation_num[2] = { 1,5 };

	int animation_count;
	bool scroll_end;
	int g_velocity;
	int jump_SE;

	Player* player;

public:
	int screenoffset;

	ePlayerState player_state;

	static Player* GetInstance();

private:
	static Player* instance;

public:
	Player();
	virtual ~Player();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	//void Draw(float sscreen_offsetcre);

	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	ePlayerState GetPlayerState() const;
	bool GetPowerUp() const;
	void SetPowerDown();
	bool GetDestroy() const;
	const Vector2D& GetVelocity() const;
	void SetScrollEnd();
	ePlayerState PlayerState();

private:
	void Movement(float delta_second);
	void AnimationControl(float delta_second);
	void JumpMoment(float delta_second);
	void WalkAnimationControl(float delta_second);
	void JumpAnimationControl(float delta_second);
};