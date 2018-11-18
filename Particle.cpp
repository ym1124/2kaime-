#include "Particle.h"
#include "DxLib.h"
#include "define.h"

int derayCounter = 0;
int derayTimer = 0;
bool particleExistFlg=false;
Particle *pr;

Particle::Particle()
{}

void Particle::ParticleMove()
{
	posX += moveX;
	posY += moveY;
}

void Particle::ParticleDraw()
{
	if(brightness>0)
	DrawGraph(posX, posY, particle_gh, true);
}

Particle* ParticleInit(Player *pl)
{
	if (particleExistFlg == false)
	{
		pr = new Particle[PARTICLE_MAX];
		particleExistFlg = true;
	}
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (derayCounter == i)
		{
			if (pr[i].used == false)
			{
				pr[i].posX = pl->posX;
				pr[i].posY = pl->posY;
				pr[i].moveX = rand() % 3 - 1;
				pr[i].moveY = rand() % 3 - 1;
				pr[i].used = true;
				pr[i].brightness = rand() % 100;
				pr[i].colorR = rand() % 100;
				pr[i].colorG = rand() % 100;
				pr[i].colorB = rand() % 100;
				pr[i].particle_gh = LoadGraph("Data/Image/effect3.png", true);
			}
		}
	}
	return pr;
}

void ParticleUpdata(Player *pl)
{
	Particle *pr = ParticleInit(pl);
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		pr[i].ParticleMove();
		pr[i].ParticleDraw();
		//�p�[�e�B�N���\���܂ł̃J�E���g
		derayTimer++;
		derayCounter = derayTimer / 100;
		//�p�[�e�B�N���\�����J�E���g
		pr[i].brightness--;
		//�p�[�e�B�N�����x����
		if(pr[i].moveX>0)
			pr[i].moveX -= 0.1;
		if (pr[i].moveY>0)
			pr[i].moveY -= 0.1;
		if (pr[i].moveX<0)
			pr[i].moveX += 0.1;
		if (pr[i].moveY<0)
			pr[i].moveY += 0.1;
		if (pr[0].brightness <= 0)//��荇�����œK����i�ŁA��ŕς��ꂽ��ς���
		{
			delete[] pr;
			particleExistFlg = false;
			derayTimer = 0;
			pr = nullptr;
			break;
		}
	}
}