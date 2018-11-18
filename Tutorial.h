#pragma once
#include "DxLib.h"
#include "define.h"
#include "Player.h"
#include "Scene.h"

class Tutorial
{
public:
	int posX, posY,hp;
	int cnt, animX,tutorialEffectX;
	int enemy_gh,hitSound;
	int startFlgCnt,tutorialCnt;
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