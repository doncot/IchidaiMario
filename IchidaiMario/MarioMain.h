/*
MarioMain.h
�}���I�{�̂̃w�_�[
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
	//�e���Ăׂ�悤��
	typedef Game Base;
};