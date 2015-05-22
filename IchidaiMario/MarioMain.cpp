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
void MarioGame::Initialize()
{
	Base::Initialize();

	//�������珉��������
	teki.Initialize();
	teki.LoadTextureFromFile(m_graphics, "teki.bmp");


}

//�Q�[�����[�v�i�����͂����ɏ����Ă����j
void MarioGame::GameLoop()
{
	Base::GameLoop();

	//��������Q�[���{�̏���
	static int x = 200;
	static int y = 200;
	//���͗�
	if (m_input.IsKeyPressed('A'))
	{
		
		//x += 20;
		//y += 20;
		teki.RMove(x, y);
		//MessageBox(nullptr,"A��������܂���","Message",MB_OK);
	}

	//�E�ړ�
	if (m_input.IsKeyPressed(VK_RIGHT))
	{
		teki.RMove(5, 0);
	}

	//�G�𓮂���
	//teki.RMove(1, 1);

}

//�`��
void MarioGame::Draw()
{
	if (m_graphics.BeginScene() && Base::m_graphics.BeginSprite())
	{
		//�����ɕ`�揈��������
		teki.Draw(m_graphics);

	}
	m_graphics.EndSprite();
	m_graphics.EndScene();
}