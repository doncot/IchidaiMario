#include"MarioMain.h"
#include<Game.h>
#include<Input.h>
#include<GameElements.h>

using namespace Inferno;

namespace
{
	//�G�L�����Ȃǂ̕ϐ��͂����ɏ�����
	Instant teki;

}

//������
bool MarioGame::Initialize()
{
	Base::Initialize();

	//�������珉��������
	teki.Initialize();
	teki.LoadTextureFromFile(m_graphics, "teki.bmp");
		

	return true;
}

//�Q�[�����[�v�i�����͂����ɏ����Ă����j
bool MarioGame::GameLoop()
{
	Base::GameLoop();

	//��������Q�[���{�̏���

	//���͗�
	if (m_input.IsKeyPressed('A'))
	{
		MessageBox(nullptr,"A��������܂���","Message",MB_OK);
	}

	

	//�G�𓮂���


	m_graphics.BeginScene(); m_graphics.BeginSprite();

	//�`��**************************
	teki.Draw(m_graphics);

	m_graphics.EndSprite(); m_graphics.EndScene();

	return true;
}