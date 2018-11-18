#include "DxLib.h"
#include "Venom.h"
#include "define.h"
#include "Scene.h"

Venom ve[VENOM_MAX];

Venom::Venom()
{
	posY = BLADE_Y_INIT;
	animX = 0;
	animCnt = 0;
	speedX = 0;
	jumpFlg = false;
}

void Venom::CreateVenom(int side)
{
	this->side = side;
	if (!venomExistFlg)//画面外に出るまで再生成されない
	{
		switch (this->side)
		{
		case LEFT_V:
			posX = -BLADE_WIDTH;
			jumpFlg = false;
			break;
		case RIGHT_V:
			posX = WINDOW_X;
			jumpFlg = false;
			break;
		}
		venomExistFlg = true;
	}
}

void Venom::VenomMove()
{
	if (venomExistFlg == true)
	{
		switch (this->side)
		{
		case LEFT_V:
			posX += VENOM_SPEED_X;
			if (posY >= (WINDOW_Y - 100) - VENOM_HEIGHT)
			{
				jumpFlg = false;
				PlaySoundMem(Venom::venom_se, DX_PLAYTYPE_BACK);
			}

			//ジャンプ処理
			if (jumpFlg)
			{
				posYTemp = posY;
				posY += (posY - posYPrev) + 1;
				posYPrev = posYTemp;
			}

			if (!jumpFlg)
			{
				jumpFlg = true;
				posYPrev = posY;
				posY = posY - VENOM_JUMP_POWER;
			}
			if (posX >= WINDOW_X)
				venomExistFlg = false;
			break;

		case RIGHT_V:
			posX -= VENOM_SPEED_X;
			if (posY >= (WINDOW_Y - 100) - VENOM_HEIGHT)
			{
				jumpFlg = false;
				PlaySoundMem(Venom::venom_se, DX_PLAYTYPE_BACK);
			}

			//ジャンプ処理
			if (jumpFlg)
			{
				posYTemp = posY;
				posY += (posY - posYPrev) + 1;
				posYPrev = posYTemp;
			}

			if (!jumpFlg)
			{
				jumpFlg = true;
				posYPrev = posY;
				posY = posY - VENOM_JUMP_POWER;
			}

			if (posX <= -VENOM_WIDTH)
				venomExistFlg = false;
			break;
		}
	}
	else
		posX = WINDOW_X * 3;//使わないときは画面外座標で固定
}

void Venom::VenomDraw(int side)
{
	if (venomExistFlg)
	{
		switch (side)
		{
		case LEFT_V:
			DrawRectGraph(posX, posY, 0, 0, VENOM_WIDTH, VENOM_HEIGHT, venom_gh, true, true);
			break;
		case RIGHT_V:
			DrawRectGraph(posX, posY, 0, 0, VENOM_WIDTH, VENOM_HEIGHT, venom_gh, true, false);
			break;
		}
	}
}

void SetVenom(int i, int cnt, int side)
{
	if (GetScenePointer()->playNowCnt == cnt)
	{
		VenomInit(i, side);
	}
	if (ve[i].venomExistFlg)
	{
		ve[i].VenomMove();
		ve[i].VenomDraw(side);
	}
}

void VenomInit(int i, int side)
{
	ve[i].CreateVenom(side);
}

void VenomUpdata()
{
	SetVenom(0, 1830, RIGHT_V);
	SetVenom(1, 2060, RIGHT_V);
	SetVenom(2, 2170, LEFT_V);
	SetVenom(3, 2410, LEFT_V);
}

void ResetVenom()
{
	for (int i = 0; i < VENOM_MAX; i++)
	{
		ve[i].animX = 0;
		ve[i].animCnt = 0;
		ve[i].venomExistFlg = false;
	}
}

Venom* GetVenomPointer()
{
	return ve;
}