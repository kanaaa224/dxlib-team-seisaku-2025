#include"DxLib.h"
#include "GameMainScene.h"


GameMainScene::GameMainScene()
{
	
}

GameMainScene::~GameMainScene()
{

}

//初期化処理
void GameMainScene::Initialize()
{
	
}

//更新処理
eSceneType GameMainScene::Update()
{
	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	DrawString(640, 360, "こちらはゲームメインです！！", GetColor(255, 255, 255));
}

//終了時処理
void GameMainScene::Finalize()
{

}

//現在のシーン情報を取得
eSceneType GameMainScene::GetNowScene() const
{
    return eSceneType::E_MAIN;
}