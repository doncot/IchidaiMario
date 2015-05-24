/*
MarioMain.h
�}���I�{�̂̃w�_�[
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
	//�e���Ăׂ�悤��
	typedef Game Base;
};