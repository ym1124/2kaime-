#include "Player.h"
#include "DxLib.h"
#include "define.h"
#include "Lazer.h"
#include "Scene.h"

Player *tpl = PlayerInit();
PlayerParts parts[PLAYER_PARTS_MAX];
int tempLi = 0;
bool lazerHitFlg = false;
int tempBi = 0;
bool bladeHitFlg = false;
int tempVi = 0;
bool venomHitFlg = false;

bool loadExplosionFlg = false;
bool PlayerParts::explosionFlg;
int PlayerParts::explosionDerayCnt;
int explosion_gh;
int animX = 0, animCnt = 0;

Player::Player()
{
	posX = PLAYERPOS_X_INIT;
	posY = PLAYERPOS_Y_INIT;
	hp = PLAYER_HP;
	playerMode = NORMAL;
	ballModeCnt = 0;
	animCnt = 0;
	isLeft = false;
	jumpX = 0;
	jumpXCnt = 0;
	knockBackAnimCnt = 0;
	knockBackAnimX = 0;
	playerRainbowFlg = false;
	hitFlg = false;
	jumpFlg = false;
	knockBackFlg = false;
	knockBackJumpFlg = false;
	ballModeFlg = false;
	rotationHitFlg = false;
	flogFlg = false;
	playerR = rand() % 255, playerG = rand() % 255, playerB = rand() % 255;
}

Player* PlayerInit()
{
	static Player *pl = new Player();
	return pl;
}

void PlayerUpdata(Player *pl)
{
	pl->pad = GetPad();
	pl->DrawPlayer();
	pl->MovePlayer();
	pl->Explosion();
	PlayerHitCheck(GetLazerPointer(), GetBladePointer(), GetVenomPointer());
}

void EndPlayer()
{
	Player *pl = PlayerInit();
	delete pl;
	pl = nullptr;
}

