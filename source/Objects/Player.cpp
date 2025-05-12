#include "Player.h"
#include "../Utility/ResourceManager.h"
//#include "../Utility/StageData.h"
#include "../Utility/InputCtrl.h"
#include "DxLib.h"

#define D_PLAYER_SPEED	(50.0f) //プレイヤー速度
#define D_GRAVITY (9.807f) //重力

#define IDLE_ANIMATION_RATE (0.1f)  //アニメーション速度
#define MOVE_ANIMATION_RATE (0.3f)
#define ROLL_ANIMATION_RATE (0.01f)
#define JUMP_ANIMATION_RATE (0.01f)
#define ATTACK_ANIMATION_RATE (0.01f)

#define VELOCITY (4.0f)  //移動量
#define ADDJUMP (1) //

Player* Player::instance = nullptr; //インスタンス生成

Player::Player() :
	run_animation(),
	idle_animation(),
	//jump_animation(),
	//dying_animation(),
	attack_animation(),
	jump_attack_flg(false),
	velocity(0.0f), //移動量
	player_state(ePlayerState::idle), //プレイヤーの状態
	animation_time(0.0f),
	animation_count(0),
	player(nullptr),
	scroll_end(false),
	p_hp(100)
{}

Player::~Player() {}

void Player::Initialize()
{
	//インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	//image画像
	idle_animation = rm->GetImages("resource/images/player/idle/03_idle.png", 8, 8, 1, 288, 45);
	run_animation = rm->GetImages("resource/images/player/run/run_288_45_8.png", 8, 8, 1, 288, 45);
	attack_animation = rm->GetImages("resource/images/player/attack1/atk_288_45.png", 6, 6, 1, 288, 45);
	jump_animation = rm->GetImages("resource/images/player/jump_up/jump_up2.png", 7, 7, 1, 288, 60);
	avoidance_animation = rm->GetImages("resource/images/player/roll/roll_288_45_7.png", 7, 7, 1, 288, 45);

	//jump_SE = rm->GetSounds("resource/sounds/xxx.wav");

	//collision.SetSize(D_OBJECT_SIZE, D_OBJECT_SIZE);  //サイズ設定

	collision.is_blocking = true; //ブロックするかどうか

	collision.SetObjectType(eObjectType::player);  //オブジェクト設定

	collision.SetHitObjectType({ eObjectType::enemy, eObjectType::ground });  //hitオブジェクトタイプ

	//collision.SetSize(46, 40);  

	SetDrawCollisionBox(true);  //当たり判定大きさ取得3
	SetDarwCollisionCapsule(true);

	img_size = Vector2D(100, 100);   //当たり判定サイズ設定

	collision.radius = 25;

	z_layer = 5;  //レイヤー設定

	mobility = eMobilityType::movable;  //

	is_on_ground = true;   //地面についたかどうか
	scroll_offset = 0.0f; //スクロール値
	ground_y = 400.0f;  //地面のlocation

	location = Vector2D(100, 400);

	image = idle_animation[0];  //初期イメージ設定

	if (image == -1) throw("エラー\n");  //エラーチェック

}

