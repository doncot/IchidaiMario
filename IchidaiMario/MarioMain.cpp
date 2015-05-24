#include"MarioMain.h"
#include<Game.h>
#include<Input.h>
#include<GameElements.h>

using namespace Inferno;

#define GROUND_Y 500
#define JUMP_H 200

/* �ړ��\�̈� */
#define MOVE_LEFT 0
#define MOVE_TOP 0
#define MOVE_RIGHT 800
#define MOVE_BOTTOM 500


//�ʒu���擾
//TODO:�����ɃI�u�W�F�N�g��n��
static struct xy_coord_t getPos(Instant target){
	struct xy_coord_t pos;

	pos.x = target.GetPosition().x;
	pos.y = target.GetPosition().y;

	return pos;
}

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
	teki.AMove(0, GROUND_Y);

	background.Initialize();
	background.LoadTextureFromFile(m_graphics, "Resource\\background.png");
	background.SetPosofULCorner(0, 0);

}

//�Q�[�����[�v�i�����͂����ɏ����Ă����j
void MarioGame::GameLoop()
{
	Base::GameLoop();
	//��������Q�[���{�̏���

	int jump_accel = 1;
	int jump_speed = -20;
	static int jump_state = false;
	static int VY, VX;
	double speed = 2.0f;
	//struct xy_coord_t current_pos;
	int current_x;
	int current_y;

	//�ʒu�̎擾
	//current_pos = getPos(teki);
	current_x = teki.GetPosition().x;
	current_y = teki.GetPosition().y;

	//�E�ړ�
	if (m_input.IsKeyDown(VK_RIGHT) || m_input.IsButtonDown(PadButton::Right))
	{
		current_x += speed;
	}
	//���ړ�
	if (m_input.IsKeyDown(VK_LEFT) || m_input.IsButtonDown(PadButton::Left))
	{
		current_x -= speed;
	}
	

	//�W�����v�L�[�̎擾
	if (m_input.IsKeyPressed(VK_UP) || m_input.IsButtonDown(PadButton::Up) )
	{
		jump_state = true;
		VY = jump_speed;
	}

	//�W�����v��Ԃ̏���
	else if (jump_state == true){

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


	teki.AMove(current_x, current_y);
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