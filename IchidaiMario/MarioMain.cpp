#include"MarioMain.h"
#include<Game.h>
#include<Input.h>
#include<GameElements.h>

using namespace Inferno;

#define GROUND_Y 500
#define JUMP_H 200
#define TRUE 1
#define FALSE 0

/* 移動可能領域 */
#define MOVE_LEFT 0
#define MOVE_TOP 0
#define MOVE_RIGHT 800
#define MOVE_BOTTOM 500


//位置を取得
//TODO:引数にオブジェクトを渡す
static struct xy_coord_t getPos(){
	struct xy_coord_t pos;

	pos.x = teki.GetPosition().x;
	pos.y = teki.GetPosition().y;

	return pos;
}

namespace
{
	//敵キャラなどの変数はここに書ける
	Instant teki;
	Instant background;

}

//初期化
void MarioGame::Initialize()
{
	Base::Initialize();
	SetTitleText("市大マリオ"); //ウィンドウタイトルに表示する文字列
	SetClientSize(800, 600);

	//ここから初期化処理
	teki.Initialize();
	teki.LoadTextureFromFile(m_graphics, "Resource\\teki.bmp");
	teki.AMove(0, GROUND_Y);

	background.Initialize();
	background.LoadTextureFromFile(m_graphics, "Resource\\background.png");
	background.SetPosofULCorner(0, 0);

}

//ゲームループ（処理はここに書いていく）
void MarioGame::GameLoop()
{

	int jump_accel = 1;
	int jump_speed = -20;
	static int jump_state = FALSE;

	static int VY, VX;
	double speed = 2.0f;
	struct xy_coord_t current_pos;

	Base::GameLoop();

	//ここからゲーム本体処理

	//位置の取得
	current_pos = getPos();

	//右移動
	if (m_input.IsKeyDown(VK_RIGHT) || m_input.IsButtonDown(PadButton::Right))
	{
		current_pos.x += speed;
	}
	//左移動
	if (m_input.IsKeyDown(VK_LEFT) || m_input.IsButtonDown(PadButton::Left))
	{
		current_pos.x -= speed;
	}
	

	//ジャンプキーの取得
	if (m_input.IsKeyPressed(VK_UP) || m_input.IsButtonDown(PadButton::Up) )
	{
		jump_state = TRUE;
		VY = jump_speed;
	}

	//ジャンプ状態の処理
	else if (jump_state == TRUE){

		//Y軸方向の速度に加速度を与える
		VY += jump_accel;
		//Y座標の更新
		current_pos.y += VY;

		//着地の判定
		if (VY > 0 && current_pos.y > GROUND_Y){
			jump_state = FALSE;
			current_pos.y = GROUND_Y;
		}
	}


	teki.AMove(current_pos.x, current_pos.y);
}

//描画
void MarioGame::Draw()
{
	if (BeginDrawing() == true)
	{
		//ここに描画処理を書く（上に書いた方から順番に描画される）
		background.Draw(m_graphics);

		teki.Draw(m_graphics);

	}
	EndDrawing();
}