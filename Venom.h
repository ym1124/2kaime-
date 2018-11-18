#pragma once

enum VENOMSIDE{LEFT_V, RIGHT_V};

class Venom
{
public:
	int posX, posY;
	int speedX, speedY;
	int posYTemp, posYPrev;
	int side;
	int animX, animCnt;
	static int venom_gh,venom_se;
	bool venomExistFlg;
	bool jumpFlg; 
	Venom();
	void CreateVenom(int);
	void VenomDraw(int);
	void VenomMove();
};

void SetVenom(int i, int cnt, int side);
void VenomInit(int i, int side);
void VenomUpdata();
void ResetVenom();
Venom* GetVenomPointer();