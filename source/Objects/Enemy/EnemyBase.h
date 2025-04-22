#pragma once
//敵の親クラス
//これを継承して敵を作っていく

#include "../GameObject.h"
#include "../../Utility/Vector2D.h"
#include "../../Utility/ResourceManager.h"

#define DEBUG

enum eEnemyState
{
	IDLE,           //待機状態
	ATTACK_POSITION,//攻撃姿勢状態
	ATTACK,         //攻撃状態
	GET_ATTACK,     //攻撃を受ける状態
	DIE             //死亡状態
};

class EnemyBase : public GameObject
{
protected:
	eEnemyState nowState;//現在の状態
	eEnemyState oldState;//1フレーム前の状態
	float nowStateTime;  //現在の状態へ遷移してからの経過時間

	Vector2D fov_BoxSize;//視野範囲
	bool playerFoundFlg; //プレイヤーを発見したか

	std::vector<int> idle_img;          //移動時の画像
	std::vector<int> attackPosition_img;//攻撃姿勢の画像
	std::vector<int> attack_img;        //攻撃の画像
	std::vector<int> getAttack_img;     //攻撃を受ける画像
	std::vector<int> die_img;           //死亡の画像

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObjectBase* hit_object) override;

protected:
	virtual void Animation(float delta_second);
};

