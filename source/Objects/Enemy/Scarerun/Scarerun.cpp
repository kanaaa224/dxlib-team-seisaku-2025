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
	ResourceManager* rm = ResourceManager::GetInstance();

	idle_img = rm->GetImages("resource/images/enemy/scarerun/idle.png", 4, 4, 1, 46, 40);

	image = idle_img[0];

	z_layer = 0;

	collision.is_blocking = true;
	collision.SetSize(46, 40);
	//collision.pivot = Vector2D(6.0f);
	collision.SetObjectType(eObjectType::enemy);
	collision.SetHitObjectType({ eObjectType::player, eObjectType::enemy, eObjectType::ground });

	SetDrawCollisionBox(true);

	__super::Initialize();
}

void Scarerun::Update(float delta_second)
{
	__super::Update(delta_second);
}

void Scarerun::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);

#ifdef DEBUG
	
#endif // DEBUG
}

void Scarerun::Finalize()
{
	//画像解放
	idle_img.clear();

	__super::Finalize();
}

void Scarerun::OnHitCollision(GameObjectBase* hit_object)
{
}
