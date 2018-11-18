#include "Lazer.h"
#include "Scene.h"

Lazer lz[LAZER_MAX];
//int Lazer::boss1Attack_gh;
//int Lazer::boss1Lazer_gh;
//int Lazer::lazerSound;
//int Lazer::enemyHitSound;
//bool Lazer::lazerLoadFlg = false;

Lazer::Lazer()//コンストラクタ
{
	hp = LAZER_HP;
	side = LEFT_L;
	isDeadFlg = false;
	lazerEyeAnimCnt = 0;
	lazerEyeAnimX = 0;
	lazerHitAnimCnt = 0;
	lazerHitAnimX = 0;
	posY = rand() % WINDOW_Y;
	brightness = LAZER_BRIGHTNESS;
	firingDerayCnt = 50;
	thickness = LAZER_THICKNESS_INIT;
	colorR = 255, colorG = 0, colorB = 0;
	lazerHitFlg = false;
	riseFlg = false;
	lazerExistFlg = false;
	setLazerFlg = false;
	lazerSoundFlg=false;
}

void CreateLazer()
{
	/*if (!Lazer::lazerLoadFlg)
	{
		Lazer::boss1Attack_gh = LoadGraph("Data/Image/attackasset.png", true);
		Lazer::boss1Lazer_gh= LoadGraph("Data/Image/縦横レーザー.png", true);
		Lazer::lazerSound = LoadSoundMem("Data/Music/se/laser1.mp3");
		Lazer::enemyHitSound= LoadSoundMem("Data/Music/se/shot-struck1.mp3");
		Lazer::lazerLoadFlg = true;
	}*/
	for (int i = 0; i < LAZER_MAX; i++)
	{
		if (!lz[i].lazerExistFlg&& !lz[i].isDeadFlg)
		{
			lz[i].brightness = LAZER_BRIGHTNESS;
			lz[i].firingDerayCnt = 50;
			//lz[i].posY = rand() % WINDOW_Y;
			lz[i].lazerExistFlg = true;
		}
	}
}

void Lazer::MoveLazer(int type)//レーザーの一連の挙動を管理
{
	lazerEyeAnimCnt++;
	firingDerayCnt--;

	if (firingDerayCnt <= 0)
		hitableFlg = true;//当たり判定発生
	if (hitableFlg)
	{
		if (!lazerSoundFlg)
		{
			PlaySoundMem(lazerSound, DX_PLAYTYPE_BACK);
			lazerSoundFlg = true;
		}
		if (!riseFlg)
		{
			LazerSway();//レーザー揺らす処理
			thickness += LAZER_RISE_SPEED;//レーザー太くする処理
			if (thickness > LAZER_THICKNESS_MAX)
				riseFlg = true;
		}
	}
	if (riseFlg)
	{
		LazerSway();//レーザー揺らす処理
		thickness--;
		brightness -= LAZER_BRIGHTNESS_SUBTRACTION;
		if (thickness <= 0)
		{
			riseFlg = false;
			lazerExistFlg = false;
			setLazerFlg = false;
			hitableFlg = false;
		}
	}
}

void Lazer::DrawLazer(int type)
{
	lazerEyeAnimX = lazerEyeAnimCnt / 8 % LAZER_EYE_ANIM_MAX;
	if (lazerExistFlg)
	{
		switch (type)
		{
		case LEFT_L:
		case RIGHT_L:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, brightness);//透明度上げる
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);//加算ブレンド
			DrawLine(0, posY, WINDOW_X, posY, GetColor(255, 0, 0), thickness);
			if (thickness == 1)
				DrawLine(0, posY, WINDOW_X, posY, GetColor(255, 0, 0), thickness / 2);//太さは0にならない
			else
				DrawLine(0, posY, WINDOW_X, posY, GetColor(255, 255, 255), thickness / 2);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			if (type == RIGHT_L)
			{
				switch (lazerHitFlg)//プレイヤーが当たってきたら輝度を赤くしてる
				{
				case true:
					SetDrawBright(255, 0, 0);
					DrawRectGraph(WINDOW_X - 300, posY - LAZER_EYE_MARGIN, lazerEyeAnimX*BOSS1_LAZER_EYE_WIDTH, 0, BOSS1_LAZER_EYE_WIDTH, BOSS1_LAZER_EYE_HEIGHT, boss1Lazer_gh, true);//目玉//要画像変更
					SetDrawBright(255, 255, 255);
					break;
				case false:
					DrawRectGraph(WINDOW_X - 300, posY - LAZER_EYE_MARGIN, lazerEyeAnimX*BOSS1_LAZER_EYE_WIDTH, 0, BOSS1_LAZER_EYE_WIDTH, BOSS1_LAZER_EYE_HEIGHT, boss1Lazer_gh, true);//目玉//要画像変更
					break;
				}
			}
			else
			{
				switch (lazerHitFlg)
				{
				case true:
					SetDrawBright(255, 0, 0);
					DrawRectGraph(-75, posY - LAZER_EYE_MARGIN, lazerEyeAnimX*BOSS1_LAZER_EYE_WIDTH, 0, BOSS1_LAZER_EYE_WIDTH, BOSS1_LAZER_EYE_HEIGHT, boss1Lazer_gh, true, true);
					SetDrawBright(255, 255, 255);
					break;
				case false:
					DrawRectGraph(-75, posY - LAZER_EYE_MARGIN, lazerEyeAnimX*BOSS1_LAZER_EYE_WIDTH, 0, BOSS1_LAZER_EYE_WIDTH, BOSS1_LAZER_EYE_HEIGHT, boss1Lazer_gh, true, true);
					break;
				}
			}
			break;
		case UP_L:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, brightness);//透明度上げる
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);//加算ブレンド
			DrawLine(posX, 0, posX, WINDOW_Y, GetColor(255, 0, 0), thickness);
			if (thickness == 1)
				DrawLine(posX, 0, posX, WINDOW_Y, GetColor(255, 0, 0), thickness / 2);//太さは0にならない
			else
				DrawLine(posX, 0, posX, WINDOW_Y, GetColor(255, 255, 255), thickness / 2);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			DrawRectGraph(posX-190, -175, lazerEyeAnimX*BOSS1_LAZER_EYE_WIDTH, BOSS1_LAZER_EYE_HEIGHT, BOSS1_LAZER_EYE_WIDTH, BOSS1_LAZER_EYE_HEIGHT, boss1Lazer_gh, true);
			break;

		}
		if (lazerHitFlg)
		{
			lazerHitAnimCnt++;
			lazerHitAnimX = lazerHitAnimCnt / 5 % 6;
			DrawRectGraph(PlayerInit()->posX, PlayerInit()->posY, lazerHitAnimX * 182, 127, 182, 189, PlayerInit()->player_effect_gh, true);
			PlaySoundMem(enemyHitSound, DX_PLAYTYPE_BACK);
		}
		else
		{
			lazerHitAnimCnt = 0;
			lazerHitAnimX = 0;
		}
	}
}

