#include "Rotation.h"
Rotation ro[ROTATION_MAX];
int rotationAnimCnt;
int tempRi=0,i=0;

Rotation::Rotation()
{
	posX = 0;
	posY = 0;
	animX = 0;
	r = 100;
	life = ROTATION_LIFE;
	rotationPosX = 0;
	rotationPosY = 0;
	rotationExistFlg = false;
}

void Rotation::MoveRotation()
{
	if (rotationExistFlg&&life==ROTATION_LIFE)
	{
		rotationR = rand() % 255;
		rotationG = rand() % 255;
		rotationB = rand() % 255;
	}
	if (rotationExistFlg)
	{
		if (life == ROTATION_LIFE)
			PlaySoundMem(Rotation::rotation_se, DX_PLAYTYPE_BACK);
		life--;
		rotationPosX = cos(DX_PI / 180 * angle) * r;//r‚Í”¼Œa
		rotationPosY = sin(DX_PI / 180 * angle) * r;
		cPosX = (posX + rotationPosX + ROTATION_WIDTH / 2);
		cPosY = (posY + rotationPosY + ROTATION_HEIGHT / 2);
		angle++;
	}
	if (life < 0)
		rotationExistFlg = false;
}

void Rotation::DrawRotation()
{
	animX = rotationAnimCnt / 50 % 7;
	rotationAnimCnt++;
	if (rotationExistFlg)
	{
		SetDrawBright(rotationR, rotationG, rotationB);
		DrawRectGraph(posX + rotationPosX, posY + rotationPosY, animX*ROTATION_WIDTH, 0, ROTATION_WIDTH, ROTATION_HEIGHT, rotation_gh, true);
		SetDrawBright(255, 255, 255);
	}
}

void Rotation::RotationHitCheck()
{
	if (rotationExistFlg)
	{
		if ((cPosX>GetPlayerPointer()->posX&&cPosX<GetPlayerPointer()->posX + PLAYER_WIDTH)
			&& (cPosY>GetPlayerPointer()->posY&&cPosX < GetPlayerPointer()->posY + PLAYER_HEIGHT))
		{
			PlayerInit()->rotationHitFlg = true;
		}
		else
			PlayerInit()->rotationHitFlg = false;
	}
	else
		PlayerInit()->rotationHitFlg = false;
}

void SetRotation(int num, int cnt, int posX, int posY, int r = ROTAITON_R_INIT)
{
	if (GetScenePointer()->playNowCnt == cnt)
	{
		ro[num].rotationExistFlg = true;
		ro[num].r = r;
	}
	if (ro[num].rotationExistFlg)
	{
		ro[num].posX = posX;
		ro[num].posY = posY;
	}
}

void RotationUpdata()
{
	SetRotation(0, 100, 100, 400);
	SetRotation(1, 200, 200, 400);
	SetRotation(2, 300, 300, 400);
	SetRotation(3, 400, 400, 400, 200);
	SetRotation(4, 500, 500, 400);
	SetRotation(5, 600, 600, 400, 400);
	SetRotation(6, 700, 700, 400);
	SetRotation(7, 800, 800, 400, 600);
	SetRotation(8, 900, 900, 400);
	SetRotation(9, 1000, 1000, 400, 800);
}

void RotationAll()
{
	RotationUpdata();
	for (int i = 0; i < ROTATION_MAX; i++)
	{
		ro[i].MoveRotation();
		ro[i].DrawRotation();
	}
	for (i = 0; i < ROTATION_MAX; i++)
	{
		if (GetPlayerPointer()->rotationHitFlg)
			i = tempRi;
		if (!ro[i].rotationExistFlg)
			GetPlayerPointer()->rotationHitFlg = false;
		ro[i].RotationHitCheck();
		if (GetPlayerPointer()->rotationHitFlg)
		{
			tempRi = i;
			break;
		}
	}
}

void Rotation::ResetRotation()
{
	posX = 0;
	posY = 0;
	life = 300;
	animX = 0;
	angle = 0;
	rotationPosX = 0;
	rotationPosY = 0;
	rotationExistFlg = false;
}

void ResetRotationAll()
{
	rotationAnimCnt = 0;
	for (int i = 0; i < ROTATION_MAX; i++)
	{
		ro[i].ResetRotation();
	}
}

//void EndRotation()
//{
//	delete ro;
//}