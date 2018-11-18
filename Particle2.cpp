#include "Particle.h"
#include "DxLib.h"
#include "define.h"

Fishes pr[PARTICLE_MAX];

Fishes::Fishes()
{
}

void Fishes::ParticleMove()
{
	posX += moveX;
	posY += moveY;
}

void Fishes::ParticleDraw()
{
	SetDrawBright(colorR, colorG, colorB);
	DrawGraph(posX, posY, particle_gh, true);
	SetDrawBright(255, 255, 255);
}

Fishes* ParticleInit(Player *pl)
{
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (pr[i].used == false)
		{
			pr[i].posX = pl->posX+(PLAYER_WIDTH/2)+rand()%101-50;//パーティクル生成位置
			pr[i].posY = pl->posY + (PLAYER_HEIGHT / 2)+ rand() % 101 - 50;
			pr[i].moveX = rand() % 5 - 2; //パーティクル移動力
			pr[i].moveY = rand() % 5 - 2;
			pr[i].used = true;//パーティクルが生成されているかどうか
			pr[i].brightness = rand() % PARTICLE_LIFE;//パーティクルの生命力
			//pr[i].colorR = rand() % 156+100;//パーティクルの色
			//pr[i].colorG = rand() % 156+100;
			//pr[i].colorB = rand() % 156+100;
			pr[i].colorR = 115;
			pr[i].colorG = 226;
			pr[i].colorB = 214;
		}
	}
	return pr;
}

void ParticleUpdata(Player *pl)
{
	Fishes *pr = ParticleInit(pl);
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		pr[i].ParticleMove();
		pr[i].ParticleDraw();
		//パーティクル表示中カウント
		pr[i].brightness--;
		//パーティクル速度減衰
		if (pr[i].moveX > 0)
			pr[i].moveX -= 0.1;
		if (pr[i].moveY > 0)
			pr[i].moveY -= 0.1;
		if (pr[i].moveX < 0)
			pr[i].moveX += 0.1;
		if (pr[i].moveY < 0)
			pr[i].moveY += 0.1;
		if (pr[i].brightness <= 0)
		{
			pr[i].used = false;
		}
	}
}