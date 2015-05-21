/*
MarioMain.h
マリオ本体のヘダー
*/
#pragma once
#include<Game.h>
#include<Input.h>


class MarioGame final : public Inferno::Game
{
public:
	void Initialize();
	void GameLoop();
	void Draw();

private:
	//親を呼べるように
	typedef Game Base;
};