void Player::Update(float delta_second)
{
	Vector2D collisionPosition = collision.GetPosition();

	velocity.y += D_GRAVITY * delta_second * ADDJUMP;  //重力速度計算

	if (location.y > 400) //地面落ちないようにする
	{
		location.y = 400;
		velocity.y = 0.5;
	}


	collision.SetPosition(location);

	collision.SetStartPoint(Vector2D(location.x, location.y - (img_size.y / 2.0f)));
	collision.SetEndPoint(Vector2D(location.x, location.y + (img_size.y / 2.0f)));

	if (GetCollision().object_type == eObjectType::enemy)
	{
		player_state = ePlayerState::damage;
	}

	//プレイヤーの状態ごとの処理
	switch (player_state) {
	case ePlayerState::idle: //idle状態の処理
		//image = move_animation[0];

		AnimationControl(idle_animation, IDLE_ANIMATION_RATE, delta_second, 8, idle);

		velocity.x = 0;

		if (
			InputCtrl::GetKeyState(KEY_INPUT_A) == PRESSED ||
			InputCtrl::GetKeyState(KEY_INPUT_D) == PRESSED ||
			InputCtrl::GetKeyState(KEY_INPUT_LEFT) == PRESSED ||
			InputCtrl::GetKeyState(KEY_INPUT_RIGHT) == PRESSED ||

			InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == PRESSED ||
			InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == PRESSED
			) {
			player_state = ePlayerState::move;
		}
		else if (InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESS || InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
		{
			//velocity.y = -4.0f;

			//is_on_ground = false;
			player_state = ePlayerState::jump;

			//PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
		}
		else if (InputCtrl::GetKeyState(KEY_INPUT_E) == PRESS || InputCtrl::GetButtonState(XINPUT_BUTTON_X) == PRESS)
		{
			//image = attack_animation[0];
			player_state = ePlayerState::attack;
		}
		else if (InputCtrl::GetKeyState(KEY_INPUT_Q) == PRESS || InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
		{
			player_state = ePlayerState::avoidance;
		}

		break;

	case ePlayerState::move: //移動処理
		Movement(delta_second);
		AnimationControl(run_animation, MOVE_ANIMATION_RATE, delta_second, 8, idle);

		break;

	case ePlayerState::die: //死亡処理

		is_destroy = true;
		//velocity.x = 0.0f;
		/*animation_time += delta_second;

		if (animation_time >= 0.07f) {
			animation_time = 0.0f;

			animation_count++;

			if (animation_count >= dying_animation.size()) {
				player_state = ePlayerState::idle;

				animation_count = 0;

				is_destroy = true;
			}
		}*/

		//image = attack_animation[];

		break;

	case ePlayerState::damage: //ダメージを受けた時の処理
		//animation_time += delta_second;
		p_hp -= 10;
		if (p_hp == 0)
		{
			player_state = ePlayerState::die;
		}

		break;

	case ePlayerState::jump: //ジャンプ状態の処理


		//PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);

		//プレイヤーがジャンプ状態のとき
		JumpMovement(delta_second);

		//if (!is_on_ground) velocity.y += D_GRAVITY * delta_second * ADDJUMP;  //重力速度計算

		/* ジャンプ中に2回攻撃させないため */
		if (InputCtrl::GetKeyState(KEY_INPUT_E) == PRESS && jump_attack_flg == false ||
			InputCtrl::GetButtonState(XINPUT_BUTTON_X) == PRESS && jump_attack_flg == false)
		{
			player_state = ePlayerState::jump_attack;
		}

		//地面についた時の処理
		if (location.y + velocity.y * delta_second > ground_y) {

			location.y = ground_y;

			velocity.y = 0.0f;
			g_velocity = 0.0f;

			is_on_ground = true;
			jump_attack_flg = false;

			player_state = ePlayerState::idle;
		}

		break;

	case ePlayerState::attack: //攻撃処理

		AnimationControl(attack_animation, ATTACK_ANIMATION_RATE, delta_second, 6, idle);

		break;
	case ePlayerState::jump_attack:

		AnimationControl(attack_animation, ATTACK_ANIMATION_RATE, delta_second, 6, jump);

		//if (jump_attack_flg == false) jump_attack_flg = true;
		//if (!is_on_ground) velocity.y += D_GRAVITY * delta_second * ADDJUMP;  //重力速度計算

		break;
	case ePlayerState::avoidance: //回避処理

		AnimationControl(avoidance_animation, ROLL_ANIMATION_RATE, delta_second, 7, idle);

		//後でアニメーション割込み聞く
		break;

	default:
		break;
	}

	if (location.x < 16.0f) location.x = 16.0f;

	location += velocity; //移動量加算
}

void Player::Draw(const Vector2D& screen_offset) const  //描画処理
{
	//DrawRotaGraphF(location.x, location.y, 5.0, 0.0, image, TRUE, this->flip_flag);
	DrawFormatString(0, 180, GetColor(255, 255, 255), "Player HP: %d", p_hp);
	DrawFormatString(0, 160, GetColor(255, 255, 255), "Player: %d", player_state);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "Player velocaty.y: %0.0f", velocity.y);
	__super::Draw(screen_offset);
}

void Player::Finalize() //終了時処理
{
	idle_animation.clear();
	attack_animation.clear();
	run_animation.clear();
	jump_animation.clear();
	avoidance_animation.clear();
}

void Player::OnHitCollision(GameObjectBase* hit_object) //当たった時
{

	//
	//if (hit_object->GetCollision().object_type == eObjectType::wall) {
	//	CapsuleCollision hc = hit_object->GetCollision();

	//	hc.point[0] += hit_object->GetLocation();
	//	hc.point[1] += hit_object->GetLocation();

	//	Vector2D near_point = NearPointCheck(hc, this->location);

	//	Vector2D dv2 = near_point - this->location;
	//	Vector2D dv = this->location - near_point;

	//	float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

	//	location += dv.Normalize() * diff;
	//}

	//if (hit_object->GetCollision().object_type == eObjectType::food) food_count++;

	//if (hit_object->GetCollision().object_type == eObjectType::power_food) {
	//	food_count++;
	//	is_power_up = true;
	//}

	if (hit_object->GetCollision().object_type == eObjectType::enemy)
	{
		player_state = ePlayerState::damage;
	}
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

//bool Player::GetDestroy() const
//{
//	return is_destroy;
//}

void Player::Movement(float delta_second)
{
	//移動処理
	if (
		InputCtrl::GetKeyState(KEY_INPUT_A) ||
		InputCtrl::GetKeyState(KEY_INPUT_LEFT) ||

		InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_LEFT)
		) {
		velocity.x = -VELOCITY;

		flip_flag = true;

		//移動状態のときボタンを押されたら
		if (InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESS || InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS && is_on_ground == true)
		{
			//velocity.y = -4.0f;

			//is_on_ground = false;
			player_state = ePlayerState::jump; //ジャンプ状態に遷移
		}
		if (InputCtrl::GetKeyState(KEY_INPUT_E) == PRESS || InputCtrl::GetButtonState(XINPUT_BUTTON_X) == PRESS)
		{
			player_state = ePlayerState::attack; //攻撃状態に遷移
		}
		if (InputCtrl::GetKeyState(KEY_INPUT_Q) == PRESS || InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
		{
			//player_state = ePlayerState::avoidance; //回避状態に遷移
		}
	}
	else if (InputCtrl::GetKeyState(KEY_INPUT_D) || InputCtrl::GetKeyState(KEY_INPUT_RIGHT) || InputCtrl::GetButtonState(XINPUT_BUTTON_DPAD_RIGHT)) {
		velocity.x = VELOCITY;

		flip_flag = false;

		//移動状態のときボタンを押されたら
		if (InputCtrl::GetKeyState(KEY_INPUT_SPACE) == PRESS || InputCtrl::GetButtonState(XINPUT_BUTTON_A) == PRESS)
		{
			//player_state = ePlayerState::jump; //ジャンプ状態に遷移
		}
		if (InputCtrl::GetKeyState(KEY_INPUT_E) == PRESS || InputCtrl::GetButtonState(XINPUT_BUTTON_X) == PRESS)
		{
			//player_state = ePlayerState::attack; //攻撃状態に遷移
		}
		if (InputCtrl::GetKeyState(KEY_INPUT_Q) == PRESS || InputCtrl::GetButtonState(XINPUT_BUTTON_B) == PRESS)
		{
			//player_state = ePlayerState::avoidance; //回避状態に遷移
		}
	}
	else {
		velocity.x = 0;

		player_state = ePlayerState::idle;
	}
}

void Player::JumpMovement(float delta_second)
{
	//ジャンプ移動処理
	if ((InputCtrl::GetKeyState(KEY_INPUT_SPACE) || InputCtrl::GetButtonState(XINPUT_BUTTON_A))) {
		velocity.y = -4.0f;

		is_on_ground = false;

		//AnimationControl(jump_animation, JUMP_ANIMATION_RATE, delta_second, 7, idle);

		//PlaySoundMem(jump_SE, DX_PLAYTYPE_BACK, TRUE);
	}
}

void Player::AnimationControl(std::vector<int> image_container, float frame, float delta_second, int image_count, ePlayerState state)
{
	animation_time += delta_second;

	if (animation_time >= frame) {
		animation_time = 0.0f;

		animation_count++;

		if (animation_count >= image_count) {
			animation_count = 0;
			if (state == jump && jump_attack_flg == false)
			{
				jump_attack_flg = true;
			}
			player_state = state;
		}

		image = image_container[animation_count];
	}
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