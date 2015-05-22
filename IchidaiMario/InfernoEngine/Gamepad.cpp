#include"Gamepad.h"

using namespace Inferno;

namespace
{
	// [�r�b�g�l]       0001, 0011, 0010, 0110, 0100, 1100, 1000, 1001, 0000
	//     �@�@�@�@�@�@�@�@��,   �E��,�@�E,   �E��,   ��,   ����, ��,   ����,  ����

	char povbit[9] = { 0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09, 0 };
}

Gamepad::Gamepad() {}

void Gamepad::Polling()
{
	JOYINFOEX padInfo;

	padInfo.dwSize = sizeof(JOYINFOEX);
	padInfo.dwFlags = JOY_RETURNX | JOY_RETURNY | JOY_RETURNBUTTONS;

	//1P�̂�
	if (joyGetPosEx(JOYSTICKID1, &padInfo) == JOYERR_NOERROR)
	{
		//�{�^����������
		for (int j = 0; j < MaxButtonNumber; j++)
		{
			if (padInfo.dwButtons & JOY_BUTTON1 << j)
				m_buttonStatus[JOYSTICKID1][JOY_BUTTON1 + j] = true;
		}

		//�����L�[
		//��
		if (padInfo.dwXpos < (0x7fff - SensitivenessThreshold) )
			m_buttonStatus[JOYSTICKID1][KEY_LEFT] = true;
		//�E
		else if (padInfo.dwXpos > (0x7fff + SensitivenessThreshold) )
			m_buttonStatus[JOYSTICKID1][KEY_RIGHT] = true;
		//��		
		if (padInfo.dwYpos < (0x7fff - SensitivenessThreshold) )
			m_buttonStatus[JOYSTICKID1][KEY_UP] = true;
		//��
		else if (padInfo.dwYpos > (0x7fff + SensitivenessThreshold) )
			m_buttonStatus[JOYSTICKID1][KEY_DOWN] = true;
			
	}

		////POV�L�[�i0xffff�������́j
		//if (padInfo[i].dwPOV != 0xffff)
		//{
		//	int direction = padInfo[i].dwPOV / 4500; //�����Z�o

		//	for (int i = 0; i < 4; i++)
		//	{
		//		if (povbit[direction] & (1 << (KEY_UP + i)) )
		//			m_buttonStatus[i][KEY_UP + i] = true;
		//	}
		//}
}