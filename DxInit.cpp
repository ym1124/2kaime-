#include "DxInit.h"

void DxInit()
{
	SetMainWindowText("Green Eyed Monster");
	ChangeWindowMode(true);
	SetGraphMode(WINDOW_X, WINDOW_Y, 32);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	srand((unsigned int)time(NULL));
}