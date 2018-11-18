#include "Scene.h"

//********プレイヤー*******//
bool PlayerParts::loadPlayerPartsExplosionFlg;
bool playerLoadGraphFlg = false;
int PlayerParts::parts_gh;
int PlayerParts::explosionSound;
//******背景**************//
bool backGraphLoadFlg = false;
bool cloudGraphLoadFlg = false;
bool auraGraphLoadFlg = false;
int Cloud::cloud_gh;
int Aura::aura_gh;
//******パーティクル**********//
int Fishes::particle_gh;
bool particleLoadGraphFlg = false;
//******落下*************//
bool FallDownLoadGraphFlg = false;
//*******レーザー********//
int Lazer::boss1Attack_gh;
int Lazer::boss1Lazer_gh;
int Lazer::lazerSound;
int Lazer::enemyHitSound;
bool Lazer::lazerLoadFlg = false;
//*******ブレード********//
int Blade::blade_gh;
int bladeGraphLoadFlg = false;
//******ヴェノム**********//
bool venomGraphLoadFlg = false;
int Venom::venom_gh;
int Venom::venom_se;
//*******回転************//
int Rotation::rotation_gh;
int Rotation::rotation_se;
bool RotationLoadGraphFlg = false;
//*******UI**********//
bool bossHpLoadFlg = false;


Scene *sc = new Scene();
int pad;

Scene::Scene()
{
	nowScene = SCENE::TITLE;
	playNowCnt = 0;
	secretCnt = 0;
	secretState = 0;
	TitleSceneCnt = 0;
	TitleModeBgmFlg = false;
	PlayModeBgmFlg = false;
	BossModeBgmFlg = false;
	BossDeadModeBgmFlg = false;
}

Scene* GetScenePointer()
{
	return sc;
}

void Scene::SceneManager()
{
	switch (nowScene)
	{
	case SCENE::TITLE:
		DoTitleScene();
		break;
	case SCENE::TUTORIAL:
		DoTutorialScene();
		break;
	case SCENE::PLAY1:
		DoPlayScene();
		break;
	case SCENE::PLAY2:
		DoBossScene();
		break;
	case SCENE::BOSSDEAD:
		DoBossDeadScene();
		break;
	case SCENE::CLEAR:
		DoClearScene();
		break;
	case SCENE::OVER:
		DoOverScene();
		break;
	default:
		break;
	}
}

void Scene::DoTitleScene()
{
	CheckCommand();
	if (sc->secretState == 10 && !PlayerInit()->flogFlg)//隠しコマンド
	{
		PlayerInit()->player_gh = LoadGraph("Data/Image/wani_spear.png");
		PlayerInit()->flogFlg = true;
	}

	if (!TitleModeBgmFlg)
	{
		PlaySoundFile("Data/Music/bgm/PlayModeBgm.mp3", DX_PLAYTYPE_BACK);
		TitleModeBgmFlg = true;
	}

	//背景描画
	BackUpdata(BackInit());

	//デバッグ表示
	//debugController(pad);

	if (DerayButtonAandReturn() == 1)
		TitleSceneCnt++;
	if (TitleSceneCnt == 2)
	{
		nowScene = SCENE::TUTORIAL;
		StopSoundFile();
	}
}

void Scene::DoTutorialScene()
{
	//背景描画
	BackUpdata(BackInit());
	//プレイヤー描画
	PlayerUpdata(PlayerInit());
	//チュートリアル
	TutorialAll();
}

