#pragma once
#include "DxLib.h"
#include "Scene.h"
#include <math.h>

class Rotation
{
public:
	int posX, posY,cPosX,cPosY;
	int animX,rotationR, rotationG, rotationB;
	int life;
	int r;
	static int rotation_gh,rotation_se;
	int angle;
	float rotationPosX, rotationPosY;
	bool rotationExistFlg;
	Rotation();
	void MoveRotation();
	void DrawRotation();
	void RotationHitCheck();
	void ResetRotation();
};

void SetRotation(int,int,int,int,int);
void RotationUpdata();
void RotationAll();
void ResetRotationAll();
void EndRotation();