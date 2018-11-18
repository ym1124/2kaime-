#pragma once
#include "DxLib.h"

enum BLADESIDE{LEFT_B,RIGHT_B};

class Blade 
{
public:
	int posX, posY;
	int animX;
	int animCnt;
	static int blade_gh;
	int side;
	bool bladeExistFlg;
	Blade();
	void CreateBlade(int);
	void BladeMove(int);
	void BladeDraw(int);
};

void SetBlade(int, int,int);
void BladeInit(int,int);
void BladeUpdata();
void ResetBlade();
void EndBlade();
Blade* GetBladePointer();