void Player::DrawPlayer()
{
	animCnt++;
	animX = animCnt / 3 % PLAYER_ANIM_MAX;
	ballAnimX = animCnt / 3 % 6;
	switch (playerMode)
	{
	case NORMAL:
		if (!isLeft)//どっち向いてるか
			DrawRectGraph(posX, posY, animX*PLAYER_WIDTH, 0, PLAYER_WIDTH, PLAYER_HEIGHT, player_gh, true, false);
		else
			DrawRectGraph(posX, posY, animX*PLAYER_WIDTH, 0, PLAYER_WIDTH, PLAYER_HEIGHT, player_gh, true, true);
		if (playerRainbowFlg == true)//ドットの色変更
		{
			SetDrawBright(playerR, playerG, playerB);
			playerR--;
			playerG--;
			playerB--;
		}
		//if (!isLeft)
			//DrawRectGraph(posX, posY, animX*PLAYER_WIDTH, 0, PLAYER_WIDTH, PLAYER_HEIGHT, playerDot_gh, true, false);//ドット描画
		if(isLeft)
			DrawRectGraph(posX, posY, animX*PLAYER_WIDTH, 0, PLAYER_WIDTH, PLAYER_HEIGHT, player_gh, true, true);
		SetDrawBright(255, 255, 255);//描画色戻す
		if (jumpFlg)
		{
			DrawRectGraph(posX, posY+PLAYER_HEIGHT, jumpX*133, 505, 133, 75, player_effect_gh, true, false);
			jumpXCnt++;
			jumpX = jumpXCnt / 2;
		}
		break;

	case BALL:
		if (CheckHitKey(KEY_INPUT_RIGHT) || pad&(1 << BUTTON_R))//右に進んでいるなら
		{
			DrawRectGraph(posX, posY + PLAYER_LEG_HEIGHT, ballAnimX*PLAYER_BALL_WIDTH, 400, PLAYER_BALL_WIDTH, PLAYER_BALL_HEIGHT, player_gh, true, false);

			//if (playerRainbowFlg == true)
				//SetDrawBright(playerR, playerG, playerB);
			//DrawRectGraph(posX, posY + PLAYER_LEG_HEIGHT, ballAnimX*PLAYER_BALL_WIDTH, 400, PLAYER_BALL_WIDTH, PLAYER_BALL_HEIGHT, playerDot_gh, true, false);
		}
		else if (CheckHitKey(KEY_INPUT_RIGHT) || pad&(1 << BUTTON_L))//左に進んでいるなら
		{
			DrawRectGraph(posX, posY + PLAYER_LEG_HEIGHT, ballAnimX*PLAYER_BALL_WIDTH, 400, PLAYER_BALL_WIDTH, PLAYER_BALL_HEIGHT, player_gh, true, true);
			//if (playerRainbowFlg == true)
				//SetDrawBright(playerR, playerG, playerB);
			//DrawRectGraph(posX, posY + PLAYER_LEG_HEIGHT, ballAnimX*PLAYER_BALL_WIDTH, 400, PLAYER_BALL_WIDTH, PLAYER_BALL_HEIGHT, playerDot_gh, true, true);
		}
		else
		{
			DrawRectGraph(posX, posY + PLAYER_LEG_HEIGHT, ballAnimX*PLAYER_BALL_WIDTH, 400, PLAYER_BALL_WIDTH, PLAYER_BALL_HEIGHT, player_gh, true, false);

			//if (playerRainbowFlg == true)
				//SetDrawBright(playerR, playerG, playerB);
			//DrawRectGraph(posX, posY + PLAYER_LEG_HEIGHT, ballAnimX*PLAYER_BALL_WIDTH, 400, PLAYER_BALL_WIDTH, PLAYER_BALL_HEIGHT, playerDot_gh, true, false);
		}
		SetDrawBright(255, 255, 255);
		if ((lazerHitFlg))//どれか１つのオブジェクトに当たってさえいれば当たっている判定
		{
			DrawRectGraph(posX-10, posY+20, ballAnimX*PLAYER_INVINCIBLE_WIDTH, 0, PLAYER_INVINCIBLE_WIDTH, PLAYER_INVINCIBLE_HEIGHT, player_effect_gh, true, false);
			if(GetScenePointer()->playNowCnt/3%2==1)
				PlaySoundMem(ball_se, DX_PLAYTYPE_BACK);
		}
		break;

	case DAMAGE:
		if (!isLeft)//どっち向いてるか
			DrawRectGraph(posX, posY, animX*PLAYER_WIDTH, 0, PLAYER_WIDTH, PLAYER_HEIGHT, player_gh, true, false);
		else
			DrawRectGraph(posX, posY, animX*PLAYER_WIDTH, 0, PLAYER_WIDTH, PLAYER_HEIGHT, player_gh, true, true);
		if (playerRainbowFlg == true)
			SetDrawBright(playerR, playerG, playerB);

		//if (!isLeft)
			//DrawRectGraph(posX, posY, animX*PLAYER_WIDTH, 0, PLAYER_WIDTH, PLAYER_HEIGHT, playerDot_gh, true, false);//ドット描画
		if(isLeft)
			DrawRectGraph(posX, posY, animX*PLAYER_WIDTH, 0, PLAYER_WIDTH, PLAYER_HEIGHT, player_gh, true, true);
		SetDrawBright(255, 255, 255);//描画色戻す
		if(PlayerInit()->rotationHitFlg == true)
			DrawRectGraph(posX, posY, 182 * knockBackAnimX, 316, 182, 189, player_effect_gh, true);
		break;
	}
	if (GetScenePointer()->nowScene == BOSSDEAD)
	{
		PlayerInit()->posX += rand() % 16 - 7;
		PlayerInit()->posY += rand() % 16 - 7;
	}

	switch (playerMode)//ドットの色調整
	{
	case NORMAL:
		if (playerR >= 9)
			playerR--;
		if (playerG >= 11)
			playerG--;
		if (playerB >= 99)
			playerB--;
		if (playerR <= 9 && playerG <= 11 && playerB <= 99)
		{
			playerR = rand() % 246 + 10;
			playerG = rand() % 244 + 12;
			playerB = rand() % 156 + 100;
		}
		break;
	case BALL:
		playerR--;
		playerG--;
		playerB--;
		if (playerR <= 0 && playerG <= 0 && playerB <= 0)
		{
			playerR = rand() % 255;
			playerG = rand() % 255;
			playerB = rand() % 255;
		}
		break;
	case DAMAGE:
		playerR = 155;
		playerG = 20;
		playerB = 20;
		break;
	}

	if (hitFlg&&playerMode != BALL&&playerMode != DEAD)
		playerMode = DAMAGE;
	if (!hitFlg&&playerMode != BALL&&playerMode != DEAD)
		playerMode = NORMAL;
}

