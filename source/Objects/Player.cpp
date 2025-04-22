#include "Player.h"
#include "../Utility/ResourceManager.h"
//#include "../Utility/StageData.h"
#include "../Utility/InputCtrl.h"
#include "DxLib.h"

#define D_PLAYER_SPEED	(50.0f) //プレイヤー速度
#define D_GRAVITY (9.807f) //重力

Player* Player::instance = nullptr; //インスタンス生成

Player::Player() :
	move_animation(),
	jump_animation(),
	dying_animation(),
	velocity(0.0f), //移動量
	player_state(ePlayerState::idle), //プレイヤーの状態
	now_direction_state(eDirectionState::left), //現在の状態
	next_direction_state(eDirectionState::left), //次状態
	animation_time(0.0f),
	player(nullptr),
	scroll_end(false),
	jump_location(Vector2D(0.0f)),
	jump_velocity(Vector2D(0.0f))
{}

Player::~Player() {}

void Player::Initialize()
{
	//インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	move_animation[0] = LoadGraph("resource/images/player/idle/01_idle_1.png");
	//move_animation[0] = rm->GetImages("resource/images/player/idle/01_idle_1.png", 9, 9, 1, 32, 32);
	//move_animation[1] = rm->GetImages("resource/images/player/01_idle_2.png", 9, 9, 1, 32, 32)[1];
	//move_animation[2] = rm->GetImages("resource/images/player/01_idle_3.png", 9, 9, 1, 32, 32);
	//move_animation[3] = rm->GetImages("resource/images/player/01_idle_4.png", 9, 9, 1, 32, 32);
	//move_animation[4] = rm->GetImages("resource/images/player/01_idle_5.png", 9, 9, 1, 32, 32);
	//move_animation[5] = rm->GetImages("resource/images/player/01_idle_6.png", 9, 9, 1, 32, 32);
	//move_animation[6] = rm->GetImages("resource/images/player/01_idle_7.png", 9, 9, 1, 32, 32);
	//move_animation = rm->GetImages("resource/images/player/xxx.png", 9, 9, 1, 32, 32);
	//jump_animation = rm->GetImages("resource/images/player/xxx.png", 9, 9, 1, 32, 32);

	//jump_SE = rm->GetSounds("resource/sounds/xxx.wav");

	collision.SetSize(D_OBJECT_SIZE, D_OBJECT_SIZE);  //サイズ設定

	collision.SetObjectType(eObjectType::player);  //オブジェクト設定

	collision.SetHitObjectType({ eObjectType::enemy, eObjectType::ground });  //hitオブジェクトタイプ

	SetDrawCollisionBox(true);  //当たり判定大きさ取得

	z_layer = 5;  //レイヤー設定

	mobility = eMobilityType::movable;  //

	is_on_ground = true;   //地面についたかどうか
	scroll_offset = 0.0f;
	ground_y = 400.0f;

	image = move_animation[0];  //初期イメージ設定

	if (image == -1) throw("エラー\n");  //エラーチェック
}

void Player::Update(float delta_second)
{
	//プレイヤーがジャンプ状態のとき
	if (player_state == ePlayerState::jump)
	{
		JumpMoment(delta_second);
	}

	if (!is_on_ground) velocity.y += D_GRAVITY* delta_second;   //重力速度の計算

	////後で聞くやつ
	//if (location.y + velocity.y * delta_second >= ground_y) {
	//	location.y = ground_y;

	//	velocity.y = 0.0f;
	//	g_velocity = 0.0f;

	//	is_on_ground = true;

	//	player_state = ePlayerState::idle;
	//}

	Vector2D collisionPosition = collision.GetPosition();

	collision.SetPosition(location);

	//プレイヤーの状態ごとの処理
	switch (player_state) {
	case ePlayerState::idle: //idle状態の処理
		image = move_animation[0];

		velocity.x = 0;

		if (
			InputCtrl::GetKeyState(KEY_INPUT_A) ||
			InputCtrl::GetKeyState(KEY_INPUT_D) ||
			InputCtrl::GetKeyState(KEY_INPUT_LEFT) ||
			InputCtrl::GetKeyState(KEY_INPUT_RIGHT)||

			InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_LEFT) ||
			InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_RIGHT)
		) {
			player_state = ePlayerState::move;
		}
		else if (InputCtrl::GetKeyState(KEY_INPUT_SPACE) || InputCtrl::GetButtonState(XINPUT_BUTTON_A)) 
		{
			player_state = ePlayerState::jump;

			//PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
		}

		break;

	case ePlayerState::move: //移動処理
		Movement(delta_second);

		AnimationControl(delta_second);

		break;

	case ePlayerState::die: //死亡処理
		animation_time += delta_second;

		if (animation_time >= 0.07f) {
			animation_time = 0.0f;

			animation_count++;

			if (animation_count >= dying_animation.size()) {
				player_state = ePlayerState::idle;

				animation_count = 0;

				is_destroy = true;
			}
		}

		image = dying_animation[animation_count];

		break;

	case ePlayerState::damage: //ダメージを受けた時の処理
		animation_time += delta_second;

		break;

	case ePlayerState::jump: //ジャンプ状態の処理

		//Movement(delta_second);
		//PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);

		if (!is_on_ground) velocity.y += D_GRAVITY * delta_second;  //重力速度計算

		//地面についた時の処理
		if (location.y + velocity.y * delta_second > ground_y) {

			location.y = ground_y;

			velocity.y = 0.0f;
			g_velocity = 0.0f;

			is_on_ground = true;

			player_state = ePlayerState::idle;
		}


		/*Vector2D collisionPosition = collision.GetPosition();
		collision.SetPosition(location);*/

		break;

	default:
		break;
	}

	if (location.x < 16.0f) location.x = 16.0f;

	/*if (scroll_end == false) {
		if (location.x >= 640.0f / 2) location.x = 640.0f / 2;
	}
	else {
		if (location.x > 600.0f) location.x = 600.0f;
	}*/

	location += velocity; //移動量加算
}

