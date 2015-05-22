#include"MarioMain.h"
#include<Game.h>
#include<Input.h>
#include<GameElements.h>

namespace
{
	//敵キャラなどの変数はここに書ける
	Instant teki;

}

//初期化
void MarioGame::Initialize()
{
	Base::Initialize();
	SetTitleText("市大マリオ"); //ウィンドウタイトルに表示する文字列

	//ここから初期化処理
	teki.Initialize();
	teki.LoadTextureFromFile(m_graphics, "Resource\\teki.bmp");
	teki.AMove(400, 400);

}

//ゲームループ（処理はここに書いていく）
void MarioGame::GameLoop()
{
	Base::GameLoop();

	//ここからゲーム本体処理

	//入力例
	if (m_input.IsKeyPressed('A') || m_input.IsButtonDown(PadButton::Button2) )
	{
		MessageBox(nullptr, "Aが押されました", "Message", MB_OK);
	}
	if ( m_input.IsButtonDown(PadButton::Button7) )
	{
		MessageBox(nullptr, "Lが押されました", "Message", MB_OK);
	}
	if (m_input.IsButtonDown(PadButton::Button6))
	{
		MessageBox(nullptr, "R2が押されました", "Message", MB_OK);
	}

	//敵を動かす
	if (m_input.IsButtonDown(PadButton::Left) || m_input.IsKeyDown(VK_LEFT) )
	{
		teki.RMove(-3, 0);
	}
	else if (m_input.IsButtonDown(PadButton::Right) || m_input.IsKeyDown(VK_RIGHT) )
	{
		teki.RMove(3, 0);
	}
	if (m_input.IsButtonDown(PadButton::Up) || m_input.IsKeyDown(VK_UP))
	{
		teki.RMove(0, -3);
	}
	else if (m_input.IsButtonDown(PadButton::Down) || m_input.IsKeyDown(VK_DOWN))
	{
		teki.RMove(0, 3);
	}
}


//描画
void MarioGame::Draw()
{
	if (BeginDrawing() == true)
	{
		//ここに描画処理を書く
		teki.Draw(m_graphics);

	}
	EndDrawing();
}