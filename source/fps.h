//////////////////////////////////////////////////
// FPS コントローラー
// 作成: Kanato Shimabukuro
//////////////////////////////////////////////////

#pragma once

#include "DxLib.h"

// FPS コントローラー クラス
class FPS {
private:
    static int frameTime, waitTime, lastTime, nowTime, updateTime, lastUpdate;

    static float count, fps;

public:
    // 制限するFPSの値を設定
    static void SetLimitRate(float);

    // 現在のFPSを計算する間隔を設定
    static void SetUpdateInterval(int);

    // 事前に指定したFPSに制限
    static void Limit();

    // 事前に指定した間隔で現在のFPSを計算
    static void Update();

    // FPSを取得（float型）
    static float Get();
};