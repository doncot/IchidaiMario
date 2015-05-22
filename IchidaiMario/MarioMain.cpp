#include"MarioMain.h"
#include<Game.h>
#include<Input.h>
#include<GameElements.h>

namespace
{
	//�G�L�����Ȃǂ̕ϐ��͂����ɏ�����
	Instant teki;
	Instant background;

}

//������
void MarioGame::Initialize()
{
	Base::Initialize();
	SetTitleText("�s��}���I"); //�E�B���h�E�^�C�g���ɕ\�����镶����
	SetClientSize(800, 600);

	//�������珉��������
	teki.Initialize();
	teki.LoadTextureFromFile(m_graphics, "Resource\\teki.bmp");
	teki.AMove(400, 400);

	background.Initialize();
	background.LoadTextureFromFile(m_graphics, "Resource\\background.png");
	background.SetPosofULCorner(0, 0);

}

//�Q�[�����[�v�i�����͂����ɏ����Ă����j
void MarioGame::GameLoop()
{
	Base::GameLoop();

	//��������Q�[���{�̏���

	//���͗�
	if (m_input.IsKeyPressed('A') || m_input.IsButtonDown(PadButton::Button2) )
	{
		MessageBox(nullptr, "A��������܂���", "Message", MB_OK);
	}
	if ( m_input.IsButtonDown(PadButton::Button7) )
	{
		MessageBox(nullptr, "L��������܂���", "Message", MB_OK);
	}
	if (m_input.IsButtonDown(PadButton::Button6))
	{
		MessageBox(nullptr, "R2��������܂���", "Message", MB_OK);
	}

	//�G�𓮂���
	if (m_input.IsButtonDown(PadButton::Left) || m_input.IsKeyDown(VK_LEFT) )
	{
		teki.RMove(-3, 0);
	}
	else if (m_input.IsButtonDown(PadButton::Right) || m_input.IsKeyDown(VK_RIGHT) )
	{
		teki.RMove(3, 0);
	}
	if (m_input.IsButtonDown(PadButton::Up) || m_input.IsKeyDown(VK_UP))
	{
		teki.RMove(0, -3);
	}
	else if (m_input.IsButtonDown(PadButton::Down) || m_input.IsKeyDown(VK_DOWN))
	{
		teki.RMove(0, 3);
	}
}


//�`��
void MarioGame::Draw()
{
	if (BeginDrawing() == true)
	{
		//�����ɕ`�揈���������i��ɏ����������珇�Ԃɕ`�悳���j
		background.Draw(m_graphics);

		teki.Draw(m_graphics);

	}
	EndDrawing();
}