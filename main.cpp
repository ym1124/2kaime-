#include <DxLib.h>
#include <time.h>
#include <stdlib.h>
#include "DxInit.h"
#include "define.h"
#include "Back.h"
#include "Player.h"
#include "Particle.h"
#include "Scene.h"

//TODO
//���[�v�������Ƀo�O�łȂ����`�F�b�N

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//DxLib�����ݒ�
	DxInit();
	int pad;
	LoadAll();
	while (ProcessMessage() != -1)
	{
		pad= GetJoypadInputState(DX_INPUT_KEY_PAD1);
		ClearDrawScreen();
		Game();
		if (CheckHitKey(KEY_INPUT_ESCAPE) || pad&(1 << 11))
		{
			EndScene();
			break;
		}
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}