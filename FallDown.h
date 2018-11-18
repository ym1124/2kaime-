#pragma once
#include "DxLib.h"
#include "define.h"
#include "Player.h"
#include "Scene.h"
#include "Lazer.h"

class FallDown
{
public:
	int posX,posY;
	int eyePosX, eyePosY, rotationX, rotationY;
	int bossHp;
	int boss_gh,bossChance_gh1, bossChance_gh2, bossChanceEye_gh,bossShadow_gh,alert_gh,fallDown_se;
	int downCnt, fallDownAnimCnt, fallDownAnimX,rotationCnt,shadowCnt,alertCnt;
	int attackableTime;
	bool fallDownExistFlg,fallFlg,eyeHitFlg,fallDownSeFlg;
	FallDown();
	void SetFallDown();
	void Attack(int cnt,int posX);
	void FallDownManager();
	void DrawFallDown();
};

void SetFallDown(int cnt, int posX);
void FallDownUpdata();
void ResetFallDown();
FallDown* GetFallDownPointer();
void EndFallDown();