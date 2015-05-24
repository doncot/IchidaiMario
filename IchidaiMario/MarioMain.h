/*
MarioMain.h
マリオ本体のヘダー
*/
#pragma once
#include<Inferno.h>

using namespace Inferno;


struct xy_coord_t{
	double x;
	double y;
};


class MarioGame final : public Game
{
public:
	void Initialize();
	void GameLoop();
	void Draw();

private:
	//親を呼べるように
	typedef Game Base;
};