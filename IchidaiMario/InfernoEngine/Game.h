/*
Game.h
�Q�[���{��
����͊��Ŋe�Q�[�����Ƃɔh��������
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
	void SetClientSize(const int width, const int height);

	virtual bool GameLoop();
	virtual void Exit();

protected:
	Inferno::Graphics m_graphics;
	Inferno::Input m_input;	

	bool m_IsInitialized;
	//Inferno::Timer m_globalTimer; //�Q�[���J�n���ɃX�^�[�g
	int m_elapsedFrame; //�Q�[���J�n����̌o�߃t���[��
	int m_frameCount; //�O��̃��[�v����̌o�߃t���[��

private:
	typedef Inferno::SimpleWindow Base;
};