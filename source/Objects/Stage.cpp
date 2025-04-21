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

	stage_background = rm->GetImages("resource/images/stage/stage1/back_color.png",1);
	std::vector<int> temp = rm->GetImages("resource/images/stage/stage1/middle.png", 1);
	stage_background.push_back(temp[0]);
	temp = rm->GetImages("resource/images/stage/stage1/front.png", 1);
	stage_background.push_back(temp[0]);

	//image = stage_background[0];

	for (int i = 0; i < 3; i++)
	{
		if (stage_background[i] == -1)
		{
			throw("エラー\n");
		}
	}

	temp.clear();
}

void Stage::Update(float delta_second)
{
	Player* player = Player::GetInstance();

	//player->GetVelocity().x 
}

void Stage::Draw(const Vector2D& screen_offset) const
{
	DrawGraph(0, 0, stage_background[0], TRUE);
	DrawGraph(0, 0, stage_background[1], TRUE);
	DrawGraph(0, 0, stage_background[2], TRUE);
	__super::Draw(screen_offset);
}

void Stage::Finalize()
{
	stage_background.clear();
}

void Stage::OnHitCollision(GameObjectBase* hit_object)
{
}

