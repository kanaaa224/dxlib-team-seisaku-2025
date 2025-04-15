#include "main.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
    if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK) return -1;
    if (SetGraphMode(_SCREEN_WIDTH_, _SCREEN_HEIGHT_, _SCREEN_COLOR_BIT_32_) != DX_CHANGESCREEN_OK) return -1;

    if (DxLib_Init() == -1) return -1;

    SetDrawScreen(DX_SCREEN_BACK);

    FPS::SetLimitRate(_SCREEN_FPS_);
    FPS::SetUpdateInterval(1000);

    while (ProcessMessage() == 0) {
        ClearDrawScreen();

        if (GetMainWindowHandle() == GetForegroundWindow()) InputCtrl::Update();

        FPS::Limit();
        FPS::Update();

#ifdef DEBUG
        SetFontSize(16);
        DrawFormatString(10, 10, GetColor(255, 255, 255), "FPS: %0.0f", FPS::Get());

        if (InputCtrl::GetKeyState(KEY_INPUT_ESCAPE) || InputCtrl::GetButtonState(XINPUT_BUTTON_BACK)) break;
#endif

        ScreenFlip();
    }

    DxLib_End();

    return 0;
}