void Player::MovePlayer()
{
	switch (playerMode)
	{
	case NORMAL:
	case DAMAGE:
		//矢印キー移動
		if (CheckHitKey(KEY_INPUT_RIGHT) || pad&(1 << BUTTON_R))
		{
			posX += PLAYER_SPEED_X;
			isLeft = false;
		}
		/*if (CheckHitKey(KEY_INPUT_UP) || pad&(1 << BUTTON_U))
			posY -= PLAYER_SPEED_Y;*/
		if (CheckHitKey(KEY_INPUT_LEFT) || pad&(1 << BUTTON_L))
		{
			posX -= PLAYER_SPEED_X;
			isLeft = true;
		}
		/*if (CheckHitKey(KEY_INPUT_DOWN) || pad&(1 << BUTTON_D))
			posY += PLAYER_SPEED_Y;*/
			//移動幅制限
		if (posX >= WINDOW_X - PLAYER_WIDTH)
			posX = WINDOW_X - PLAYER_WIDTH;
		if (posX <= 0)
			posX = 0;
		if (posY >= WINDOW_Y - PLAYER_HEIGHT)
			posY = WINDOW_Y - PLAYER_HEIGHT;
		if (posY <= 0)
			posY = 0;
		break;

	case BALL:
		//矢印キー移動
		if (CheckHitKey(KEY_INPUT_RIGHT) || pad&(1 << BUTTON_R))
		{
			posX += PLAYER_BALL_SPEED_X;
			isLeft = false;
		}
		/*if (CheckHitKey(KEY_INPUT_UP) || pad&(1 << BUTTON_U))
			posY -= PLAYER_BALL_SPEED_Y;*/
		if (CheckHitKey(KEY_INPUT_LEFT) || pad&(1 << BUTTON_L))
		{
			posX -= PLAYER_BALL_SPEED_X;
			isLeft = true;
		}
		/*if (CheckHitKey(KEY_INPUT_DOWN) || pad&(1 << BUTTON_D))
			posY += PLAYER_BALL_SPEED_Y;*/
			//移動幅制限
		if (posX >= WINDOW_X - PLAYER_BALL_WIDTH)
			posX = WINDOW_X - PLAYER_BALL_WIDTH;
		if (posX <= 0)
			posX = 0;
		if (posY >= WINDOW_Y - PLAYER_BALL_HEIGHT)
			posY = WINDOW_Y - PLAYER_BALL_HEIGHT;
		if (posY <= 0)
			posY = 0;
		BallSystem();
		break;
	}
	// ジャンプ
	Jump();
}

