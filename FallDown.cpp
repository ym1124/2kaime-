#pragma once
#include "FallDown.h"

FallDown *fl = new FallDown();
Player *fpl = GetPlayerPointer();
int Cnt = 0;

FallDown::FallDown()
{
	posX = 0;
	posY = 0;
	rotationX = 0;
	rotationY = 0;
	rotationCnt = 0;
	shadowCnt = 200;
	fallDownAnimCnt = 0;
	fallDownAnimX = 0;
	downCnt = DOWN_CNT;
	alertCnt = 200;
	bossHp = BOSS2HP_INIT;
	fallDownExistFlg = false;
	eyeHitFlg = false;
	fallFlg = false;
}

void FallDown::SetFallDown()
{
	//DrawFormatString(0, 300, GetColor(255, 255, 255), "Cnt:%d", Cnt);
	if (!fallDownExistFlg)
	{
		posX = 0;
		posY = -FALLDOWN_BOSS_HEIGHT;
		eyePosX = posX + EYE_POSX_MARGIN;
		eyePosY = posY + EYE_POSY_MARGIN;
		downCnt = DOWN_CNT;
		alertCnt = 200;
		shadowCnt = SHADOW_CNT;
		fallDownExistFlg = true;
		fallFlg = false;
		eyeHitFlg = false;
	}
}

void FallDown::Attack(int cnt, int posX)
{
	if (fallDownExistFlg&&GetScenePointer()->playNowCnt == cnt)
	{
		this->posX = posX;
		this->posY = -FALLDOWN_BOSS_HEIGHT - 1500;//1500は背景の目玉消すためのディレイ;
		eyePosX = this->posX + EYE_POSX_MARGIN;
		eyePosY = posY + EYE_POSY_MARGIN;
		fallFlg = true;
	}
	if (fallFlg)
	{
		shadowCnt--;
		alertCnt--;
		posY += FALLDOWN_BOSS_SPEED;
		/*eyePosX = posX + EYE_POSX_MARGIN;*/
		eyePosY = posY + EYE_POSY_MARGIN;
		if ((fpl->posX > this->posX - PLAYER_WIDTH + 230 && fpl->posX < this->posX + FALLDOWN_BOSS_WIDTH - 230)
			&& (fpl->posY<this->posY + FALLDOWN_BOSS_HEIGHT - 130 && fpl->posY>this->posY - PLAYER_HEIGHT))
			fpl->hp -= 15;
		if (posY + FALLDOWN_BOSS_HEIGHT - 300 > PLAYERPOS_Y_INIT)
		{
			fallFlg = false;
			alertCnt = 200;
		}
	}
}

void FallDown::DrawFallDown()
{
	fallDownAnimCnt++;
	fallDownAnimX = fallDownAnimCnt / 10 % 11;
	rotationX = cos(DX_PI / 100 * fallDownAnimCnt) * 100;
	rotationY = sin(DX_PI / 100 * fallDownAnimCnt) * 100;
	if (fallDownExistFlg && (posY + FALLDOWN_BOSS_HEIGHT - 300) <= PLAYERPOS_Y_INIT)
	{
		DrawGraph(posX, posY, boss_gh, true);
		if (alertCnt >= 0&& fallFlg&&(alertCnt/10%2==1))
			DrawGraph(posX+600, 300, alert_gh, true);
		if (fallFlg&&shadowCnt<0)
		{
			DrawGraph(posX, WINDOW_Y - 100, bossShadow_gh, true);
		}
	}
	if(fallFlg)

	if (!fallFlg)
		shadowCnt = SHADOW_CNT;
	if (fallDownExistFlg && (posY + FALLDOWN_BOSS_HEIGHT - 300) > PLAYERPOS_Y_INIT)
	{
		DrawGraph(posX, posY, bossChance_gh1, true);
		if (GetScenePointer()->playNowCnt / 10 % 2 == 1)//目玉点滅
		{
			SetDrawBright(255, 0, 0);
			DrawGraph(posX + rotationX, posY + rotationY, bossChanceEye_gh, true);
			SetDrawBright(255, 255, 255);
		}
		DrawGraph(posX, posY, bossChance_gh2, true);
		DrawBox(posX - PLAYER_WIDTH + 230, posY - PLAYER_HEIGHT, posX + FALLDOWN_BOSS_WIDTH - 230, posY + FALLDOWN_BOSS_HEIGHT - 130, GetColor(50, 150, 255), false);//デバッグ用
		DrawBox(eyePosX, eyePosY, eyePosX + EYE_WIDTH, eyePosY + EYE_HEIGHT, GetColor(50, 150, 255), false);//デバッグ用
	}
	/*DrawFormatString(0, 250, GetColor(255, 255, 255), "FallDownBossY:%d", posY);*/
}

void FallDown::FallDownManager()
{
	if (fallDownExistFlg && !fallFlg && downCnt >= 0 && posX > PLAYERPOS_Y_INIT - FALLDOWN_BOSS_HEIGHT)//殴れるタイミング
	{
		downCnt--;
		if (fpl->playerMode == BALL && (fpl->posX > eyePosX - PLAYER_WIDTH&&fpl->posX < eyePosX + EYE_WIDTH) && (fpl->posY<eyePosY + EYE_HEIGHT&&fpl->posY>eyePosY - PLAYER_HEIGHT))
		{
			eyeHitFlg = true;
		}
		else
			eyeHitFlg = false;
	}
	if (downCnt < 0)
	{
		posY -= FALLDOWN_BOSS_SPEED;
		if (posY + FALLDOWN_BOSS_HEIGHT < 0)
		{
			fallDownExistFlg = false;
			Cnt++;
		}
	}
	if (!fallDownExistFlg || fallFlg || posX < PLAYERPOS_Y_INIT - FALLDOWN_BOSS_HEIGHT)
		eyeHitFlg = false;

	if (eyeHitFlg)
	{
		bossHp -= 2;
		PlaySoundMem(Lazer::enemyHitSound, DX_PLAYTYPE_BACK);
		eyeHitFlg = false;
		//DrawFormatString(0, 200, GetColor(255, 255, 255), "ボスに当たっています");
	}

	if (bossHp < 0)
	{
		GetScenePointer()->nowScene = BOSSDEAD;
	}
}

void SetFallDown(int cnt, int posX)
{
	fl->SetFallDown();
	fl->Attack(cnt, posX);
	fl->FallDownManager();
	fl->DrawFallDown();
}

void FallDownUpdata()
{
	switch (Cnt)//Cntは2ずつ
	{
	case 0:
	case 1:
		SetFallDown(300, 600);
		break;
	case 2:
	case 3:
		SetFallDown(3100, 600);
		break;
	case 4:
	case 5:
		SetFallDown(6000, 0);
		break;

	}
}

void ResetFallDown()
{
	Cnt = 0;
	fl->posX = 0;
	fl->posY = 0;
	fl->rotationX = 0;
	fl->rotationY = 0;
	fl->rotationCnt = 0;
	fl->downCnt = DOWN_CNT;
	fl->bossHp = BOSS2HP_INIT;
	fl->fallDownExistFlg = false;
	fl->eyeHitFlg = false;
	fl->fallFlg = false;
	fl->fallDownAnimCnt = 0;
	fl->fallDownAnimX = 0;
	fl->shadowCnt = SHADOW_CNT;
}

FallDown* GetFallDownPointer()
{
	return fl;
}

void EndFallDown()
{
	delete fl;
	fl = nullptr;
}