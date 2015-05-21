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

class Game: public Inferno::SimpleWindow
{
public:
	Game();
	virtual ~Game();
	virtual bool Initialize();
	virtual bool GameLoop();
	virtual void Exit();

	void SetClientSize(const int width, const int height);

protected:
	Inferno::Graphics m_graphics;
	Inferno::Input m_input;	

	bool m_IsInitialized;
	//Inferno::Timer m_globalTimer; //ゲーム開始時にスタート
	int m_elapsedFrame; //ゲーム開始からの経過フレーム
	int m_frameCount; //前回のループからの経過フレーム

private:
	typedef Inferno::SimpleWindow Base;
};