void Player::KnockBack(Lazer *lz, Blade *bl, Venom *ve)
{
	if (!knockBackJumpFlg&&hitFlg&&!GetPlayerPointer()->jumpFlg)
	{
		knockBackJumpFlg = true;
		posYPrev = posY;
		posY = posY - KNOCKBACK_JUMP_POWER;
	}

	if (posY >= PLAYERPOS_Y_INIT)
	{
		knockBackJumpFlg = false;
		knockBackAnimCnt = 0;
		knockBackAnimX = 0;
		posY = PLAYERPOS_Y_INIT;
	}

	//ノックバック処理
	if (knockBackJumpFlg&&!GetPlayerPointer()->jumpFlg)
	{
		for (int i = 0; i < LAZER_MAX; i++)
		{
			if (lz[i].hitableFlg&&lazerHitFlg)
			{
				switch (lz[i].side)
				{
				case RIGHT_L:
					posX -= 2;
					break;
				case LEFT_L:
					posX += 2;
					break;
				}
			}
		}
		for (int i = 0; i < BLADE_MAX; i++)
		{
			if (bl[i].bladeExistFlg&&bladeHitFlg)
			{
				switch (bl[i].side)
				{
				case RIGHT_B:
					posX -= 2;
					break;
				case LEFT_B:
					posX += 2;
					break;
				}
			}
		}
		for (int i = 0; i < VENOM_MAX; i++)
		{
			if (ve[i].venomExistFlg&&venomHitFlg)//existFlgでやるとバグのこるけどとりあえず妥協
			{
				switch (ve[i].side)
				{
				case RIGHT_V:
					posX -= 2;
					break;
				case LEFT_V:
					posX += 2;
					break;
				}
			}
		}
		if (knockBackJumpFlg)
		{
			knockBackAnimCnt++;
			knockBackAnimX = knockBackAnimCnt / 5 % 3;
			DrawRectGraph(posX, posY, 182 * knockBackAnimX, 316, 182, 189, player_effect_gh, true);
		}
		posYTemp = posY;
		posY += (posY - posYPrev) + 1;
		posYPrev = posYTemp;
	}
}