void Scene::DoPlayScene()
{
	if (!PlayModeBgmFlg)
	{
		PlaySoundFile("Data/Music/bgm/PlayModeBgm.mp3", DX_PLAYTYPE_BACK);
		PlayModeBgmFlg = true;
	}

	playNowCnt++;
	//背景描画
	BackUpdata(BackInit());
	//パーティクル
	ParticleUpdata(PlayerInit());
	//プレイヤー描画
	PlayerUpdata(PlayerInit());
	//レーザー
	LazerInit();
	LazerUpdata();
	//ブレード
	BladeUpdata();
	//ヴェノム
	VenomUpdata();
	//UI
	UIAll();

	if (playNowCnt > 4600)
	{
		playNowCnt = 0;
		PlayModeBgmFlg = false;
		//****レーザー*****//
		for (int i = 0; i < LAZER_MAX; i++)
		{
			GetLazerPointer()[i].hp = LAZER_HP;
			GetLazerPointer()[i].lazerEyeAnimCnt = 0;
			GetLazerPointer()[i].lazerEyeAnimX = 0;
			GetLazerPointer()[i].thickness = LAZER_THICKNESS_INIT;
			GetLazerPointer()[i].isDeadFlg = false;
			GetLazerPointer()[i].firingDerayCnt = 50;
			GetLazerPointer()[i].lazerExistFlg = false;
			GetLazerPointer()[i].lazerHitFlg = false;
			GetLazerPointer()[i].riseFlg = false;
			GetLazerPointer()[i].setLazerFlg = false;
			GetLazerPointer()[i].hitableFlg = false;
			GetLazerPointer()[i].lazerSoundFlg = false;
			GetLazerPointer()[i].colorR = 255;
			GetLazerPointer()[i].colorG = 0;
			GetLazerPointer()[i].colorB = 0;
		}
	}

	//シ－ン遷移
	if (PlayerInit()->playerMode == DEAD && GetPlayerPartsPointer()->PlayerParts::explosionDerayCnt < 0)//プレイヤー死亡且つ爆発見終わったら
	{
		nowScene = OVER;
		StopSoundFile();
	}

	if (GetUIPointer()->bossHp < 0)
	{
		nowScene = PLAY2;
		StopSoundFile();
		playNowCnt = 0;
	}

	//デバッグ用表示
	SetFontSize(50);
	DrawFormatString(0, 0, GetColor(0, 0, 0), "カウント:%d", playNowCnt);
	//DrawFormatString(0, 50, GetColor(0, 0, 0), "HP:%d", PlayerInit()->hp);
	//DrawFormatString(0, 100, GetColor(0, 0, 0), "プレイヤー状態:%d,ヒットフラグ:%d", PlayerInit()->playerMode, PlayerInit()->hitFlg);
	//if (CheckHitKey(KEY_INPUT_E) || pad&(1 << BUTTON_B))//自爆ボタン
		//PlayerInit()->playerMode = DEAD;
	//debugController(pad);
}

void Scene::DoBossScene()
{
	if (!BossModeBgmFlg)
	{
		PlaySoundFile("Data/Music/bgm/PlayModeBgm.mp3", DX_PLAYTYPE_BACK);
		BossModeBgmFlg = true;
	}
	playNowCnt++;
	//背景描画
	BackUpdata(BackInit());
	//フォールダウン
	FallDownUpdata();
	//ブレード
	BladeUpdata();
	//パーティクル
	ParticleUpdata(PlayerInit());
	//プレイヤー描画
	PlayerUpdata(PlayerInit());
	//ローテ
	RotationAll();
	//UI
	UIAll();

	//シ－ン遷移
	if (PlayerInit()->playerMode == DEAD && GetPlayerPartsPointer()->PlayerParts::explosionDerayCnt < 0)//プレイヤー死亡且つ爆発見終わったら
	{
		nowScene = OVER;
		StopSoundFile();
	}

	//デバッグ用表示
	SetFontSize(50);
	//DrawFormatString(0, 0, GetColor(0, 0, 0), "カウント:%d", playNowCnt);
	//DrawFormatString(0, 50, GetColor(0, 0, 0), "HP:%d", PlayerInit()->hp);
	//DrawFormatString(0, 100, GetColor(0, 0, 0), "プレイヤー状態:%d,ヒットフラグ:%d", PlayerInit()->playerMode, PlayerInit()->hitFlg);
	if (CheckHitKey(KEY_INPUT_E) || pad&(1 << BUTTON_B))//自爆ボタン
		PlayerInit()->playerMode = DEAD;
	//debugController(pad);
}

