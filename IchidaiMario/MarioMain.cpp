#include"MarioMain.h"
#include<Game.h>
#include<Input.h>
#include<GameElements.h>

using namespace Inferno;

#define GROUND_Y 500
#define JUMP_H 200

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


}

//ゲームループ（処理はここに書いていく）
void MarioGame::GameLoop()
{
	
	int jump_start_y, jump_current_y;

	Base::GameLoop();

	//ここからゲーム本体処理

	//入力例
	//if (m_input.IsKeyPressed('A'))
	//{
		
		//teki.RMove(x, y);
		//MessageBox(nullptr,"Aが押されました","Message",MB_OK);
	//}

	//右移動
	if (m_input.IsKeyPressed(VK_RIGHT))
	{
		teki.RMove(5, 0);
	}
	//垂直ジャンプ
	else if (m_input.IsKeyPressed(VK_UP))
	{
		jump_start_y = jump_current_y = teki.GetPosition().y;
		while ((jump_start_y - jump_current_y) <= JUMP_H){
			teki.RMove(0, -5);
			jump_current_y = teki.GetPosition().y;
			Draw();
		}
		while (jump_current_y <= jump_start_y){
			teki.RMove(0, 5);
			jump_current_y = teki.GetPosition().y;
			Draw();
		}
	}

	//敵を動かす
	//teki.RMove(1, 1);

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