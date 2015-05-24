#include"MarioMain.h"
#include<Game.h>
#include<Input.h>
#include<GameElements.h>

using namespace Inferno;

#define GROUND_Y 500
#define JUMP_H 200
#define TRUE 1
#define FALSE 0


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
	teki.LoadTextureFromFile(m_graphics, "teki.bmp");
	teki.AMove(0, GROUND_Y);

	background.Initialize();
	background.LoadTextureFromFile(m_graphics, "Resource\\background.png");
	background.SetPosofULCorner(0, 0);

}

//�Q�[�����[�v�i�����͂����ɏ����Ă����j
void MarioGame::GameLoop()
{
	
	int jump_start_y, jump_current_y;
	int jump_accel = 1;
	int jump_speed = -20;
	static int jump_state = FALSE;
	static int VY, VX;
	int current_y, current_x;
	double speed = 2.0f;

	Base::GameLoop();

	//��������Q�[���{�̏���

	//�ʒu�̎擾
	current_x = teki.GetPosition().x;
	current_y = teki.GetPosition().y;

	//�E�ړ�
	if (m_input.IsKeyPressed(VK_RIGHT))
	{
		current_x += speed;
	}

	//�W�����v�L�[�̎擾
	if (m_input.IsKeyPressed(VK_UP))
	{
		jump_state = TRUE;
		VY = jump_speed;
	}

	//�W�����v��Ԃ̏���
	else if (jump_state == TRUE){

		//Y�������̑��x�ɉ����x��^����
		VY += jump_accel;
		//Y���W�̍X�V
		current_y += VY;

		//���n�̔���
		if (VY > 0 && current_y > GROUND_Y){
			jump_state = FALSE;
			current_y = GROUND_Y;
		}
	}
	if ( m_input.IsButtonDown(PadButton::Button7) )
	{
		MessageBox(nullptr, "L��������܂���", "Message", MB_OK);
	}
	if (m_input.IsButtonDown(PadButton::Button6))
	{
		MessageBox(nullptr, "R2��������܂���", "Message", MB_OK);
	}

	teki.AMove(current_x, current_y);


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