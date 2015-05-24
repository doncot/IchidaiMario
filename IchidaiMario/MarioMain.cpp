#include"MarioMain.h"
#include<Game.h>
#include<Input.h>
#include<GameElements.h>

using namespace Inferno;

#define GROUND_Y 500
#define JUMP_H 200
#define TRUE 1
#define FALSE 0


namespace
{
	//敵キャラなどの変数はここに書ける
	Instant teki;

}

//初期化
void MarioGame::Initialize()
{
	Base::Initialize();

	//ここから初期化処理
	teki.Initialize();
	teki.LoadTextureFromFile(m_graphics, "teki.bmp");
	teki.AMove(0, GROUND_Y);


}

//ゲームループ（処理はここに書いていく）
void MarioGame::GameLoop()
{
	
	int jump_start_y, jump_current_y;
	int jump_accel = 1;
	int jump_speed = -20;
	static int jump_state = FALSE;
	static int VY, VX;
	int current_y, current_x;
	double speed = 2.0f;

	Base::GameLoop();

	//ここからゲーム本体処理

	//位置の取得
	current_x = teki.GetPosition().x;
	current_y = teki.GetPosition().y;

	//右移動
	if (m_input.IsKeyPressed(VK_RIGHT))
	{
		current_x += speed;
	}

	//ジャンプキーの取得
	if (m_input.IsKeyPressed(VK_UP))
	{
		jump_state = TRUE;
		VY = jump_speed;
	}

	//ジャンプ状態の処理
	else if (jump_state == TRUE){

		//Y軸方向の速度に加速度を与える
		VY += jump_accel;
		//Y座標の更新
		current_y += VY;

		//着地の判定
		if (VY > 0 && current_y > GROUND_Y){
			jump_state = FALSE;
			current_y = GROUND_Y;
		}
	}

	teki.AMove(current_x, current_y);

}

//描画
void MarioGame::Draw()
{
	if (m_graphics.BeginScene() && Base::m_graphics.BeginSprite())
	{
		//ここに描画処理を書く
		teki.Draw(m_graphics);

	}
	m_graphics.EndSprite();
	m_graphics.EndScene();
}