#include "Flotte.h"

Flotte::Flotte()
{
}

Flotte::~Flotte()
{
}

void Flotte::Initialize()
{
	//ResourceManagerのインスタンスを取得
	ResourceManager* rm = ResourceManager::GetInstance();
	//idle_imgコンテナに画像を格納
	idle_img = rm->GetImages("resource/images/enemy/flotte/idle.png", 4, 4, 1, 20, 20);
	//attackPoition_imgコンテナに画像を格納
	//attackPosition_img = rm->GetImages("");//攻撃姿勢時の画像が用意できたらここに入れる
	//attack_imgコンテナに画像を格納
	//attack_img = rm->GetImages("");//攻撃時の画像が用意できたらここに入れる
	//getAttack_imgコンテナに画像を格納
	//getAttack_img = rm->GetImages("");//攻撃を受けた時の画像が用意できたらここに入れる
	//die_imgコンテナに画像を格納
	//die_img = rm->GetImages("");//死んだ時の画像が用意できたらここに入れる
	//現在の画像を設定
	image = idle_img[0];

	//画像の描画順番
	z_layer = 0;

	//当たり判定の大きさ
	collision.SetSize(20, 20);

	collision.radius = 10;
	//collision.pivot = Vector2D(6.0f);

#ifdef DEBUG
	//当たり判定を表示
	SetDrawCollisionBox(false);
	SetDrawCollisionCircle(true);
#endif // DEBUG

	//現在のステートを設定
	SetEnemyState(IDLE);

	//親クラスのInitializeを実行
	__super::Initialize();
}

void Flotte::Update(float delta_second)
{
}

void Flotte::Draw(const Vector2D& screen_offset) const
{
}

void Flotte::Finalize()
{
}

void Flotte::OnHitCollision(GameObjectBase* hit_object)
{
}

void Flotte::Movement(float distance)
{
}
