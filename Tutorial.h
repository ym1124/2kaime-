#pragma once
#include "DxLib.h"
#include "define.h"
#include "Player.h"
#include "Scene.h"

class Tutorial
{
public:
	int posX, posY,hp;
	int cnt, animX;
	int enemy_gh,hitSound;
	int startFlgCnt;
	bool hitFlg;
	Tutorial();
	void StartGame();
	void DrawTutorial();
	void StartFlgCntINIT();
	void ResetTutorial();
};

void TutorialAll();
void ResetTutorial();
Tutorial* GetTutorialPointer();
void EndTutorial();