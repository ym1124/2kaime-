#pragma once
#include "Player.h"
class Fishes
{
public:
	float posX, posY;
	float moveX, moveY;
	static int particle_gh;
	int brightness;
	int colorR,colorG,colorB;
	bool used=false;
	Fishes();
	void ParticleMove();
	void ParticleDraw();
};

Fishes* ParticleInit(Player*);
void ParticleUpdata(Player*);