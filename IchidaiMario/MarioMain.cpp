#include"MarioMain.h"
#include<Game.h>
#include<Input.h>
#include<GameElements.h>

using namespace Inferno;

#define GROUND_Y 500
#define JUMP_H 200

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
	
	int jump_start_y, jump_current_y;

	Base::GameLoop();

	//��������Q�[���{�̏���

	//���͗�
	//if (m_input.IsKeyPressed('A'))
	//{
		
		//teki.RMove(x, y);
		//MessageBox(nullptr,"A��������܂���","Message",MB_OK);
	//}

	//�E�ړ�
	if (m_input.IsKeyPressed(VK_RIGHT))
	{
		teki.RMove(5, 0);
	}
	//�����W�����v
	else if (m_input.IsKeyPressed(VK_UP))
	{
		jump_start_y = jump_current_y = teki.GetPosition().y;
		while ((jump_start_y - jump_current_y) <= JUMP_H){
			teki.RMove(0, -5);
			jump_current_y = teki.GetPosition().y;
			Draw();
		}
		while (jump_current_y <= jump_start_y){
			teki.RMove(0, 5);
			jump_current_y = teki.GetPosition().y;
			Draw();
		}
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