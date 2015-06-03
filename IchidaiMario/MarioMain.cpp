#include"MarioMain.h"
#include<Inferno.h>
#include"Player.h"

using namespace Inferno;

#define GROUND_Y 500


//位置を取得
//TODO:引数にオブジェクトを渡す
static struct xy_coord_t getPos(Instant target){
	struct xy_coord_t pos;

	pos.x = target.GetPosition().x;
	pos.y = target.GetPosition().y;

	return pos;
}

namespace
{
	//敵キャラなどの変数はここに書け
	Texture playerTex;
	Idea player_;
	Player player;

	Instant background;

}

//初期化
void MarioGame::Initialize()
{
	Base::Initialize();
	SetTitleText("市大マリオ"); //ウィンドウタイトルに表示する文字列
	SetClientSize(800, 600);

	//ここから初期化処理
	playerTex.LoadImageFile(m_graphics, "Resource\\player.bmp");
	player_.SetTexture(playerTex);
	player.SetIdea(player_);
	player.AMove(0, GROUND_Y);
	player.SetAttribute(GEAttribute::Visible, true);

	//enemy[0].SetIdea(enemy_);
	//enemy2.SetIdea(enemy_);
	//enemy3.SetIdea(enemy_);

	background.Initialize();
	background.LoadTextureFromFile(m_graphics, "Resource\\background.png");
	background.SetPosofULCorner(0, 0);

}

//ゲームループ（処理はここに書いていく）
void MarioGame::GameLoop()
{
	Base::GameLoop();
	//ここからゲーム本体処理
	player.Move(m_input);


}

//描画
void MarioGame::Draw()
{
	if (BeginDrawing() == true)
	{
		//ここに描画処理を書く（上に書いた方から順番に描画される）
		background.Draw(m_graphics);

		player.Draw(m_graphics);

	}
	EndDrawing();
}