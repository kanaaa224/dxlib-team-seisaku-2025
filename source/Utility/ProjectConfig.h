#pragma once

#include <string>

#define	D_SUCCESS (0)
#define	D_FAILURE (-1)

#define D_WIN_MAX_X (1280)
#define D_WIN_MAX_Y (720)
#define D_COLOR_BIT (32)

#define D_FPS (60)

#define D_APP_NAME "DxLib"

#define DEBUG 1

void FrameControl();

const float& GetDeltaSecond();

int ErrorThrow(std::string error_log);