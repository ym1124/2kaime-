#pragma once
//********ゲームシステム関連*************//
#define WINDOW_X 1600
#define WINDOW_Y 900

//**********背景関連****************//
#define CLOUD_MAX 30
#define AURA_MAX 1000
#define VIBRATION_VALUE 29//外枠を引っ張る強さと速さ
#define GROUND_HEIGHT 100
#define CLOUD_WIDTH 500
#define CLOUD_HEIGHT 507
#define DARK_CNT 50

//********プレイヤー関連*************//
#define PLAYER_WIDTH 150
#define PLAYER_HEIGHT 130
#define PLAYER_INVINCIBLE_WIDTH 127
#define PLAYER_INVINCIBLE_HEIGHT 127
#define PLAYER_LEG_HEIGHT 40
#define PLAYER_HP 500;
#define PLAYERPOS_X_INIT WINDOW_X/3
#define PLAYERPOS_Y_INIT (WINDOW_Y-PLAYER_HEIGHT-GROUND_HEIGHT)
#define PLAYER_SPEED_X 7
#define PLAYER_SPEED_Y 7
#define PLAYER_ANIM_MAX 9
#define JUMP_POWER 25
#define PLAYER_PARTS_MAX 18
#define PLAYER_PARTS_WIDTH 50
#define PLAYER_PARTS_HEIGHT 50
#define EXPLOSION_DERAY_CNT 3000;
#define EXPLOSION_WIDTH 256
#define EXPLOSION_HEIGHT 256
#define KNOCKBACK_JUMP_POWER 8

//*********ボールモード*************//
#define PLAYER_BALL_WIDTH 100
#define PLAYER_BALL_HEIGHT 100
#define PLAYER_BALL_SPEED_X 15
#define PLAYER_BALL_SPEED_Y 15
#define BALL_TIME 100

//*********パーティクル関連***********//
#define PARTICLE_MAX 100
#define PARTICLE_LIFE 50

//*********レーザー関連**************//
#define LAZER_MAX 32//レーザーの最大本数
#define LAZER_HP 125
#define LAZER_THICKNESS_MAX 150//レーザーの太さの最大値
#define LAZER_BRIGHTNESS_SUBTRACTION 1 //レーザーの透明度が減算する速度
#define LAZER_RISE_SPEED 3//レーザーが太くなる早さ
#define LAZER_BRIGHTNESS 255//レーザーの生命力
#define LAZER_THICKNESS_INIT 1//レーザー発射前の線の太さ
#define LAZER_FIRING_CNT 30//線が出てから発射までの時間
#define LAZER_TIME 84//レーザーを描画している時間
#define BOSS1_LAZER_EYE_WIDTH 390
#define BOSS1_LAZER_EYE_HEIGHT 390
#define LAZER_EYE_ANIM_MAX 30//レーザーのアニメーション枚数
#define LAZER_EYE_MARGIN 190


//**********ブレード関連****************//
#define BLADE_MAX 9
#define BLADE_WIDTH 330
#define BLADE_HEIGHT 330
#define BLADE_Y_INIT WINDOW_Y-250
#define BLADE_SPEED_X 8
#define BLADE_SPEED_Y 8
#define BLADE_TIME (WINDOW_X+BLADE_HEIGHT)/BLADE_SPEED_X
#define BLADE_ANIM_MAX 7


//*********ベノム関連********************//
#define VENOM_MAX 30
#define VENOM_WIDTH 300
#define VENOM_HEIGHT 300
#define VENOM_Y_INIT WINDOW_Y-250
#define VENOM_JUMP_POWER 27
#define VENOM_SPEED_X 6

//**********フォールダウン関連************//
#define FALLDOWN_BOSS_WIDTH 1600
#define FALLDOWN_BOSS_HEIGHT 1600
#define FALLDOWN_BOSS_SPEED 5
#define EYE_POSX_MARGIN 490
#define EYE_POSY_MARGIN 740
#define EYE_WIDTH 630
#define EYE_HEIGHT 550

//*********回転関連**********************//
#define ROTATION_MAX 10
#define ROTATION_WIDTH 220
#define ROTATION_HEIGHT 220
#define ROTATION_LIFE 1000
#define ROTAITON_R_INIT 100

//************ボス関連*******************//
#define BOSSHP_INIT 1 //1000
#define BOSS2HP_INIT 1000 //1000
#define BOSS1_HEIGHT 1600
#define BOSS1_WEIGHT 1600
#define BOSS1_X_INIT 0
#define BOSS1_Y_INIT -200
#define BOSS1_SWAY_UP_SPEED 0.3
#define BOSS1_SWAY_DOWN_SPEED 0.3
#define BOSS1_SPEED_Y 5
#define SHADOW_CNT 200
#define DOWN_CNT 1000

//**********UI関連***************//
#define BOSSHP_X_INIT 10
#define BOSSHP_Y_INIT 10
#define BOSSHP_GAGE_X 660
#define BOSSHP_GAGE_Y 160
#define DAMAGE_MAX 10