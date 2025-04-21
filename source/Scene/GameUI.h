#pragma once

class GameUI
{
private:
	int hp_ber;     //HPバー
	int hp_frame;   //HPフレーム

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
