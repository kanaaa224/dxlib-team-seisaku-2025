//////////////////////////////////////////////////
// FPS コントローラー
// 作成: Kanato Shimabukuro
//////////////////////////////////////////////////

#include "fps.h"

int FPS::frameTime  = 0;
int FPS::waitTime   = 0;
int FPS::lastTime   = 0;
int FPS::nowTime    = 0;
int FPS::updateTime = 0;
int FPS::lastUpdate = 0;

float FPS::count = 0.0f;
float FPS::fps   = 0.0f;

void FPS::SetLimitRate(float refreshRate) {
    frameTime = (int)(1000.0f / refreshRate);
}

void FPS::SetUpdateInterval(int updateInterval) {
    updateTime = updateInterval;
}

void FPS::Limit() {
    nowTime = GetNowCount();

    waitTime = frameTime - (nowTime - lastTime);

    if (waitTime > 0) WaitTimer(waitTime);

    lastTime = GetNowCount();
}

void FPS::Update() {
    int time = GetNowCount();

    count += 1.0f;

    if (updateTime < (time - lastUpdate)) {
        fps = count / (float)(time - lastUpdate) * 1000.0f;

        lastUpdate = time;

        count = 0.0f;
    }
}

float FPS::Get() {
    return fps;
}