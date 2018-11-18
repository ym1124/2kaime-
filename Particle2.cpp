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
			pr[i].posX = pl->posX+(PLAYER_WIDTH/2)+rand()%101-50;//�p�[�e�B�N�������ʒu
			pr[i].posY = pl->posY + (PLAYER_HEIGHT / 2)+ rand() % 101 - 50;
			pr[i].moveX = rand() % 5 - 2; //�p�[�e�B�N���ړ���
			pr[i].moveY = rand() % 5 - 2;
			pr[i].used = true;//�p�[�e�B�N������������Ă��邩�ǂ���
			pr[i].brightness = rand() % PARTICLE_LIFE;//�p�[�e�B�N���̐�����
			//pr[i].colorR = rand() % 156+100;//�p�[�e�B�N���̐F
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
		//�p�[�e�B�N���\�����J�E���g
		pr[i].brightness--;
		//�p�[�e�B�N�����x����
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