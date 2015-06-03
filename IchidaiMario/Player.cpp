#include"Player.h"

using namespace Inferno;

#define GROUND_Y 500
#define JUMP_H 200

/* 移動可能領域 */
#define MOVE_LEFT 0
#define MOVE_TOP 0
#define MOVE_RIGHT 800
#define MOVE_BOTTOM 500

void Player::Move(Input& input)
{



	//右移動
	if (input.IsKeyDown(VK_RIGHT) || input.IsButtonDown(PadButton::Right))
	{
		m_pos.x += WalkSpeed;
	}
	//左移動
	if (input.IsKeyDown(VK_LEFT) || input.IsButtonDown(PadButton::Left))
	{
		m_pos.x -= WalkSpeed;
	}


	//ジャンプキーの取得
	if (input.IsKeyPressed(VK_UP) || input.IsButtonPressed(PadButton::Button3))
	{
		m_jumpState = true;
		m_vel.y = JumpSpeed;
	}

	//ジャンプ状態の処理
	else if (m_jumpState == true){

		//Y軸方向の速度に加速度を与える
		m_vel.y += JumpAccel;
		//Y座標の更新
		m_pos.y += m_vel.y;

		//着地の判定
		if (m_vel.y > 0 && m_pos.y > GROUND_Y){
			m_jumpState = false;
			m_pos.y = GROUND_Y;
		}
	}

	//縦方向の移動範囲を制限する
	if (m_pos.y <= MOVE_TOP){
		m_pos.y = MOVE_TOP;
	}
	else if (m_pos.y >= MOVE_BOTTOM){
		m_pos.y = MOVE_BOTTOM;
	}

	//横方向の移動範囲を制限する
	if (m_pos.x <= MOVE_LEFT){
		m_pos.x = MOVE_LEFT;
	}
	else if (m_pos.x >= MOVE_RIGHT){
		m_pos.x = MOVE_RIGHT;
	}


	//AMove(current_x, m_pos.y);
}