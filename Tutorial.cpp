#include "Tutorial.h"

Tutorial *tu=new Tutorial();
bool TutorialLoadGraphFlg = false;

Tutorial::Tutorial()
{
	cnt = 0;
	animX = 0;
	hitFlg = false;
	startFlgCnt = 0;
	hp = 255;
	posX = WINDOW_X / 2;
	posY = WINDOW_Y-75- BOSS1_LAZER_EYE_HEIGHT;
}

void Tutorial::StartFlgCntINIT()
{
	if (hp < 50 && startFlgCnt <= 2)
	{
		hitFlg = false;
		hp = 255;
		posX = rand()%(WINDOW_X- BOSS1_LAZER_EYE_WIDTH);
		posY = WINDOW_Y - 75 - BOSS1_LAZER_EYE_HEIGHT;
	}
}

void Tutorial::StartGame()
{
	if (!TutorialLoadGraphFlg)
	{
		enemy_gh = LoadGraph("Data/Image/縦横レーザー.png");
		hitSound= LoadSoundMem("Data/Music/se/shot-struck1.mp3");
		TutorialLoadGraphFlg = true;
	}

	if ((GetPlayerPointer()->posX > posX - PLAYER_WIDTH&&GetPlayerPointer()->posX < posX + BOSS1_LAZER_EYE_WIDTH)
		&& (GetPlayerPointer()->posY>posY - PLAYER_HEIGHT&&GetPlayerPointer()->posY < posY + BOSS1_LAZER_EYE_HEIGHT)
		&& GetPlayerPointer()->playerMode == BALL)
		hitFlg = true;
	else
		hitFlg = false;
	if (hitFlg&&hp >= 50)
	{
		hp -= 3;
		PlaySoundMem(hitSound, DX_PLAYTYPE_BACK);
	}
	if (hp < 50)
	{
		startFlgCnt ++;
		StartFlgCntINIT();
		if (BackInit()->tBossY < BOSS1_Y_INIT&&startFlgCnt>2)
		{
			GetScenePointer()->nowScene = PLAY1;
		}
	}
}

void Tutorial::DrawTutorial()
{
	cnt++;
	animX = cnt / 8 % LAZER_EYE_ANIM_MAX;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, hp);
	if (startFlgCnt <= 2)
	{
		if (!hitFlg)
			DrawRectGraph(posX, posY, animX*BOSS1_LAZER_EYE_WIDTH, 0, BOSS1_LAZER_EYE_WIDTH, BOSS1_LAZER_EYE_HEIGHT, enemy_gh, true);
		else
		{
			SetDrawBright(255, 0, 0);
			DrawRectGraph(posX, posY, animX*BOSS1_LAZER_EYE_WIDTH, 0, BOSS1_LAZER_EYE_WIDTH, BOSS1_LAZER_EYE_HEIGHT, enemy_gh, true);//目玉//要画像変更
			SetDrawBright(255, 255, 255);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Tutorial::ResetTutorial()
{
	startFlgCnt = 0;
	hp = 255;
}

void TutorialAll()
{
	tu->StartGame();
	tu->DrawTutorial();
}

void ResetTutorial()
{
	tu->ResetTutorial();
	tu->cnt = 0;
	tu->animX = 0;
	tu->hitFlg = false;
}

Tutorial* GetTutorialPointer()
{
	return tu;
}

void EndTutorial()
{
	delete tu;
}