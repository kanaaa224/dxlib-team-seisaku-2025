#pragma once
//敵の親クラス
//これを継承して敵を作っていく

#include "../GameObject.h"
#include "../../Utility/Vector2D.h"

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
	int nowState;        //現在の状態
	float nowStateTime;  //現在の状態へ遷移してからの経過時間

	Vector2D hitBoxSize; //当たり判定

	Vector2D fov_BoxSize;//視野範囲
	bool playerFoundFlg; //プレイヤーを発見したか

	int move_img[10];          //移動時の画像
	int attackPosition_img[10];//攻撃姿勢の画像
	int attack_img[10];        //攻撃の画像
	int getAttack_img[10];     //攻撃を受ける画像
	int die_img[10];           //死亡の画像

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObjectBase* hit_object) override;

};

