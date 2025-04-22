#pragma once

class GameUI
{
private:
	int hp_ber;        //HPバー
	int hp_frame;      //HPフレーム

	int player_icon;   //playerアイコン
	int player_frame;   //フレーム

	int time_frame;     //タイムフレーム

	int buf_attack;   //バフ・攻撃力UP
	int attack_frame;
	int buf_defense;  //バフ・防御力UP
	int defense_frame;
	int buf_HPUP;     //バフ・体力上限UP
	int HPUP_fame;
	int buf_recovery; //バフ・体力回復
	int recovery_frame;
	int buf_movement; //バフ・移動速度UP
	int movement_frame;


	static GameUI* instance;
	GameUI* gameui;

public:
	GameUI();
	virtual ~GameUI();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	static GameUI* GetInstance();
};
