#pragma once
#include "Lazer.h"
#include "Blade.h"
#include "Venom.h"

enum PLAYERMOVE{BUTTON_D,BUTTON_L,BUTTON_R,BUTTON_U,BUTTON_A,BUTTON_B};
enum PLAYERSTATUS { NORMAL, BALL, DAMAGE ,DEAD};

class Player
{
public:
	int posX, posY,posYPrev,posYTemp, posYDamageTemp, posYDamagePrev;
	int hp;
	int animX,ballAnimX, animCnt,jumpX,jumpXCnt,knockBackAnimCnt,knockBackAnimX;
	int player_gh,playerDot_gh, player_effect_gh, ball_se, playerHpGage_gh;
	int pad;
	int playerMode;
	int ballModeCnt, knockBackCnt;
	int playerR, playerG, playerB;
	int playerParts[10];
	bool isLeft;
	bool playerRainbowFlg;
	bool hitFlg,jumpFlg,ballModeFlg,isDead,damageJumpFlg,knockBackFlg,knockBackJumpFlg;
	bool rotationHitFlg;
	bool flogFlg;
	Player();
	void DrawPlayer();
	void MovePlayer();
	void Jump();
	void KnockBack(Lazer *lz, Blade *bl, Venom *ve);
	void BallSystem();
	void Explosion();
};

Player* PlayerInit();
void PlayerUpdata(Player*);
void PlayerHitCheck(Lazer*, Blade*, Venom*);
void ResetPlayer();
void EndPlayer();
Player* GetPlayerPointer();

class PlayerParts
{
public:
	int posX, posY;
	int posYTemp, posYPrev;
	int moveXPower, moveYPower;
	int static explosionDerayCnt;
	float angle;
	static bool explosionFlg;
	static bool loadPlayerPartsExplosionFlg;
	static int parts_gh;
	static int explosionSound;
	PlayerParts();
	void Explosion();
	void DrawParts(int i);
	void ExplosionAll(int i);
};

PlayerParts* GetPlayerPartsPointer();
void ResetPlayerParts();
void DrawEffect();