void Player::Draw(const Vector2D& screen_offset) const  //描画処理
{
	DrawFormatString(0, 120, GetColor(255, 255, 255), "PlayerState: %0.0f", velocity.y);
	__super::Draw(screen_offset);
}

void Player::Finalize() //終了時処理
{
	//move_animation.clear();
	DeleteGraph(move_animation[0]);
	dying_animation.clear();
}

void Player::OnHitCollision(GameObjectBase* hit_object) //当たった時
{
	/*
	
	if (hit_object->GetCollision().object_type == eObjectType::wall) {
		CapsuleCollision hc = hit_object->GetCollision();

		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		Vector2D near_point = NearPointCheck(hc, this->location);

		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		location += dv.Normalize() * diff;
	}

	if (hit_object->GetCollision().object_type == eObjectType::food) food_count++;

	if (hit_object->GetCollision().object_type == eObjectType::power_food) {
		food_count++;
		is_power_up = true;
	}

	if (hit_object->GetCollision().object_type == eObjectType::enemy) {}

	*/
}

ePlayerState Player::GetPlayerState() const
{
	return player_state;
}

bool Player::GetPowerUp() const
{
	return is_power_up;
}

void Player::SetPowerDown()
{
	is_power_up = false;
}

bool Player::GetDestroy() const
{
	return is_destroy;
}

void Player::Movement(float delta_second)
{
	//移動処理
	if (
		InputCtrl::GetKeyState(KEY_INPUT_A) ||
		InputCtrl::GetKeyState(KEY_INPUT_LEFT) ||

		InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_LEFT)
	) {
		velocity.x = -1.0f;

		flip_flag = true;

		if (
			InputCtrl::GetKeyState(KEY_INPUT_SPACE) ||

			InputCtrl::GetButtonState(XINPUT_BUTTON_A)
		) {
			player_state = ePlayerState::jump;
			animation_time += delta_second;


			//アニメーション設定
			if (animation_time >= (1.0f / 8.0f)) {
				animation_time = 0.0f;

				animation_count++;

				if (animation_count >= 2) animation_count = 0;

				image = jump_animation[jump_animation_num[animation_count]];
			}

			//PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
		}

		player_state = ePlayerState::move;
	}

	else if (InputCtrl::GetKeyState(KEY_INPUT_D) || InputCtrl::GetKeyState(KEY_INPUT_RIGHT) || InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_RIGHT)) {
		velocity.x = 1.0f;

		flip_flag = false;

		if (
			InputCtrl::GetKeyState(KEY_INPUT_SPACE) ||

			InputCtrl::GetButtonState(XINPUT_BUTTON_A)
		) {
			player_state = ePlayerState::jump;

			animation_time += delta_second;

			if (animation_time >= (1.0f / 8.0f)) {
				animation_time = 0.0f;

				animation_count++;

				if (animation_count >= 2) animation_count = 0;

				image = jump_animation[jump_animation_num[animation_count]];
			}

			//PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
		}

		player_state = ePlayerState::move;
	}

	else if (InputCtrl::GetKeyState(KEY_INPUT_SPACE) ||InputCtrl::GetButtonState(XINPUT_BUTTON_A)) {
		animation_time += delta_second;

		if (animation_time >= (1.0f / 8.0f)) {
			animation_time = 0.0f;

			animation_count++;

			if (animation_count >= 2) animation_count = 0;

			image = jump_animation[jump_animation_num[animation_count]];
		}

		player_state = ePlayerState::jump;

		//PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
	}
	else {
		velocity.x = 0;

		player_state = ePlayerState::idle;
	}
}

void Player::JumpMoment(float delta_second)
{
	//ジャンプ移動処理
	if ((
		InputCtrl::GetKeyState(KEY_INPUT_SPACE) ||

		InputCtrl::GetButtonState(XINPUT_BUTTON_A)
	) && is_on_ground == true) {
		velocity.y = -4.0f;

		JumpAnimationControl(delta_second);

		player_state = ePlayerState::jump;

		is_on_ground = false;

		if (player_state == ePlayerState::jump)
		{
			this->velocity.y -= 1.0f; //ジャンプ力
		}

		//PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
	}
}

void Player::AnimationControl(float delta_second)
{
	//animation_time += delta_second;

	//if (animation_time >= (1.0f / 8.0f)) {
	//	animation_time = 0.0f;

	//	animation_count++;

	//	if (animation_count >= 4) animation_count = 0;

	//	image = move_animation[animation_num[animation_count]];
	//}
}

void Player::WalkAnimationControl(float delta_second)
{
	animation_time += delta_second;

	if (animation_time >= (1.0f / 8.0f)) {
		animation_time = 0.0f;

		animation_count++;

		if (animation_count >= 4) animation_count = 0;

		image = move_animation[animation_num[animation_count]];
	}
}

void Player::JumpAnimationControl(float delta_second)
{
	animation_time += delta_second;

	if (animation_time >= (1.0f / 8.0f)) {
		animation_time = 0.0f;

		animation_count++;

		if (animation_count >= 2) animation_count = 0;

		image = jump_animation[jump_animation_num[animation_count]];
	}

	//PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
}

Player* Player::GetInstance()
{
	if (instance == nullptr) instance = new Player();

	return instance;
}

const Vector2D& Player::GetVelocity() const
{
	return velocity;
}

void Player::SetScrollEnd()
{
	scroll_end = true;
}

ePlayerState Player::PlayerState()
{
	return player_state;
}