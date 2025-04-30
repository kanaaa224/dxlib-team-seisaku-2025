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
	//現在の画像を設定
	image = idle_img[0];

	//画像の描画順番
	z_layer = 0;

	//当たり判定の大きさ
	collision.SetSize(46, 40);

	collision.radius = 23;
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

void Scarerun::Update(float delta_second)
{
	__super::Update(delta_second);

	if (nowState == IDLE) {
		Movement(30.0f);
	}
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

void Scarerun::Animation(float delta_second)
{
	__super::Animation(delta_second);
}

void Scarerun::Movement(float distance)
{
	__super::Movement(distance);
}

void Scarerun::InitUpdate()
{
	__super::InitUpdate();
}
