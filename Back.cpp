#include "Back.h"
#include "DxLib.h"
#include "Scene.h"

Cloud cl[CLOUD_MAX];
Aura au[AURA_MAX];

Back::Back()
{
	fallDownY = 0;
	bossSwayY = 0;
	animTCnt = 0;
	endCnt = 0;
	animCnt = 0;
	animX = 0;
	animY = 0;
	darkCnt = DARK_CNT;
	tBossX = BOSS1_X_INIT;
	tBossY = 1100;
	pictureNum = 0;
	titleCnt = 0;
	movie = false;
	titleMovie = false;
}

Back* BackInit()
{
	//クラス実体宣言
	static Back *bg = new Back();//staticだと一回しか生成されない？
	return bg;
}

void EndBack()
{
	Back *bg = BackInit();
	delete bg;
	bg = nullptr;
}

void BackUpdata(Back *bg)
{
	bg->DrawBack();
}

void Back::DrawBack()
{
	Scene *sc = GetScenePointer();
	switch (sc->nowScene)
	{
	case TITLE:
		DrawTitleBack();
		break;
	case TUTORIAL:
		DrawTutorialBack();
		break;
	case PLAY1:
		DrawPlayBack();
		break;
	case PLAY2:
		DrawPlayBack();
		break;
	case BOSSDEAD:
		DrawBossDeadBack();
		break;
	case CLEAR:
		DrawClearBack();
		break;
	case OVER:
		DrawOverBack();
		break;
	default:
		break;
	}
}

void Back::DrawTitleBack()
{
	switch (GetScenePointer()->TitleSceneCnt)
	{
	case 0:
		titleCnt++;
		if (!titleMovie)
		{
			titleMovie = true;
			PlayMovie("Data/Image/タイトル.avi", 2, DX_MOVIEPLAYTYPE_BCANCEL);
		}
		if (titleCnt > 100)
		{
			titleMovie = false;
			titleCnt = 0;
		}
		break;
	case 1:
		DrawGraph(0, 0, tutorial_gh, true);
		break;
	}
}

void Back::DrawTutorialBack()
{
	DrawGraph(0, 0, Back_gh, true);//背景描画
	for (int i = 0; i < AURA_MAX; i++)
	{
		au[i].AuraAll();
	}
	switch (pictureNum)
	{
	case 0:
		DrawRectGraph(BOSS1_X_INIT, tBossY, BOSS1_WEIGHT*animX, BOSS1_HEIGHT*animY, BOSS1_WEIGHT, BOSS1_HEIGHT, boss_gh1, true);//ボス画像1
		break;
	case 1:
		DrawRectGraph(BOSS1_X_INIT, tBossY, BOSS1_WEIGHT*animX, BOSS1_HEIGHT*animY, BOSS1_WEIGHT, BOSS1_HEIGHT, boss_gh2, true);//ボス画像2
		break;
	}
	for (int i = 0; i < CLOUD_MAX; i++)
	{
		cl[i].CloudAll();
	}
	DrawGraph(0, WINDOW_Y - 100, floor_gh, true);//地面

	animTCnt++;
	//瞬きさせる処理
	eyeOpenMode = animTCnt / 160 % 2;
	/*pictureNum = animCnt / 80 % 2;*/
	if (eyeOpenMode == 0)//目の描画に関する処理
	{
		pictureNum = animTCnt / 80 % 2;//画像は2枚あるので使う画像の選択
		animX = animTCnt / 4 % 4;
		animY = animTCnt / 16 % 5;
	}
	else
	{
		pictureNum = 1 - animTCnt / 80 % 2;
		animX = 3 - (animTCnt / 4 % 4);
		animY = 4 - (animTCnt / 16 % 5);
	}
	if (GetTutorialPointer()->startFlgCnt>2)
		tBossY -= BOSS1_SPEED_Y;
}

