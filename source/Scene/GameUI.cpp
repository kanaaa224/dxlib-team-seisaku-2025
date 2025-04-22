#include "GameUI.h"
#include "DxLib.h"

// 静的メンバ変数定義 nullptrで初期化
GameUI* GameUI::instance = nullptr;

GameUI::GameUI() :  hp_ber(NULL), 
					hp_frame(NULL), 
					gameui(nullptr),
					player_frame(NULL),
					player_icon(NULL),
					time_frame(NULL),
					buf_attack(NULL),
					attack_frame(NULL),
					buf_defense(NULL),
					defense_frame(NULL),
					buf_HPUP(NULL),
					HPUP_fame(NULL),
					buf_recovery(NULL),
					recovery_frame(NULL),
					buf_movement(NULL),
					movement_frame(NULL)
{
}

GameUI::~GameUI()
{
}

void GameUI::Initialize()
{
	//HPバー
	hp_ber = LoadGraph("resource/images/ui/hp_bar_backA.png");
	//HPフレーム
	hp_frame = LoadGraph("resource/images/ui/hp_frameA.png");

	//playerアイコン
	player_frame = LoadGraph("resource/images/ui/character_icon.png");
	//playerフレーム
	player_icon = LoadGraph("resource/images/ui/character_frame.png");

	//タイムフレーム
	time_frame = LoadGraph("resource/images/ui/timer_frame.png");

	//バフ・攻撃力UP
	buf_attack = LoadGraph("resource/images/ui/buf_icons/buf_attack_power_up.png");
	attack_frame = LoadGraph("resource/images/ui/buf_frames/frame_attack_power.png");
	//バフ・防御力UP
	buf_defense = LoadGraph("resource/images/ui/buf_icons/buf_Defense_power_up.png");
	defense_frame = LoadGraph("resource/images/ui/buf_frames/frame_Defense_power.png");
	//バフ・体力上限UP
	buf_HPUP = LoadGraph("resource/images/ui/buf_icons/buf_hp_upper_limit_up.png");
	HPUP_fame = LoadGraph("resource/images/ui/buf_frames/frame_hp_upper_limit.png");
	//バフ・体力回復
	buf_recovery = LoadGraph("resource/images/ui/buf_icons/buf_hp_recovery.png");
	recovery_frame = LoadGraph("resource/images/ui/buf_frames/frame_Defense_power.png");
	//バフ・移動速度UP
	buf_movement = LoadGraph("resource/images/ui/buf_icons/buf_movement_speed_up.png");
	movement_frame = LoadGraph("resource/images/ui/buf_frames/frame_movement_speed.png");
}

void GameUI::Update()
{
}

void GameUI::Draw()
{ 

	//HPフレーム表示
	DrawGraph(45, 5, hp_frame, FALSE);
	//HPバー表示
	DrawGraph(40, 15, hp_ber, FALSE);
	//playerフレーム
	DrawGraph(0, 5, player_frame, FALSE);
	//playerアイコン
	DrawGraph(0, 5, player_icon, FALSE);
	//タイムフレーム
	DrawGraph(65, 40, time_frame, FALSE);

	/* 座標 x, y, 拡大率 2.0, 回転率 0.0, 画像ハンドル, 透過フラグ TRUE, 画像を反転するか */
	//DrawRotaGraphF();
}

void GameUI::Finalize()
{
}

GameUI* GameUI::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new GameUI();
	}
	return instance;
}
