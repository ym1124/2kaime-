#pragma once
#include "Scene.h"

class Back
{
public:
	int Back_gh,Title_gh,Over_gh,boss_gh1,boss_gh2,Flame_gh,floor_gh,tutorial_gh;
	int eyeOpenMode,animTCnt,animCnt, animX,animY,pictureNum;
	int tBossX, tBossY;
	int fallDownY;
	int fallDownCnt;
	float bossSwayY;
	float variableX, variableY;
	bool movie;
	Back();
	void DrawBack();
	void DrawTitleBack();
	void DrawTutorialBack();
	void DrawBossDeadBack();
	void DrawPlayBack();
	void DrawOverBack();
};

Back* BackInit();
void BackUpdata(Back*);
void EndBack();
void ResetBack();

class Cloud
{
public:
	int posX, posY,life;
	int movePosX, movePosY;
	static int cloud_gh;
	int rngX;
	bool used;
	Cloud();
	void MoveCloud();
	void DrawCloud();
	void CloudAll();
};

class Aura
{
public:
	int posX, posY, life;
	int movePosX, movePosY;
	static int aura_gh;
	bool used;
	Aura();
	void MoveAura();
	void DrawAura();
	void AuraAll();
};