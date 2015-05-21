/*
MarioMain.h
マリオ本体のヘダー
*/
#pragma once
#include<Game.h>
#include<Input.h>


class MarioGame : public Inferno::Game
{
public:
	bool Initialize();
	bool GameLoop();

private:
	//親を呼べるように
	typedef Game Base;
};