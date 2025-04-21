#include "Scarerun.h"

Scarerun::Scarerun()
{
}

Scarerun::~Scarerun()
{
}

void Scarerun::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	move_img = rm->GetImages("resource/images/enemy/scarerun/idle.png", 4, 4, 1, 46, 40);

	image = move_img[0];
}

void Scarerun::Update(float delta_second)
{
}

void Scarerun::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Scarerun::Finalize()
{
	//‰æ‘œ‰ð•ú
	move_img.clear();
}

void Scarerun::OnHitCollision(GameObjectBase* hit_object)
{
}
