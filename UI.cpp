#include "UI.h"
#include "define.h"
#include "Lazer.h"
#include "Player.h"

UI *ui = new UI();
Damage dm[DAMAGE_MAX];
Lazer *tlz = GetLazerPointer();
int damage = 0;

UI::UI()
{
	hpPosX = BOSSHP_X_INIT;
	hpPosY = BOSSHP_Y_INIT;
	bossHp = BOSSHP_INIT;
	hpAnimX = bossHp;
	hpAnimX2 = GetFallDownPointer()->bossHp;
	hpRate = 647/1000.f;
	hpRate2 = 647 / 1000.f;
}

void UI::DrawHp()
{
	if (GetScenePointer()->nowScene == PLAY1)
	{
		hpAnimX = hpRate*bossHp;
		DrawRectGraph(hpPosX, hpPosY, 820, 0, 820, BOSSHP_GAGE_Y, bosshp_gh, true);
		DrawRectGraph(hpPosX, hpPosY, 0, 0, hpAnimX, BOSSHP_GAGE_Y, bosshp_gh, true);
	}
	if (GetScenePointer()->nowScene == PLAY2)
	{
		hpAnimX2 = hpRate2*GetFallDownPointer()->bossHp;
		DrawRectGraph(hpPosX, hpPosY, 820, 173, 820, BOSSHP_GAGE_Y, bosshp_gh, true);
		DrawRectGraph(hpPosX, hpPosY, 0, 0, hpAnimX2, BOSSHP_GAGE_Y, bosshp_gh, true);
	}
}

void UI::HpManager()//bossダメージ減らすのはフラグ１つ作って管理したほうが良い
{
	for (int i = 0; i < LAZER_MAX; i++)
	{
		if (GetPlayerPointer()->playerMode != BALL)
			tlz[i].lazerHitFlg = false;
		if (tlz[i].lazerExistFlg  && tlz[i].hitableFlg && GetPlayerPointer()->playerMode == BALL)//目を開けるアニメーション入れるならこれでいい
		{
			switch (tlz[i].side)
			{
			case LEFT_L:
				if (GetPlayerPointer()->posX < BOSS1_LAZER_EYE_WIDTH - 75)
				{
					damage = rand() % 3 + 1;
					bossHp -= damage;
					tlz[i].hp -= damage;
					tlz[i].lazerHitFlg = true;
				}
				else
					tlz[i].lazerHitFlg = false;
				break;
			case RIGHT_L:
				if (GetPlayerPointer()->posX > (WINDOW_X + 75) - BOSS1_LAZER_EYE_WIDTH)
				{
					damage = rand() % 3 + 1;
					bossHp -= damage;
					tlz[i].hp -= damage;
					tlz[i].lazerHitFlg = true;
				}
				else
					tlz[i].lazerHitFlg = false;
				break;
			default:
				break;
			}
		}
		if (tlz[i].lazerExistFlg&&tlz[i].hp <= 0)//追加したとこ
		{
			tlz[i].lazerExistFlg = false;
			tlz[i].isDeadFlg = true;
		}
	}
	//DamageAll(damage);
}

void UIAll()
{
	ui->DrawHp();
	ui->HpManager();
	PlayerHpView();
}

UI* GetUIPointer()
{
	return ui;
}

void EndUI()
{
	delete ui;
}

void ResetUI()
{
	ui->bossHp = BOSSHP_INIT;
}

Damage::Damage() :damageExistFlg(false)
{
	life = rand() % 15;
}

void Damage::DrawDamage()
{
	if (damageExistFlg)//&&レーザーが生きているとき)
	{
		SetFontSize(30);
		DrawFormatString(posX, posY, GetColor(255, 255, 255), "%d", this->damage);
		SetFontSize(50);
	}
}

void Damage::DamageManager(int damage)
{
	if(damageExistFlg)
		life--;
	if (life < 0)
		damageExistFlg = false;
	if (!damageExistFlg&&GetPlayerPointer()->playerMode == BALL)
	{
		life = rand()%15;
		this->posX = GetPlayerPointer()->posX + (rand() % 51 - 25);
		this->posY = GetPlayerPointer()->posY + (rand() % 31 - 15);
		this->damage = damage;
		damageExistFlg = true;
	}
}

void DamageAll(int damage)
{
	static int i = 0;
	if (GetPlayerPointer()->playerMode == BALL)
	{
		i++;
		dm[i].DrawDamage();
		dm[i].DamageManager(damage);
		if (i == (DAMAGE_MAX - 1))
			i = 0;
	}
	else
	{
		for (int j = 0; j < DAMAGE_MAX; j++)
		{
			dm[j].life = -1;
		}
	}
}

void PlayerHpView()
{
	SetFontSize(40);
	//DrawFormatString(PlayerInit()->posX, PlayerInit()->posY - 30, GetColor(36, 240, 226), "HP:%d", PlayerInit()->hp);
	SetFontSize(60);
}