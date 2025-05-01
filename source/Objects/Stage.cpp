#include "DxLib.h"
#include "../Objects/Stage.h"
#include "../Utility/ResourceManager.h"

#include "Player.h"

Stage::Stage(): stage_background(), draw_count(0)
{
	
}

Stage::~Stage()
{

}

void Stage::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	stage_background = rm->GetImages("resource/images/stage/stage1/forest.png",1);

	image = stage_background[0];

	if (image == -1)
	{
		throw("画像Errer");
	}
}

void Stage::Update(float delta_second)
{
	//velocity.x = 1;

	location += velocity;
}

void Stage::Draw(const Vector2D& screen_offset) const
{

	//DrawGraph(0 - screen_offset.x, )

	__super::Draw(screen_offset);

	DrawRotaGraphF(location.x + 1280, location.y, 1.0, 0.0, image, TRUE, this->flip_flag); // 仮

	DrawFormatString(0, 200, GetColor(255, 255, 255), "location: %f", location.x);
	DrawFormatString(0, 220, GetColor(255, 255, 255), "velocity: %f", velocity.x);
}

void Stage::Finalize()
{
	stage_background.clear();
}

void Stage::OnHitCollision(GameObjectBase* hit_object)
{
}

