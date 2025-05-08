#include "Scarerun.h"
#include "DxLib.h"

Scarerun::Scarerun()
{
}

Scarerun::~Scarerun()
{
}

void Scarerun::Initialize()
{
	//ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	//idle_imgコンテナに画像を格納
	idle_img = rm->GetImages("resource/images/enemy/scarerun/idle.png", 4, 4, 1, 46, 40);
	//attackPoition_imgコンテナに画像を格納
	//attackPosition_img = rm->GetImages("");//攻撃姿勢時の画像が用意できたらここに入れる
	//attack_imgコンテナに画像を格納
	//attack_img = rm->GetImages("");//攻撃時の画像が用意できたらここに入れる
	//getAttack_imgコンテナに画像を格納
	//getAttack_img = rm->GetImages("");//攻撃を受けた時の画像が用意できたらここに入れる
	//die_imgコンテナに画像を格納
	die_img = rm->GetImages("resource/images/enemy/scarerun/idle.png", 4, 4, 1, 46, 40);//死んだ時の画像が用意できたらここに入れる
	
	//画像サイズ
	img_size = Vector2D(10, 5);

	//現在の画像を設定
	image = idle_img[0];

	//画像の描画順番
	z_layer = 0;

	//当たり判定の大きさ
	collision.SetSize(46, 40);

	collision.radius = 20;
	//collision.pivot = Vector2D(6.0f);
	
#ifdef DEBUG
	//当たり判定を表示
	SetDrawCollisionBox(false);
	SetDrawCollisionCircle(false);
	SetDarwCollisionCapsule(true);
#endif // DEBUG

	//現在のステートを設定
	SetEnemyState(IDLE);

	//親クラスのInitializeを実行
	__super::Initialize();
}

void Scarerun::Update(float delta_second)
{
	__super::Update(delta_second);

	if (nowState == IDLE) {
		Movement(30.0f);//左右移動
	}
	//if (hp <= 0) {//hpが０の時
	//	nowState = DIE;
	//}

	Animation(delta_second);
}

void Scarerun::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Scarerun::Finalize()
{
	//画像解放
	idle_img.clear();

	__super::Finalize();
}

void Scarerun::OnHitCollision(GameObjectBase* hit_object)
{
	__super::OnHitCollision(hit_object);
}

void Scarerun::Movement(float distance)
{
	__super::Movement(distance);
}
