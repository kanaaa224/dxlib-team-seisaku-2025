#include "DxLib.h"
#include "../Objects/Stage.h"
#include "../Utility/ResourceManager.h"

Stage::Stage()
{
	
}

Stage::~Stage()
{

}

void Stage::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();

	stage_background = rm->GetImages("resource/images/stage/tutorial/layers/Grassy_Mountains_preview.png",1);

	image = stage_background[0];

	if (image == -1) throw("ÉGÉâÅ[\n");

}

void Stage::Update(float delta_second)
{
}

void Stage::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void Stage::Finalize()
{
	stage_background.clear();
}

void Stage::OnHitCollision(GameObjectBase* hit_object)
{
}

