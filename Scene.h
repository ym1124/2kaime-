#pragma once
#include "DxInit.h"
#include "define.h"
#include "Player.h"
#include "Scene.h"
#include "Back.h"
#include "Particle.h"
#include "Lazer.h"
#include "Blade.h"
#include "Venom.h"
#include "UI.h"
#include "FallDown.h"
#include "Rotation.h"
#include "Tutorial.h"


enum SCENE { TITLE, TUTORIAL, PLAY1, PLAY2, BOSSDEAD, OVER, CLEAR };

class Scene
{
public:
	int nowScene;
	int playNowCnt;
	int secretCnt, secretState;
	int TitleSceneCnt;
	bool TitleModeBgmFlg;
	bool PlayModeBgmFlg;
	bool BossModeBgmFlg;
	bool BossDeadModeBgmFlg;
	Scene();
	void SceneManager();
	void DoTitleScene();
	void DoTutorialScene();
	void DoPlayScene();
	void DoBossScene();
	void DoBossDeadScene();
	void DoClearScene();
	void DoOverScene();
	void CheckCommand();
	void EndScene();
};
Scene* GetScenePointer();
void EndScene();
void Game();
void LoadAll();
void debugController(int);
void ResetScene();
void ResetGame();
int GetPad();
int DerayButtonAandReturn();