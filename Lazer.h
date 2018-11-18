#pragma once
#include "DxLib.h"
#include "define.h"

enum LAZERSIDE{LEFT_L,RIGHT_L,UP_L};

class Lazer
{
public:
	int posX,posY;
	int hp;
	float thickness;
	int brightness;
	int side;
	static int boss1Attack_gh, boss1Lazer_gh,lazerSound,enemyHitSound;
	int colorR, colorG, colorB;
	int lazerEyeAnimCnt, lazerEyeAnimX,lazerHitAnimCnt,lazerHitAnimX;
	int firingDerayCnt;//レーザーが太くなるまでのディレイ
	int lazerTime;//レーザーの一連の時間の長さ
	bool lazerHitFlg;//レーザーの目玉の当たり判定
	bool isDeadFlg;//ダメージで死んだか？
	bool hitableFlg;//プレイヤーの当たり判定取るフラグ
	bool riseFlg;//太さ変えるときのフラグ
	bool lazerExistFlg;//存在フラグ←このフラグはゲーム開始時に全部trueになってるから開始のフラグに使うのはよくない
	bool setLazerFlg;
	bool lazerSoundFlg;
	static bool lazerLoadFlg;
	Lazer();
	void DrawLazer(int);
	void MoveLazer(int);
	void LazerSway();
};

void CreateLazer();
void LazerInit();
void LazerUpdata();
void SetLazer(int i, int cnt,int posXorY,int type);
void ResetLazer();
void EndLazer();
Lazer* GetLazerPointer();