void PlayerHitCheck(Lazer *lz, Blade *bl, Venom *ve)
{
	//レーザーの当たり判定消える瞬間に停止する。無限ループに入ってる←当たりながら消えた場合existFlgがfalseになって一生ループする
	tpl = PlayerInit();
	if (GetScenePointer()->nowScene == PLAY1|| GetScenePointer()->nowScene == PLAY2)
	{
		//レーザー当たり判定
		for (int i = 0; i < LAZER_MAX; i++)
		{
			if (lazerHitFlg)
				i = tempLi;
			if (!lz[i].lazerExistFlg)
				lazerHitFlg = false;
			if (lz[i].lazerExistFlg && lz[i].hitableFlg)//２つの当たり判定を取らないために各々に&&pl->hitFlg==falseにする？
			{
				switch (lz[i].side)
				{
				case LEFT_L:
				case RIGHT_L:
					if (((tpl->posY + PLAYER_HEIGHT)>(lz[i].posY - lz[i].thickness / 2)) && (tpl->posY < (lz[i].posY + lz[i].thickness / 2)))
						lazerHitFlg = true;
					else
						lazerHitFlg = false;
					break;
				case UP_L:
					if (((tpl->posX + PLAYER_WIDTH) > (lz[i].posX - lz[i].thickness / 2)) && (tpl->posX < (lz[i].posX + lz[i].thickness / 2)))
						lazerHitFlg = true;
					else
						lazerHitFlg = false;
					break;
				}
				if (lazerHitFlg)
				{
					tempLi = i;
					break;//ブレイクしないと次の繰り返しでfalseに入る//これだと複数レーザー同時に出たとき対応できない？→if(tpl->hitFlg==true)break;に変更？
				}
			}
		}
		if (GetScenePointer()->nowScene != PLAY1)
			lazerHitFlg = false;

		//ブレード当たり判定
		for (int i = 0; i < BLADE_MAX; i++)
		{
			if (bladeHitFlg)
				i = tempBi;
			if (!bl[i].bladeExistFlg)
				bladeHitFlg = false;
			if (bl[i].bladeExistFlg)
			{
				if (((tpl->posY + PLAYER_HEIGHT)>(bl[i].posY+30)) && (tpl->posY < (bl[i].posY + BLADE_HEIGHT-30)) && (tpl->posX + PLAYER_WIDTH>bl[i].posX+30&&tpl->posX < bl[i].posX + BLADE_WIDTH-30))
				{
					bladeHitFlg = true;
				}
				else
				{
					bladeHitFlg = false;//複数刃がある時だとi=0がこっちを通って当たり判定消えてしまう
				}
				if (bladeHitFlg)
				{
					tempBi = i;
					break;
				}
			}
		}


		//ベノム当たり判定
		for (int i = 0; i < VENOM_MAX; i++)
		{
			if (venomHitFlg)
				i = tempVi;
			if (!ve[i].venomExistFlg)
				venomHitFlg = false;
			if (ve[i].venomExistFlg)
			{
				if (((tpl->posY + PLAYER_HEIGHT)>(ve[i].posY+30)) && (tpl->posY < (ve[i].posY + VENOM_HEIGHT-30)) && (tpl->posX + PLAYER_WIDTH>ve[i].posX+30&&tpl->posX < ve[i].posX + VENOM_WIDTH-30))
					venomHitFlg = true;
				else
					venomHitFlg = false;
			}
			if (venomHitFlg)
			{
				tempVi = i;
				break;
			}
		}
		if (GetScenePointer()->nowScene != PLAY1)
			venomHitFlg = false;

		if ((lazerHitFlg) && ((tpl->playerMode == NORMAL) || (tpl->playerMode == DAMAGE)))//どれか１つのオブジェクトに当たってさえいれば当たっている判定
		{
			tpl->hitFlg = true;
			//DrawFormatString(1200, 100, GetColor(255, 255, 255), "当たっています");
		}
		else if ((bladeHitFlg || venomHitFlg) && ((tpl->playerMode == NORMAL) || (tpl->playerMode == DAMAGE) || (tpl->playerMode == BALL)))
		{
			tpl->hitFlg = true;
			tpl->playerMode = NORMAL;
			//DrawFormatString(1200, 100, GetColor(255, 255, 255), "当たっています");
		}
		else
			tpl->hitFlg = false;

		if (tpl->hitFlg)//ヒット中の処理
		{
			tpl->playerRainbowFlg = true;
			tpl->hp--;
			PlaySoundMem(tpl->playerDamage_se, DX_PLAYTYPE_BACK);
		}

		else
		{
			tpl->playerRainbowFlg = false;
		}

		//ノックバック処理
		tpl->KnockBack(lz, bl, ve);

		if (tpl->hitFlg)
			StartJoypadVibration(DX_INPUT_PAD1, 200, 10);

		if (tpl->hp < 0)
		{
			tpl->playerMode = DEAD;
			StartJoypadVibration(DX_INPUT_PAD1, 500, 10);
		}
	}
	if (GetScenePointer()->nowScene == PLAY2)
	{
		if (tpl->rotationHitFlg && ((tpl->playerMode == NORMAL) || (tpl->playerMode == DAMAGE) || (tpl->playerMode == BALL)))
		{
			tpl->hitFlg = true;
			tpl->playerMode = NORMAL;
			/*DrawFormatString(1200, 100, GetColor(255, 255, 255), "当たっています");*/
		}
		else
			tpl->hitFlg = false;
		if (tpl->hitFlg)//ヒット中の処理
		{
			tpl->playerRainbowFlg = true;
			tpl->hp--;
		}

		else
		{
			tpl->playerRainbowFlg = false;
		}

		//ノックバック処理追加

		if (tpl->hitFlg)
			StartJoypadVibration(DX_INPUT_PAD1, 200, 10);

		if (tpl->hp < 0)
		{
			tpl->playerMode = DEAD;
			StartJoypadVibration(DX_INPUT_PAD1, 500, 10);
		}
	}
}

void Player::Jump()
{
	if (posY >= PLAYERPOS_Y_INIT)
		jumpFlg = false;

	//ジャンプ処理
	if (jumpFlg)
	{
		ballModeFlg = false;
		posYTemp = posY;
		posY += (posY - posYPrev) + 1;
		posYPrev = posYTemp;
	}

	if ((posY - posYPrev) + 1 >= 0 && jumpFlg)
	{
		playerMode = BALL;
	}

	if (DerayButtonAandReturn() == 1 && !jumpFlg && (playerMode == NORMAL || playerMode == DAMAGE))
	{
		jumpFlg = true;
		posYPrev = posY;
		posY = posY - JUMP_POWER;
		jumpX = 0;
		jumpXCnt = 0;
		PlaySoundMem(jump_se, DX_PLAYTYPE_BACK);
	}
}

void Player::Explosion()
{
	if (playerMode == DEAD)
	{
		PlayerParts::explosionFlg = true;
		GetPlayerPointer()->hp = -1;
	}
	for (int i = 0; i < PLAYER_PARTS_MAX; i++)
	{
		parts[i].ExplosionAll(i);
	}
}

