#include<Input.h>
#include<InfernoException.h>

//IME�������ׂ̈ɕK�v
#include<imm.h>
#pragma comment(lib, "imm32.lib")

using namespace InputNS;

namespace Inferno
{
Input::Input() :
m_LButtonPressed(false), m_mouseX(0), m_mouseY(0), m_hIMC(nullptr)
{
	for (auto& e : m_keysDown) e = false;
	for (auto& e : m_keysPressed) e = false;
}

#pragma region �}�E�X

	int Input::GetMouseX() const
	{
		return m_mouseX;
	}

	int Input::GetMouseY() const
	{
		return m_mouseY;
	}

	bool Input::IsMouseLButtonPressed() const
	{
		return m_LButtonPressed;
	}

	void Input::ClearMouseLButton()
	{
		m_LButtonDown = false;
		m_LButtonPressed = false;
	}

#pragma endregion

#pragma region �L�[�{�[�h

	bool Input::IsKeyDown(const unsigned char vkey) const
	{
		return m_keysDown[vkey];
	}

	bool Input::IsKeyPressed(const unsigned char vkey)
	{
		bool rvalue = m_keysPressed[vkey];
		m_keysPressed[vkey] = false;
		return rvalue;
	}

	bool Input::IsAnyKeyPressed() const
	{
		for (int i = 0; i < InputNS::KeyLen; i++)
		{
			if (m_keysDown[i] == true || m_keysPressed[i] == true)
			{
				return true;
			}
		}
		return false;

	}

	void Input::ClearKeys()
	{
		for (int i = 0; i < InputNS::KeyLen; i++)
		{
			m_keysDown[i] = false;
			m_keysPressed[i] = false;
		}
	}
#pragma endregion

#pragma region �Q�[���p�b�h
bool Input::IsButtonDown(PadButton btn)
{
	return m_buttonStatus[0][static_cast<int>(btn)];
}

bool Input::IsButtonPressed(PadButton btn)
{
	auto rvalue = m_buttonStatus[0][static_cast<int>(btn)];
	m_buttonStatus[0][static_cast<int>(btn)] = false;
	return rvalue;
}

/*
void Input::Polling()
{
	JOYINFOEX padInfo;

	padInfo.dwSize = sizeof(JOYINFOEX);
	padInfo.dwFlags = JOY_RETURNX | JOY_RETURNY | JOY_RETURNBUTTONS;

	//1P�̂�
	if (joyGetPosEx(JOYSTICKID1, &padInfo) == JOYERR_NOERROR)
	{
		//�{�^����������
		for (int j = 0; j < UseButtonNumber - DirectionKeyNumber; j++)
		{
			if (padInfo.dwButtons & JOY_BUTTON1 << j)
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Button1) + j] = true;
			else
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Button1) + j] = false;
		}

		//�����L�[
		//�j���[�g����
		int nuturalPos = (padInfo.dwXpos - 0x7fff) + (padInfo.dwYpos - 0x7fff);
		if ( nuturalPos >= -SensitivenessThreshold && nuturalPos <= SensitivenessThreshold )
		{
			for (int i = 0; i < DirectionKeyNumber; i++)
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Up) + i] = false;
		}
		//�j���[�g��������Ȃ��Ȃ�
		else
		{
			//�E
			if (padInfo.dwXpos >(0xffff - SensitivenessThreshold))
			{
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Right)] = true;
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Left)] = false;
			}
			//��
			else if (padInfo.dwXpos < ( 0 + SensitivenessThreshold))
			{
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Left)] = true;
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Right)] = false;
			}
			//��		
			if (padInfo.dwYpos < (0 + SensitivenessThreshold))
			{
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Up)] = true;
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Down)] = false;
			}
			//��
			else if (padInfo.dwYpos > (0xffff - SensitivenessThreshold))
			{
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Down)] = true;
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Up)] = false;
			}
		}
	}
}
*/

#pragma endregion

void Input::DisableIME(HWND hWnd)
{
	m_hIMC = ImmAssociateContext(hWnd, NULL);
}

void Input::EnableIME(HWND hWnd)
{
	if (m_hIMC)
	{
		ImmAssociateContext(hWnd, m_hIMC);
	}
}

#pragma region WindowProc
bool Input::InputProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
#pragma region �}�E�X
	case WM_MOUSEMOVE:
		m_mouseX = LOWORD(lp);
		m_mouseY = HIWORD(lp);
		break;
	case WM_LBUTTONDOWN:
		m_LButtonDown = true;
		m_LButtonPressed = true;
		m_mouseX = LOWORD(lp);
		m_mouseY = HIWORD(lp);
		break;
	case WM_LBUTTONUP:
		m_LButtonDown = false;
		m_mouseX = LOWORD(lp);
		m_mouseY = HIWORD(lp);
		break;
#pragma endregion
#pragma region �L�[�{�[�h
	case WM_KEYDOWN:
		m_keysDown[wp] = true;
		m_keysPressed[wp] = true;
		break;
	case WM_KEYUP:
		m_keysDown[wp] = false;
		break;
#pragma endregion
#pragma region �Q�[���p�b�h
	case MM_JOY1MOVE:
		{
			//�p�����[�^�[������͕��������o
			int padX = LOWORD(lp);
			int padY = HIWORD(lp);
			//�����L�[
			//�j���[�g����
			if ( padX == 0x7eff && padY == 0x7eff )
			{
				for (int i = 0; i < DirectionKeyNumber; i++)
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Up) + i] = false;
			}
			//�j���[�g��������Ȃ��Ȃ�
			else
			{
				//�E
				if (padX == 0xffff)
				{
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Right)] = true;
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Left)] = false;
				}
				//��
				else if (padX == 0)
				{
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Left)] = true;
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Right)] = false;
				}
				//��		
				if (padY == 0)
				{
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Up)] = true;
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Down)] = false;
				}
				//��
				else if (padY == 0xffff)
				{
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Down)] = true;
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Up)] = false;
				}
			}
		}
		break;
	case MM_JOY1BUTTONDOWN:
		//�{�^���������ꂽ�Ƃ�
		for (int i = 0; i < UseButtonNumber - DirectionKeyNumber; i++)
		{
			if (static_cast<unsigned>( wp & (JOY_BUTTON1 << i) ) )
			{
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Button1) + i] = true;
				//���b�Z�[�W�ł�1����������̂ŁA�����ŋA��
				break;
			}
		}
		break;
	case MM_JOY1BUTTONUP:
		//�{�^�����オ������
		for (int i = 0; i < UseButtonNumber - DirectionKeyNumber; i++)
		{
			if (static_cast<unsigned>(wp & (JOY_BUTTON1 << i)))
			{
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Button1) + i] = false;
				//���b�Z�[�W�ł�1����������̂ŁA�����ŋA��
				break;
			}
		}
		break;
#pragma endregion

	default:
		break;
	}
	return S_OK;
}
#pragma endregion

}