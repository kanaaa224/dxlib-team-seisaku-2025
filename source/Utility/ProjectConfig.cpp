#include "ProjectConfig.h"
#include "DxLib.h"

LONGLONG old_time;
LONGLONG now_time;
float delta_second;

void FrameControl()
{
	now_time = GetNowHiPerformanceCount();

	delta_second = (float)(now_time - old_time) * 1.0e-6f;

	old_time = now_time;

	float refresh_rate = (float)GetRefreshRate();

	if (delta_second > (1.0f / refresh_rate)) delta_second = (1.0f / refresh_rate);
}

const float& GetDeltaSecond()
{
	return delta_second;
}

int ErrorThrow(std::string error_log)
{
	ErrorLogFmtAdd(error_log.c_str());

	return D_FAILURE;
}