void LazerInit()
{
	CreateLazer();
}

void LazerUpdata()
{
	//レーザーは0番目から開始
	//最大値はdefine.hのLAZER_MAXで決定
	//SetLazer(n番目のレーザー,呼び出す(プレイモードでの)カウント,呼び出すXまたはY座標,出現する方向)
	//レーザーが太線になるまでのディレイは33フレーム
	SetLazer(0, 450, 300, UP_L);
	SetLazer(1, 690, 1400, UP_L);
	SetLazer(2, 920, 700, RIGHT_L);
	SetLazer(3, 1155, 700, UP_L);
	SetLazer(4, 1155, 1300, UP_L);
	SetLazer(5, 1305, 1000, UP_L);
	SetLazer(6, 1305, 300, UP_L);
	SetLazer(7, 1390, 700, RIGHT_L);
	SetLazer(8, 1545, 700, UP_L);

	SetLazer(9, 1630, 300, UP_L);
	SetLazer(10, 1630, 1200, UP_L);

	SetLazer(11, 1830, 1000, UP_L);
	SetLazer(12, 1950, 300, UP_L);
	SetLazer(13, 2070, 900, UP_L);
	SetLazer(14, 2190, 1200, UP_L);
	SetLazer(15, 2310, 600, UP_L);
	SetLazer(16, 2430, 1000, UP_L);
	SetLazer(17, 2600, 700, LEFT_L);

	SetLazer(18, 2792, 1300, UP_L);
	SetLazer(19, 2821, 1000, UP_L);
	SetLazer(20, 2852, 600, UP_L);
	SetLazer(21, 2881, 300, UP_L);

	SetLazer(22, 3185, 700, LEFT_L);
	SetLazer(23, 3408, 700, RIGHT_L);

	SetLazer(24, 3720, 100, UP_L);
	SetLazer(25, 3720, 700, UP_L);
	SetLazer(26, 3832, 300, UP_L);
	SetLazer(27, 3832, 1200, UP_L);

	SetLazer(28, 3960, 700, RIGHT_L);
	SetLazer(29, 4245, 700, LEFT_L);

	SetLazer(30, 100, 700, RIGHT_L);
	SetLazer(31, 250, 700, LEFT_L);
}

void SetLazer(int i, int cnt, int posXorY,int type)
{
	if (cnt == GetScenePointer()->playNowCnt)
	{
		lz[i].setLazerFlg = true;//レーザーが作られるようになるフラグ
		switch (type)
		{
		case RIGHT_L:
		case LEFT_L:
			lz[i].posY = posXorY;
			break;
		case UP_L:
			lz[i].posX = posXorY;
			break;
		}
		lz[i].side = type;
	}
	if (lz[i].setLazerFlg)
	{
		lz[i].MoveLazer(type);
		lz[i].DrawLazer(type);
	}
}

void EndLazer()
{
	/*delete[] lz;
	for (int i = 0; i < LAZER_MAX; i++)
	{
		lz[i] = nullptr;
	}*/
}

void Lazer::LazerSway()
{
	if (lazerHitFlg)
		posY += rand() % 31 - 15;
	else
		posY += rand() % 7 - 3;
}

Lazer* GetLazerPointer()
{
	//switch()
	return lz;
}

void ResetLazer()
{
	for (int i = 0; i < LAZER_MAX; i++)
	{
		lz[i].hp = LAZER_HP;
		lz[i].lazerEyeAnimCnt = 0;
		lz[i].lazerEyeAnimX = 0;
		lz[i].thickness = LAZER_THICKNESS_INIT;
		lz[i].isDeadFlg = false;
		lz[i].firingDerayCnt = 50;
		lz[i].lazerExistFlg = false;
		lz[i].lazerHitFlg = false;
		lz[i].riseFlg = false;
		lz[i].setLazerFlg = false;
		lz[i].hitableFlg = false;
		lz[i].lazerSoundFlg = false;
		lz[i].colorR = 255;
		lz[i].colorG = 0;
		lz[i].colorB = 0;
	}
}