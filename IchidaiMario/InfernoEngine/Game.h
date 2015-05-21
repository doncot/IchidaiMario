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

namespace Inferno
{

class Game: public Inferno::SimpleWindow
{
public:
	Game();
	virtual ~Game();
	virtual void Initialize();
	virtual void GameLoop();
	virtual void Draw();
	virtual void Exit();

	void SetClientSize(const int width, const int height);

protected:
	Graphics m_graphics;
	Input m_input;	

	bool m_IsInitialized;
	//Inferno::Timer m_globalTimer; //�Q�[���J�n���ɃX�^�[�g
	int m_elapsedFrame; //�Q�[���J�n����̌o�߃t���[��
	int m_frameCount; //�O��̃��[�v����̌o�߃t���[��

private:
	typedef SimpleWindow Base;
};

}