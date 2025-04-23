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
					HPUP_frame(NULL),
					buf_recovery(NULL),
					recovery_frame(NULL),
					buf_movement(NULL),
					movement_frame(NULL),
					avoidance_button(NULL)
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
	player_icon = LoadGraph("resource/images/ui/character_icon.png");
	//playerフレーム
	player_frame = LoadGraph("resource/images/ui/character_frame.png");

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
	HPUP_frame = LoadGraph("resource/images/ui/buf_frames/frame_hp_upper_limit.png");
	//バフ・体力回復
	buf_recovery = LoadGraph("resource/images/ui/buf_icons/buf_hp_recovery.png");
	recovery_frame = LoadGraph("resource/images/ui/buf_frames/frame_hp_recovery.png");
	//バフ・移動速度UP
	buf_movement = LoadGraph("resource/images/ui/buf_icons/buf_movement_speed_up.png");
	movement_frame = LoadGraph("resource/images/ui/buf_frames/frame_movement_speed.png");

	//回避ボタン
	avoidance_button = LoadGraph("resource/images/ui/button/short_button_animation1.png");

}

void GameUI::Update()
{
}

void GameUI::Draw()
{ 
	/* 座標 x, y, 拡大率 2.0, 回転率 0.0, 画像ハンドル, 透過フラグ TRUE, 画像を反転するか */
	//DrawRotaGraphF(45,5,2.0,0.0,hp_frame,TRUE,0);

	/*int size = 50;
	int width = size;
	int height = size;
	int a = 0;
	int b = 0;
	DrawExtendGraph(a,b,a+width,b+height,hp_frame, true);*/

	//HPフレーム表示
	/* 座標 x, y, 拡大率 2.0, 回転率 0.0, 画像ハンドル, 透過フラグ TRUE, 画像を反転するか */
	DrawRotaGraph(255, 30, 1.0, 0.0, hp_frame, TRUE, FALSE);
	//HPバー表示
	DrawRotaGraph(251, 30,0.9,0.0, hp_ber, TRUE,FALSE);

	//playerフレーム
	DrawRotaGraph(72,75,5.5,0.0, player_frame,TRUE,FALSE);
	//playerアイコン
	DrawRotaGraph(72,70,1.8,0.0, player_icon, TRUE,FALSE);

	//タイムフレーム
	DrawRotaGraph(240, 74,5.0,0.0, time_frame, TRUE,FALSE);
	DrawFormatString(155, 74, GetColor(255, 255, 255), "タイム表示させる00:00");


	//画像の大きさの半分
	int frame_size = 32;
	//余白
	int pading_size = 170;
	//基準値
	int x = 460 + frame_size/2;

	//バフ・攻撃力UP
	DrawRotaGraph(x, 74, 1.5, 0.0, attack_frame, TRUE, FALSE);//0
	DrawRotaGraph(x, 74, 1.5, 0.0, buf_attack, TRUE, FALSE);//0
	x += pading_size;
	//バフ・防御力UP
	DrawRotaGraph(x, 74, 1.5, 0.0, defense_frame, TRUE, FALSE);//0
	DrawRotaGraph(x, 74, 1.5, 0.0, buf_defense, TRUE, FALSE);//0
	x += pading_size;
	//バフ・体力上限
	DrawRotaGraph(x, 74, 1.5, 0.0, HPUP_frame, TRUE, FALSE);
	DrawRotaGraph(x, 74, 1.5, 0.0, buf_HPUP, TRUE, FALSE);
	x += pading_size;
	//バフ・体力回復
	DrawRotaGraph(x, 74, 1.5, 0.0, recovery_frame, TRUE, FALSE);
	DrawRotaGraph(x, 74, 1.5, 0.0, buf_recovery, TRUE, FALSE);//0
	x += pading_size;
	//バフ・移動速度UP
	DrawRotaGraph(x, 74, 1.5, 0.0, movement_frame, TRUE, FALSE);
	DrawRotaGraph(x, 74, 1.5, 0.0, buf_movement, TRUE, FALSE);

	//回避UI
	DrawRotaGraph(1150, 650, 3.5, 0.0, avoidance_button, TRUE, FALSE);
	
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
