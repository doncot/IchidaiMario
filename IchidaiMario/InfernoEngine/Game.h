/*
Game.h
ゲーム本体
これは基底で各ゲームごとに派生させる
*/
#pragma once
#include<SimpleWindow.h>
#include"Graphics.h"
#include<Input.h>
//#include"Timer.h"

namespace Inferno
{

class Game: public Inferno::SimpleWindow
{
public:
	Game();
	virtual ~Game();
	virtual void Initialize();
	virtual void GameLoop();
	virtual void Draw() const;
	virtual void Exit();

	void SetClientSize(const int width, const int height);

	bool BeginDrawing() const;
	void EndDrawing() const;

protected:
	Graphics m_graphics;
	Input m_input;	

	bool m_IsInitialized;
	//Inferno::Timer m_globalTimer; //ゲーム開始時にスタート
	int m_elapsedFrame; //ゲーム開始からの経過フレーム
	int m_frameCount; //前回のループからの経過フレーム

private:
	typedef SimpleWindow Base;
};

}