void Back::DrawBossDeadBack()
{
	if (tBossY < 0)
		tBossY = 0;
	DrawGraph(rand()%31-15, rand() % 31 - 15, Back_gh, true);//背景描画
	for (int i = 0; i < AURA_MAX; i++)
	{
		au[i].AuraAll();
	}
	switch (pictureNum)
	{
	case 0:
		DrawRectGraph(BOSS1_X_INIT+ rand() % 31 - 15, tBossY, BOSS1_WEIGHT*animX, BOSS1_HEIGHT*animY, BOSS1_WEIGHT, BOSS1_HEIGHT, boss_gh1, true);//ボス画像1
		break;
	case 1:
		DrawRectGraph(BOSS1_X_INIT+ rand() % 31 - 15, tBossY, BOSS1_WEIGHT*animX, BOSS1_HEIGHT*animY, BOSS1_WEIGHT, BOSS1_HEIGHT, boss_gh2, true);//ボス画像2
		break;
	}
	for (int i = 0; i < CLOUD_MAX; i++)
	{
		cl[i].CloudAll();
	}
	DrawGraph(rand() % 31 - 15, WINDOW_Y - 100+ rand() % 31 - 15, floor_gh, true);//地面

	animTCnt++;
	//瞬きさせる処理
	eyeOpenMode = animTCnt / 160 % 2;
	/*pictureNum = animCnt / 80 % 2;*/
	if (eyeOpenMode == 0)//目の描画に関する処理
	{
		pictureNum = animTCnt / 80 % 2;//画像は2枚あるので使う画像の選択
		animX = animTCnt / 4 % 4;
		animY = animTCnt / 16 % 5;
	}
	else
	{
		pictureNum = 1 - animTCnt / 80 % 2;
		animX = 3 - (animTCnt / 4 % 4);
		animY = 4 - (animTCnt / 16 % 5);
	}
		tBossY += 1;
		if (tBossY > 1000)
		{
			GetScenePointer()->nowScene = CLEAR;
			StopSoundFile();
		}
}

void Back::DrawPlayBack()
{
	variableX = GetScenePointer()->playNowCnt % VIBRATION_VALUE;
	variableY = GetScenePointer()->playNowCnt % VIBRATION_VALUE;
	DrawGraph(0, 0, Back_gh, true);//背景描画
	for (int i = 0; i < CLOUD_MAX; i++)
	{
		cl[i].CloudAll();
	}
	for (int i = 0; i < AURA_MAX; i++)
	{
		au[i].AuraAll();
	}
	switch (pictureNum)
	{
	case 0:
		DrawRectGraph(BOSS1_X_INIT, BOSS1_Y_INIT + bossSwayY+ fallDownY, BOSS1_WEIGHT*animX, BOSS1_HEIGHT*animY, BOSS1_WEIGHT, BOSS1_HEIGHT, boss_gh1, true);//ボス画像1
		break;
	case 1:
		DrawRectGraph(BOSS1_X_INIT, BOSS1_Y_INIT + bossSwayY+ fallDownY, BOSS1_WEIGHT*animX, BOSS1_HEIGHT*animY, BOSS1_WEIGHT, BOSS1_HEIGHT, boss_gh2, true);//ボス画像2
		break;
	}

	for (int i = 0; i < CLOUD_MAX; i++)
	{
		cl[i].CloudAll();
	}
	DrawGraph(0, WINDOW_Y - 100, floor_gh, true);//地面
	DrawModiGraph(0 - variableX, 0 - variableY, WINDOW_X + variableX, 0 - variableY,//外枠の描画と振動
		WINDOW_X + variableX, WINDOW_Y + variableY, 0 - variableX, WINDOW_Y + variableY, Flame_gh, true);
	animCnt++;
	//瞬きさせる処理
	eyeOpenMode = animCnt / 160 % 2;
	/*pictureNum = animCnt / 80 % 2;*/
	if (eyeOpenMode == 0)//目の描画に関する処理
	{
		pictureNum = animCnt / 80 % 2;//画像は2枚あるので使う画像の選択
		animX = animCnt / 4 % 4;
		animY = animCnt / 16 % 5;
	}
	else
	{
		pictureNum = 1-animCnt / 80 % 2;
		animX = 3 - (animCnt / 4 % 4);
		animY = 4 - (animCnt / 16 % 5);
	}
	if (animCnt % 300 <= 150)//bossの揺れが切り替わる時間
		bossSwayY -= BOSS1_SWAY_UP_SPEED;
	else
		bossSwayY += BOSS1_SWAY_DOWN_SPEED;

	if (GetFallDownPointer()->fallFlg)
	{
		fallDownY -= FALLDOWN_BOSS_SPEED;
	}

	if (!GetFallDownPointer()->fallFlg&&fallDownY < 0)//直す Cnt++のせいでバグある
	{
		fallDownY += FALLDOWN_BOSS_SPEED;
	}

	if (GetFallDownPointer()->posY + FALLDOWN_BOSS_HEIGHT>0&& fallDownY < 0)
		fallDownY = -FALLDOWN_BOSS_HEIGHT;
}

