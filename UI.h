#pragma once
#include "DxLib.h"
#include "Scene.h"

class UI
{
public:
	int hpPosX, hpPosY;
	float hpAnimX,hpAnimX2;
	float hpRate,hpRate2;
	int bossHp;
	int bosshp_gh;
	UI();
	void DrawHp();
	void HpManager();
};

void UIAll();
void EndUI();
void ResetUI();
UI* GetUIPointer();

class Damage
{
public:
	int posX, posY;
	int damage;
	int life;
	bool damageExistFlg;
	Damage();
	void DrawDamage();
	void DamageManager(int damage);
};

void DamageAll(int damage);
void PlayerHpView();