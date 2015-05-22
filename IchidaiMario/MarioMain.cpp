#include"MarioMain.h"
#include<Game.h>
#include<Input.h>
#include<GameElements.h>

using namespace Inferno;

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
	Base::GameLoop();

	//ここからゲーム本体処理
	static int x = 200;
	static int y = 200;
	//入力例
	if (m_input.IsKeyPressed('A'))
	{
		
		//x += 20;
		//y += 20;
		teki.RMove(x, y);
		//MessageBox(nullptr,"Aが押されました","Message",MB_OK);
	}

	//右移動
	if (m_input.IsKeyPressed(VK_RIGHT))
	{
		teki.RMove(5, 0);
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