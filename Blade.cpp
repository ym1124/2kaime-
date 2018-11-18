#include "Blade.h"
#include "define.h"
#include "Scene.h"

Blade bl[BLADE_MAX];

Blade::Blade()
{
	posY =- BLADE_HEIGHT;
	animX = 0;
	animCnt = 0;
	bladeExistFlg = false;
}

void Blade::CreateBlade(int side)
{
	if (!bladeExistFlg)//画面外に出るまで再生成されない
	{
		this->side = side;
		switch (this->side)
		{
		case LEFT_B:
			posX = -BLADE_WIDTH / 2;
			posY = -BLADE_HEIGHT;
			break;
		case RIGHT_B:
			posX = WINDOW_X-(BLADE_WIDTH / 2);
			posY = -BLADE_HEIGHT;
			break;
		}
		bladeExistFlg = true;
	}
}

void Blade::BladeMove(int side)
{
	if (bladeExistFlg)
	{
		switch (side)
		{
		case LEFT_B:
			if(posX <= -BLADE_WIDTH/2)
				posY += BLADE_SPEED_Y;
			if(posY>=BLADE_Y_INIT)
				posX += BLADE_SPEED_X;
			if (posX >= WINDOW_X)
				bladeExistFlg = false;
			break;
		case RIGHT_B:
			if (posX >= WINDOW_X - (BLADE_WIDTH / 2))
				posY += BLADE_SPEED_Y;
			if (posY >= BLADE_Y_INIT)
				posX -= BLADE_SPEED_X;
			if (posX <= -BLADE_WIDTH)
				bladeExistFlg = false;
			break;
		}
	}
	else
		posX = WINDOW_X * 3;//使わないときは画面外座標で固定
}

void Blade::BladeDraw(int side)
{
	animCnt++;
	animX = animCnt% BLADE_ANIM_MAX;
	if (bladeExistFlg)
	{
		switch (side)
		{
		case LEFT_B:
			DrawRectGraph(posX, posY, animX*BLADE_WIDTH, 1000, BLADE_WIDTH, BLADE_HEIGHT, blade_gh, true, true);
			break;
		case RIGHT_B:
			DrawRectGraph(posX, posY, animX*BLADE_WIDTH, 1000, BLADE_WIDTH, BLADE_HEIGHT, blade_gh, true);
			break;
		}
	}
	if (!bladeExistFlg)
	{
		animCnt = 0;
		animX = 0;
	}
}

void SetBlade(int i, int cnt, int side)
{
	if (GetScenePointer()->playNowCnt == cnt)
	{
		BladeInit(i,side);
	}
	if (bl[i].bladeExistFlg)
	{
		bl[i].BladeMove(side);
		bl[i].BladeDraw(side);
	}
}

void BladeInit(int i,int side)
{
	bl[i].CreateBlade(side);
}

void BladeUpdata()
{
	//SetBlade(n番目のブレード,出現カウント,出現させる場所)
	SetBlade(0, 217, RIGHT_B);
	SetBlade(1, 460, LEFT_B);
	SetBlade(2, 695, RIGHT_B);
	SetBlade(3, 920, LEFT_B);
	SetBlade(4, 1159, RIGHT_B);
	SetBlade(5, 1388, LEFT_B);
	SetBlade(6, 1630, RIGHT_B);

	SetBlade(7, 3007, LEFT_B);

	SetBlade(8, 3220, RIGHT_B);
}

Blade* GetBladePointer()
{
	return bl;
}

void ResetBlade()
{
	for (int i = 0; i < BLADE_MAX; i++)
	{
		bl[i].bladeExistFlg = false;
	}
}