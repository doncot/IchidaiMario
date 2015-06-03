#include"Player.h"

using namespace Inferno;

#define GROUND_Y 500
#define JUMP_H 200

/* �ړ��\�̈� */
#define MOVE_LEFT 0
#define MOVE_TOP 0
#define MOVE_RIGHT 800
#define MOVE_BOTTOM 500

void Player::Move(Input& input)
{



	//�E�ړ�
	if (input.IsKeyDown(VK_RIGHT) || input.IsButtonDown(PadButton::Right))
	{
		m_pos.x += WalkSpeed;
	}
	//���ړ�
	if (input.IsKeyDown(VK_LEFT) || input.IsButtonDown(PadButton::Left))
	{
		m_pos.x -= WalkSpeed;
	}


	//�W�����v�L�[�̎擾
	if (input.IsKeyPressed(VK_UP) || input.IsButtonPressed(PadButton::Button3))
	{
		m_jumpState = true;
		m_vel.y = JumpSpeed;
	}

	//�W�����v��Ԃ̏���
	else if (m_jumpState == true){

		//Y�������̑��x�ɉ����x��^����
		m_vel.y += JumpAccel;
		//Y���W�̍X�V
		m_pos.y += m_vel.y;

		//���n�̔���
		if (m_vel.y > 0 && m_pos.y > GROUND_Y){
			m_jumpState = false;
			m_pos.y = GROUND_Y;
		}
	}

	//�c�����̈ړ��͈͂𐧌�����
	if (m_pos.y <= MOVE_TOP){
		m_pos.y = MOVE_TOP;
	}
	else if (m_pos.y >= MOVE_BOTTOM){
		m_pos.y = MOVE_BOTTOM;
	}

	//�������̈ړ��͈͂𐧌�����
	if (m_pos.x <= MOVE_LEFT){
		m_pos.x = MOVE_LEFT;
	}
	else if (m_pos.x >= MOVE_RIGHT){
		m_pos.x = MOVE_RIGHT;
	}


	//AMove(current_x, m_pos.y);
}