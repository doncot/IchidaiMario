#include"MarioMain.h"
#include<Game.h>
#include<Input.h>
#include<GameElements.h>

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

	//���͗�
	if (m_input.IsKeyPressed('A'))
	{
		MessageBox(nullptr,"A��������܂���","Message",MB_OK);
	}

	//�G�𓮂���
	teki.AMove(200, 200);

}

//�`��
void MarioGame::Draw()
{
	if (BeginDrawing() == true)
	{
		//�����ɕ`�揈��������
		teki.Draw(m_graphics);

	}
	EndDrawing();
}