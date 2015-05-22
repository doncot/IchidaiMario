#include"Gamepad.h"

using namespace Inferno;

namespace
{
	// [ビット値]       0001, 0011, 0010, 0110, 0100, 1100, 1000, 1001, 0000
	//     　　　　　　　　上,   右上,　右,   右下,   下,   左下, 左,   左上,  無効
	//char povbit[9] = { 0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09, 0 };
}

Gamepad::Gamepad() {}

void Gamepad::Polling()
{
	JOYINFOEX padInfo;

	padInfo.dwSize = sizeof(JOYINFOEX);
	padInfo.dwFlags = JOY_RETURNX | JOY_RETURNY | JOY_RETURNBUTTONS;

	//1Pのみ
	if (joyGetPosEx(JOYSTICKID1, &padInfo) == JOYERR_NOERROR)
	{
		//ボタン分だけ回す
		for (int j = 0; j < MaxButtonNumber; j++)
		{
			if (padInfo.dwButtons & JOY_BUTTON1 << j)
				m_buttonStatus[JOYSTICKID1][JOY_BUTTON1 + j] = true;
		}

		//方向キー
		//左
		if (padInfo.dwXpos < (0x7fff - SensitivenessThreshold) )
			m_buttonStatus[JOYSTICKID1][KEY_LEFT] = true;
		//右
		else if (padInfo.dwXpos > (0x7fff + SensitivenessThreshold) )
			m_buttonStatus[JOYSTICKID1][KEY_RIGHT] = true;
		//上		
		if (padInfo.dwYpos < (0x7fff - SensitivenessThreshold) )
			m_buttonStatus[JOYSTICKID1][KEY_UP] = true;
		//下
		else if (padInfo.dwYpos > (0x7fff + SensitivenessThreshold) )
			m_buttonStatus[JOYSTICKID1][KEY_DOWN] = true;
			
	}

		////POVキー（0xffffが無入力）
		//if (padInfo[i].dwPOV != 0xffff)
		//{
		//	int direction = padInfo[i].dwPOV / 4500; //方向算出

		//	for (int i = 0; i < 4; i++)
		//	{
		//		if (povbit[direction] & (1 << (KEY_UP + i)) )
		//			m_buttonStatus[i][KEY_UP + i] = true;
		//	}
		//}
}