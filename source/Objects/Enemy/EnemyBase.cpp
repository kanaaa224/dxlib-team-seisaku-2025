#include "EnemyBase.h"
#include "../../Utility/InputCtrl.h"//デバック用で入れている（主にデバックキーで）

EnemyBase::EnemyBase() : 
	idle_img(), 
	attackPosition_img(),
	attack_img(),
	getAttack_img(),
	die_img(),
	nowImageNum(0),
	nowState(eEnemyState::IDLE),
	oldState(eEnemyState::NONE),
	nowStateTime(0.0f),
	playerLocation(Vector2D(0.0f)),
	playerFoundFlg(false),
	spawnPosition(Vector2D(0.0f)),
	initUpdateFlg(false),
	max_hp(100.0f),
	hp(100.0f)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
	//当たり判定
	collision.is_blocking = true;
	collision.SetObjectType(eObjectType::enemy);
	collision.SetHitObjectType({ eObjectType::player, eObjectType::enemy, eObjectType::ground });
}

void EnemyBase::Update(float delta_second)
{
	//初期化
	if (initUpdateFlg == false) {
		InitUpdate();
		initUpdateFlg = true;
	}

	collision.SetPosition(location);

	//重力
	//if (location.y <= 720 - 40) {//縦の画面サイズー適当な数字
	//	velocity.y = FALLING_SPEED;
	//}
	//else {
	//	velocity.y = 0;
	//}

#ifdef DEBUG
	if (InputCtrl::GetKeyState(KEY_INPUT_E) == PRESSED && InputCtrl::GetKeyState(KEY_INPUT_0) == PRESSED) {//(E + 0)でhpを0にする
		hp = 0;
	}
	if (InputCtrl::GetKeyState(KEY_INPUT_E) == PRESSED && InputCtrl::GetKeyState(KEY_INPUT_1) == PRESSED) {//(E + 0)でhpを10減らす
		hp -= 10;
	}
#endif // DEBUG

	//locationを更新
	location += velocity;

	Vector2D collisionPosition = collision.GetPosition();

	collision.SetPosition(location);
	collision.SetStartPoint(Vector2D(location.x, location.y - img_size.y));
	collision.SetEndPoint(Vector2D(location.x, location.y + img_size.y));
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

#ifdef DEBUG
	DrawHP();
#endif // DEBUG

}

void EnemyBase::Finalize()
{
}

void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	if (eObjectType::player == hit_object->GetCollision().object_type) {//プレイヤー
		GetDamageMovement(hit_object);//ダメージを受けた時のノックバック処理 ※現在はプレイヤーと当たったらにしているが攻撃判定ができた場合は攻撃中か？の判定も追加する
	}
}