void Scene::DoBossDeadScene()
{
	if (!BossDeadModeBgmFlg)
	{
		PlaySoundFile("Data/Music/bgm/PlayModeBgm.mp3", DX_PLAYTYPE_BACK);
		BossDeadModeBgmFlg = true;
	}
	//背景描画
	BackUpdata(BackInit());
	//パーティクル
	ParticleUpdata(PlayerInit());
	//プレイヤー描画
	PlayerUpdata(PlayerInit());
}

void Scene::DoClearScene()
{
	//背景描画
	BackUpdata(BackInit());

	if (DerayButtonAandReturn() == 1)
		ResetGame();
}

void Scene::DoOverScene()
{
	//背景描画
	BackUpdata(BackInit());

	if (DerayButtonAandReturn() == 1)
		ResetGame();
}

void Scene::CheckCommand()
{
	switch (secretState)
	{
	case 0:
	case 1:
		if (pad&(1 << BUTTON_U))
			secretCnt++;
		else
			secretCnt = 0;
		if (secretCnt == 1)
			secretState++;
		break;
	case 2:
	case 3:
		if (pad&(1 << BUTTON_D))
			secretCnt++;
		else
			secretCnt = 0;
		if (secretCnt == 1)
			secretState++;
		break;
	case 4:
	case 6:
		if (pad&(1 << BUTTON_L))
			secretCnt++;
		else
			secretCnt = 0;
		if (secretCnt == 1)
			secretState++;
		break;
	case 5:
	case 7:
		if (pad&(1 << BUTTON_R))
			secretCnt++;
		else
			secretCnt = 0;
		if (secretCnt == 1)
			secretState++;
		break;
	case 8:
		if (pad&(1 << BUTTON_B))
			secretCnt++;
		else
			secretCnt = 0;
		if (secretCnt == 1)
			secretState++;
		break;
	case 9:
		if (pad&(1 << BUTTON_A))
			secretCnt++;
		else
			secretCnt = 0;
		if (secretCnt == 1)
			secretState++;
		break;
	}
}

void Scene::EndScene()
{
	PlayModeBgmFlg = false;
	EndBack();
	EndPlayer();
	EndLazer();
	EndUI();
	//EndFallDown();
	EndTutorial();
	/*EndRotation();*/
}

