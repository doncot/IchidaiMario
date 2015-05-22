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
	SetTitleText("�s��}���I"); //�E�B���h�E�^�C�g���ɕ\�����镶����

	//�������珉��������
	teki.Initialize();
	teki.LoadTextureFromFile(m_graphics, "Resource\\teki.bmp");
	teki.AMove(400, 400);

}

//�Q�[�����[�v�i�����͂����ɏ����Ă����j
void MarioGame::GameLoop()
{
	Base::GameLoop();

	//��������Q�[���{�̏���

	//���͗�
	if (m_input.IsKeyPressed('A'))
	{
		MessageBox(nullptr, "A��������܂���", "Message", MB_OK);
	}

	//�G�𓮂���
	if (m_input.IsButtonDown(PadButton::Left))
	{
		teki.RMove(-7, 0);
	}
	else if (m_input.IsButtonDown(PadButton::Right))
	{
		teki.RMove(7, 0);
	}
	
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