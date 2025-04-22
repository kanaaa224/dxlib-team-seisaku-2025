#pragma once
//敵の親クラス
//これを継承して敵を作っていく

#include "../GameObject.h"
#include "../../Utility/Vector2D.h"
#include "../../Utility/ResourceManager.h"

#define DEBUG                 //デバック表示
#define IMG_CHANGE_TIME 0.05f //画像の切り替え速度
#define MOVE_SPEED 1.0f       //移動速度

enum eEnemyState
{
	NONE,           //何もなし
	IDLE,           //待機状態
	ATTACK_POSITION,//攻撃姿勢状態
	ATTACK,         //攻撃状態
	GET_ATTACK,     //攻撃を受ける状態
	DIE             //死亡状態
};

class EnemyBase : public GameObject
{
protected:
	eEnemyState nowState;               //現在の状態
	eEnemyState oldState;               //1フレーム前の状態
	float nowStateTime;                 //現在の状態へ遷移してからの経過時間

	Vector2D fov_BoxSize;               //視野範囲
	bool playerFoundFlg;                //プレイヤーを発見したか

	std::vector<int> idle_img;          //移動時の画像
	std::vector<int> attackPosition_img;//攻撃姿勢の画像
	std::vector<int> attack_img;        //攻撃の画像
	std::vector<int> getAttack_img;     //攻撃を受ける画像
	std::vector<int> die_img;           //死亡の画像
	int nowImageNum;                    //画像配列の現在の要素数を格納する用

	Vector2D spawnPosition;             //スポーン位置を格納

	bool initUpdateFlg;

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObjectBase* hit_object) override;

protected:
	/// <summary>
	/// ステートに合わせて画像を切り替える
	/// </summary>
	/// <param name="delta_second">1フレーム何秒経過したか</param>
	virtual void Animation(float delta_second);
	/// <summary>
	/// 敵のステートをセット
	/// </summary>
	/// <param name="setState"></param>
	virtual void SetEnemyState(eEnemyState setState) { 
		oldState = nowState; 
		nowState = setState;
	};
	/// <summary>
	/// 基本的な左右移動
	/// ※飛行する敵などは書き換える
	/// スポーン位置を始点に引数に入れたdistance分移動したら、
	/// 始点に方向転換して移動する
	/// </summary>
	/// <param name="distance"></param>
	virtual void Movement(float distance);
	/// <summary>
	/// Update内で１回のみ初期化したい変数
	/// </summary>
	virtual void InitUpdate();
};