void Player::BallSystem()
{
	ballModeCnt++;
	if (!(CheckHitKey(KEY_INPUT_SPACE) || pad&(1 << BUTTON_A)) || ballModeFlg)//ボールでいる時間の制限
	{
		playerMode = NORMAL;
		ballModeCnt = 0;
	}
	if (ballModeCnt > BALL_TIME)
	{
		ballModeCnt = 0;
		ballModeFlg = true;
	}
}

Player* GetPlayerPointer()
{
	tpl = PlayerInit();
	return tpl;
}

void ResetPlayer()
{
	tpl->posX = PLAYERPOS_X_INIT;
	tpl->posY = PLAYERPOS_Y_INIT;
	tpl->hp = PLAYER_HP;
	tpl->playerMode = NORMAL;
	tpl->ballModeCnt = 0;
	tpl->animCnt = 0;
	tpl->ballAnimX = 0;
	tpl->playerRainbowFlg = false;
	tpl->hitFlg = false;
	tpl->jumpFlg = false;
	tpl->ballModeFlg = false;
	tpl->isDead = false;
	tpl->playerR = rand() % 255;
	tpl->playerG = rand() % 255;
	tpl->playerB = rand() % 255;
	tempLi = 0;
	lazerHitFlg = false;
	tempBi = 0;
	bladeHitFlg = false;
	tempVi = 0;
	venomHitFlg = false;
}


//************PlayerPartsクラス**************//

PlayerParts::PlayerParts()
{
	PlayerParts::explosionFlg = false;
	PlayerParts::loadPlayerPartsExplosionFlg = false;
	moveXPower = rand() % 21 - 10;
	moveYPower = rand() % -10;
	angle = DX_PI / 180;
};

void PlayerParts::Explosion()
{
	if (!loadExplosionFlg)
	{
		explosion_gh = LoadGraph("Data/Image/effect1.png");
		loadExplosionFlg = true;
	}
	if (!explosionFlg)
	{
		posX = tpl->posX;
		posY = tpl->posY;
		posYPrev = posY;
		posY = posY - (rand() % 30 + 10);
		PlayerParts::explosionDerayCnt = EXPLOSION_DERAY_CNT;
	}
	if (explosionFlg)
	{
		posX += moveXPower;
		posYTemp = posY;
		posY += (posY - posYPrev) + 1;
		posYPrev = posYTemp;
		PlayerParts::explosionDerayCnt--;
	}
}

void DrawEffect()
{
	if (tpl->playerMode == DEAD)
	{
		if (animCnt == 1)
		{
			PlaySoundMem(PlayerParts::explosionSound, DX_PLAYTYPE_BACK);
		}
		animCnt++;
		animX = animCnt / 50;
		DrawRectGraph(tpl->posX, tpl->posY, EXPLOSION_WIDTH*animX, 0, EXPLOSION_WIDTH, EXPLOSION_HEIGHT, explosion_gh, true);
	}
}

void PlayerParts::DrawParts(int i)
{
	if (!PlayerParts::loadPlayerPartsExplosionFlg)
	{
		PlayerParts::loadPlayerPartsExplosionFlg = true;
	}
	if (explosionFlg)
	{
		angle += 0.3;
		DrawRectRotaGraph(posX, posY, i*PLAYER_PARTS_WIDTH, 0, PLAYER_PARTS_WIDTH, PLAYER_PARTS_HEIGHT, 1, angle, parts_gh, true);
	}
}

void PlayerParts::ExplosionAll(int i)
{
	Explosion();
	DrawEffect();
	DrawParts(i);
}

PlayerParts* GetPlayerPartsPointer()
{
	return parts;
}

void ResetPlayerParts()
{
	PlayerParts::explosionFlg = false;
	animCnt = 0;
	animX = 0;
	for (int i = 0; i < PLAYER_PARTS_MAX; i++)
	{
		parts[i].moveXPower = rand() % 21 - 10;
		parts[i].moveYPower = rand() % -10;
		parts[i].angle = DX_PI / 180;
	}
};