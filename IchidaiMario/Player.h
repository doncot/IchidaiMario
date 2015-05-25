/*
Player.h
�v���C���[�N���X
*/
#pragma once
#include<Inferno.h>

using namespace Inferno;

class Player : public Substance
{
private:
	typedef Substance Base;
	//�萔
	const int JumpAccel = 1;
	const int JumpSpeed = -20;
	const double WalkSpeed = 2.0f;

public:
	Player() : Base(){}
	Player(const Idea& idea) : Base(idea){}
	virtual ~Player(){}

	void Move(Input& input);
	
private:
	bool m_jumpState = false;
	//���@�̌��݂̑���
	Vec2<int> m_vel;


};