void Back::DrawClearBack()
{
	PlayMovie("Data/Image/イントロ_1.avi", 2, DX_MOVIEPLAYTYPE_BCANCEL);
	endCnt++;
	if (endCnt>0)
		ResetGame();
}

void Back::DrawOverBack()
{
	PlayMovie("Data/Image/イントロ_1.avi", 2, DX_MOVIEPLAYTYPE_BCANCEL);
	endCnt++;
	if (endCnt>0)
		ResetGame();
}

void Back::DrawDark()
{
	if (darkCnt > 0)
	{
		darkCnt--;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, darkCnt *5);
		DrawGraph(0, 0, dark_gh, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void ResetBack()
{
	BackInit()->movie = false;
	BackInit()->titleMovie = false;
	BackInit()->tBossX = BOSS1_X_INIT;
	BackInit()->tBossY = 1100;
	BackInit()->fallDownY = 0;
	BackInit()->bossSwayY = 0;
	BackInit()->animTCnt = 0;
	BackInit()->animCnt = 0;
	BackInit()->titleCnt = 0;
	BackInit()->animX = 0;
	BackInit()->animY = 0;
	BackInit()->darkCnt = DARK_CNT;
	BackInit()->endCnt = 0;
}

Cloud::Cloud()
{
	posX = rand() % WINDOW_X;
	posY = WINDOW_Y-170;
	movePosX = rand() % 11 - 5;
	movePosY = rand() %  4*-1;
	rngX = rand() % 5;
	life = rand() % 200;
	used = false;
}

void Cloud::MoveCloud()
{
	if (!used)
	{
		posX = rand() % WINDOW_X;
		posY = WINDOW_Y-170;
		movePosX = rand() % 11 - 5;
		movePosY = rand() % 4 * -1;
		life = rand() % 100;
		rngX = rand() % 5;
		used = true;
	}
	if (used)
	{
		posX += movePosX;
		posY += movePosY;
		life--;
	}
	if (life < 0)
		used = false;
}

void Cloud::DrawCloud()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, life);
	DrawRectGraph(posX, posY, rngX*CLOUD_WIDTH, 0, CLOUD_WIDTH, CLOUD_HEIGHT, cloud_gh, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Cloud::CloudAll()
{
	MoveCloud();
	DrawCloud();
}


Aura::Aura()
{
	posX = rand() % WINDOW_X;
	posY = rand() % WINDOW_Y;
	if(posX>WINDOW_X/2)
		movePosX = rand() % 6+5;
	if (posX<WINDOW_X / 2)
		movePosX = rand() % 6*-1-5;
	if (posY>WINDOW_Y / 2)
		movePosY = rand() % 6+5;
	if (posY<WINDOW_Y / 2)
		movePosY = rand() % 6*-1-5;
	life = rand() % 200;
	used = false;
}

void Aura::MoveAura()
{
	if (!used)
	{
		posX = rand() % WINDOW_X;
		posY = rand() % WINDOW_Y;
		if (posX>WINDOW_X / 2)
			movePosX = rand() % 6 + 5;
		if (posX<WINDOW_X / 2)
			movePosX = rand() % 6 * -1 - 5;
		if (posY>WINDOW_Y / 2)
			movePosY = rand() % 6 + 5;
		if (posY<WINDOW_Y / 2)
			movePosY = rand() % 6 * -1 - 5;
		life = rand() % 200;
		used = true;
	}
	if (used)
	{
		posX += movePosX;
		posY += movePosY;
		life--;
	}
	if (life < 0)
		used = false;
}

void Aura::DrawAura()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, life);
	SetDrawBright(255, 217, 0);
	DrawGraph(posX, posY,aura_gh, true);
	SetDrawBright(255,255,255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Aura::AuraAll()
{
	MoveAura();
	DrawAura();
}