void LoadAll()
{
	if (!backGraphLoadFlg)
	{
		BackInit()->boss_gh1 = LoadGraph("Data/Image/boss1.png");
		BackInit()->boss_gh2 = LoadGraph("Data/Image/boss2.png");
		BackInit()->Back_gh = LoadGraph("Data/Image/BackGround.png");
		BackInit()->Title_gh = LoadGraph("Data/Image/TitleBack.png");
		BackInit()->Over_gh = LoadGraph("Data/Image/OverBack.png");
		BackInit()->Flame_gh = LoadGraph("Data/Image/Bluebar.png");
		BackInit()->floor_gh = LoadGraph("Data/Image/floor.png");
		BackInit()->tutorial_gh = LoadGraph("Data/Image/チュートリアル.png");
		backGraphLoadFlg = true;
	}
	if (!FallDownLoadGraphFlg)
	{
		GetFallDownPointer()->bossChance_gh1 = LoadGraph("Data/Image/混乱３.png");
		GetFallDownPointer()->bossChance_gh2 = LoadGraph("Data/Image/混乱１.png");
		GetFallDownPointer()->bossChanceEye_gh = LoadGraph("Data/Image/混乱２.png");
		GetFallDownPointer()->boss_gh = LoadGraph("Data/Image/bossfall.png");
		GetFallDownPointer()->bossShadow_gh = LoadGraph("Data/Image/落ちてくる影.png");
		GetFallDownPointer()->alert_gh = LoadGraph("Data/Image/注意ピン.png");
		FallDownLoadGraphFlg = true;
	}
	if (!Lazer::lazerLoadFlg)
	{
		Lazer::boss1Attack_gh = LoadGraph("Data/Image/attackasset.png");
		Lazer::boss1Lazer_gh = LoadGraph("Data/Image/縦横レーザー.png");
		Lazer::lazerSound = LoadSoundMem("Data/Music/se/laser1.mp3");
		Lazer::enemyHitSound = LoadSoundMem("Data/Music/se/shot-struck1.mp3");
		Lazer::lazerLoadFlg = true;
	}
	if (!bladeGraphLoadFlg)
	{
		Blade::blade_gh = LoadGraph("Data/Image/attackasset.png");
		bladeGraphLoadFlg = true;
	}
	if (!venomGraphLoadFlg)
	{
		Venom::venom_gh = LoadGraph("Data/Image/attackasset.png");
		Venom::venom_se = LoadSoundMem("Data/Music/se/");
		venomGraphLoadFlg = true;
	}
	if (!playerLoadGraphFlg)
	{
		PlayerInit()->player_gh = LoadGraph("Data/Image/player.png");
		PlayerInit()->playerDot_gh = LoadGraph("Data/Image/playercolor.png");
		PlayerInit()->player_effect_gh = LoadGraph("Data/Image/effect.png");
		PlayerInit()->playerHpGage_gh = LoadGraph("Data/Image/playerhp.png");
		PlayerInit()->ball_se = LoadSoundMem("Data/Music/se/");
		playerLoadGraphFlg = true;
	}
	if (!PlayerParts::loadPlayerPartsExplosionFlg)
	{
		PlayerParts::parts_gh = LoadGraph("Data/Image/player_parts.png");
		PlayerParts::explosionSound = LoadSoundMem("Data/Music/se/bomb2.mp3");
		PlayerParts::loadPlayerPartsExplosionFlg = true;
	}
	if (!RotationLoadGraphFlg)
	{
		Rotation::rotation_gh = LoadGraph("Data/Image/上窪君.png");
		Rotation::rotation_se = LoadSoundMem("Data/Music/se/");//
		RotationLoadGraphFlg = true;
	}
	if (!bossHpLoadFlg)
	{
		GetUIPointer()->bosshp_gh = LoadGraph("Data/Image/HPゲージ.png");
		bossHpLoadFlg = true;
	}
	if (!particleLoadGraphFlg)
	{
		Fishes::particle_gh = LoadGraph("Data/Image/particle.png");
		particleLoadGraphFlg = true;
	}
	if (!cloudGraphLoadFlg)
	{
		Cloud::cloud_gh = LoadGraph("Data/Image/Fog.png");
		cloudGraphLoadFlg = true;
	}
	if (!auraGraphLoadFlg)
	{
		Aura::aura_gh = LoadGraph("Data/Image/particle.png");
		auraGraphLoadFlg = true;
	}
}

void ResetScene()
{
	sc->nowScene = TITLE;
	sc->playNowCnt = 0;
	sc->TitleSceneCnt = 0;
	sc->TitleModeBgmFlg = false;
	sc->PlayModeBgmFlg = false;
	sc->BossModeBgmFlg = false;
	sc->BossDeadModeBgmFlg = false;
}

void ResetGame()
{
	ResetPlayer();
	ResetBack();
	ResetPlayerParts();
	ResetBlade();
	ResetLazer();
	ResetVenom();
	ResetUI();
	ResetTutorial();
	ResetFallDown();
	ResetRotationAll();
	ResetScene();
}

void Game()
{
	pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	sc->SceneManager();
}

void EndScene()
{
	sc->EndScene();
}

void debugController(int pad)
{
	for (int i = 0; i < 28; i++)
	{
		if (pad&(1 << i))
		{
			DrawFormatString(0, i * 15, GetColor(255, 255, 255), "%dを入力中です", i);
		}
	}
}

int GetPad()
{
	return pad;
}

int DerayButtonAandReturn()
{
	static int buttonCnt = 0;
	if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN) || pad&(1 << BUTTON_A))
		buttonCnt++;
	else
		buttonCnt = 0;

	return buttonCnt;
}