void EnemyBase::Animation(float delta_second)
{
	switch (nowState)
	{
	case IDLE:
		//現在のステートと前フレームのステートが違う場合nowStateTiemを０にする
		if (nowState != oldState) {
			nowStateTime = 0;
			nowImageNum = 0;
		}
		//現在のステートになって何秒経過しているか加算
		nowStateTime += delta_second;
		//現在のステートを更新
		SetEnemyState(IDLE);

		//コンテナの最後の要素数になったら最初の画像の要素数にする
		if (nowImageNum >= idle_img.size()) {
			nowImageNum = 0;
		}

		//画像切り替え
		if (nowStateTime >= IMG_CHANGE_TIME && nowImageNum <= idle_img.size()) {
			image = idle_img[nowImageNum];
			nowStateTime = 0;
			nowImageNum++;
		}
		break;
	case ATTACK_POSITION:
		//現在のステートと前フレームのステートが違う場合nowStateTiemを０にする
		if (nowState != oldState) {
			nowStateTime = 0;
			nowImageNum = 0;
		}
		//現在のステートになって何秒経過しているか加算
		nowStateTime += delta_second;
		//現在のステートを更新
		SetEnemyState(ATTACK_POSITION);

		//コンテナの最後の要素数になったら最初の画像の要素数にする
		if (nowImageNum >= attackPosition_img.size()) {
			nowImageNum = 0;
		}

		//画像切り替え
		if (nowStateTime >= IMG_CHANGE_TIME && nowImageNum <= attackPosition_img.size()) {
			image = attackPosition_img[nowImageNum];
			nowStateTime = 0;
			nowImageNum++;
		}
		break;
	case ATTACK:
		//現在のステートと前フレームのステートが違う場合nowStateTiemを０にする
		if (nowState != oldState) {
			nowStateTime = 0;
			nowImageNum = 0;
		}
		//現在のステートになって何秒経過しているか加算
		nowStateTime += delta_second;
		//現在のステートを更新
		SetEnemyState(ATTACK);

		//コンテナの最後の要素数になったら最初の画像の要素数にする
		if (nowImageNum >= attack_img.size()) {
			nowImageNum = 0;
		}

		//画像切り替え
		if (nowStateTime >= IMG_CHANGE_TIME && nowImageNum <= attack_img.size()) {
			image = attack_img[nowImageNum];
			nowStateTime = 0;
			nowImageNum++;
		}
		break;
	case GET_ATTACK:
		//現在のステートと前フレームのステートが違う場合nowStateTiemを０にする
		if (nowState != oldState) {
			nowStateTime = 0;
			nowImageNum = 0;
		}
		//現在のステートになって何秒経過しているか加算
		nowStateTime += delta_second;
		//現在のステートを更新
		SetEnemyState(GET_ATTACK);

		//コンテナの最後の要素数になったら最初の画像の要素数にする
		if (nowImageNum >= getAttack_img.size()) {
			nowImageNum = 0;
		}

		//画像切り替え
		if (nowStateTime >= IMG_CHANGE_TIME && nowImageNum <= getAttack_img.size()) {
			image = getAttack_img[nowImageNum];
			nowStateTime = 0;
			nowImageNum++;
		}
		break;
	case DIE:
		//現在のステートと前フレームのステートが違う場合nowStateTiemを０にする
		if (nowState != oldState) {
			nowStateTime = 0;
			nowImageNum = 0;
		}
		//現在のステートになって何秒経過しているか加算
		nowStateTime += delta_second;
		//現在のステートを更新
		SetEnemyState(DIE);

		//コンテナの最後の要素数になったら最初の画像の要素数にする
		if (nowImageNum >= die_img.size()) {
			nowImageNum = 0;
		}

		//画像切り替え
		if (nowStateTime >= IMG_CHANGE_TIME && nowImageNum <= die_img.size()) {
			image = die_img[nowImageNum];
			nowStateTime = 0;
			nowImageNum++;
		}
		break;
	default:
		break;
	}
}

void EnemyBase::Movement(float distance)
{
	if (spawnPosition.x <= location.x) {
		velocity.x = -MOVE_SPEED;
		flip_flag = true;
	}
	if (spawnPosition.x - distance >= location.x) {
		velocity.x = MOVE_SPEED;
		flip_flag = false;
	}
}

void EnemyBase::InitUpdate()
{
	//スポーン位置を設定
	spawnPosition = location;
}

void EnemyBase::GetDamageMovement(GameObjectBase* hit_object)
{
	switch (GetCollisionSide(*hit_object))
	{
	case eCollisionSide::top://上方向
		break;
	case eCollisionSide::bottom://下方向
		break;
	case eCollisionSide::left://左方向
		velocity.x = 2.0f;
		velocity.y = 1.0f;
		break;
	case eCollisionSide::right://右方向
		velocity.x = -2.0f;
		velocity.y = 1.0f;
		break;
	default:
		break;
	}

	velocity.x = 2.0f;
	velocity.y = 1.0f;
}

void EnemyBase::HitEnemyMovement(GameObjectBase* hit_object)
{
	switch (GetCollisionSide(*hit_object))
	{
	case eCollisionSide::top://上方向
		break;
	case eCollisionSide::bottom://下方向
		break;
	case eCollisionSide::left://左方向
		velocity.x = 2.0f;
		velocity.y = 1.0f;
		break;
	case eCollisionSide::right://右方向
		velocity.x = -2.0f;
		velocity.y = 1.0f;
		break;
	default:
		break;
	}
}

void EnemyBase::DrawHP() const
{
	//現在のHP割合
	float hp_rate = hp / max_hp;
	float hp_x_size = HP_X_MAXSIZE * hp_rate;

	//
	DrawBox(location.x - img_size.x - (HP_X_MAXSIZE / 3), location.y - img_size.y - collision.radius,
		    (location.x - img_size.x - (HP_X_MAXSIZE / 3)) + hp_x_size, location.y - img_size.y - collision.radius - HP_Y_SIZE,
		    GetColor(255, 0, 0), TRUE);
}

