#pragma once
#include "DxLib.h"
#include "define.h"

enum LAZERSIDE{LEFT_L,RIGHT_L,UP_L};

class Lazer
{
public:
	int posX,posY;
	int hp;
	float thickness;
	int brightness;
	int side;
	static int boss1Attack_gh, boss1Lazer_gh,lazerSound,enemyHitSound;
	int colorR, colorG, colorB;
	int lazerEyeAnimCnt, lazerEyeAnimX,lazerHitAnimCnt,lazerHitAnimX;
	int firingDerayCnt;//���[�U�[�������Ȃ�܂ł̃f�B���C
	int lazerTime;//���[�U�[�̈�A�̎��Ԃ̒���
	bool lazerHitFlg;//���[�U�[�̖ڋʂ̓����蔻��
	bool isDeadFlg;//�_���[�W�Ŏ��񂾂��H
	bool hitableFlg;//�v���C���[�̓����蔻����t���O
	bool riseFlg;//�����ς���Ƃ��̃t���O
	bool lazerExistFlg;//���݃t���O�����̃t���O�̓Q�[���J�n���ɑS��true�ɂȂ��Ă邩��J�n�̃t���O�Ɏg���̂͂悭�Ȃ�
	bool setLazerFlg;
	bool lazerSoundFlg;
	static bool lazerLoadFlg;
	Lazer();
	void DrawLazer(int);
	void MoveLazer(int);
	void LazerSway();
};

void CreateLazer();
void LazerInit();
void LazerUpdata();
void SetLazer(int i, int cnt,int posXorY,int type);
void ResetLazer();
void EndLazer();
Lazer* GetLazerPointer();