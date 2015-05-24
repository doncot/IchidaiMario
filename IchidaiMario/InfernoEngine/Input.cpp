#include<Input.h>
#include<InfernoException.h>

//IME無効化の為に必要
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

#pragma region マウス

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

#pragma region キーボード

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

#pragma region ゲームパッド
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

	//1Pのみ
	if (joyGetPosEx(JOYSTICKID1, &padInfo) == JOYERR_NOERROR)
	{
		//ボタン分だけ回す
		for (int j = 0; j < UseButtonNumber - DirectionKeyNumber; j++)
		{
			if (padInfo.dwButtons & JOY_BUTTON1 << j)
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Button1) + j] = true;
			else
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Button1) + j] = false;
		}

		//方向キー
		//ニュートラル
		int nuturalPos = (padInfo.dwXpos - 0x7fff) + (padInfo.dwYpos - 0x7fff);
		if ( nuturalPos >= -SensitivenessThreshold && nuturalPos <= SensitivenessThreshold )
		{
			for (int i = 0; i < DirectionKeyNumber; i++)
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Up) + i] = false;
		}
		//ニュートラルじゃないなら
		else
		{
			//右
			if (padInfo.dwXpos >(0xffff - SensitivenessThreshold))
			{
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Right)] = true;
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Left)] = false;
			}
			//左
			else if (padInfo.dwXpos < ( 0 + SensitivenessThreshold))
			{
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Left)] = true;
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Right)] = false;
			}
			//上		
			if (padInfo.dwYpos < (0 + SensitivenessThreshold))
			{
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Up)] = true;
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Down)] = false;
			}
			//下
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
#pragma region マウス
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
#pragma region キーボード
	case WM_KEYDOWN:
		m_keysDown[wp] = true;
		m_keysPressed[wp] = true;
		break;
	case WM_KEYUP:
		m_keysDown[wp] = false;
		break;
#pragma endregion
#pragma region ゲームパッド
	case MM_JOY1MOVE:
		{
			//パラメーターから入力方向を検出
			int padX = LOWORD(lp);
			int padY = HIWORD(lp);
			//方向キー
			//ニュートラル
			if ( padX == 0x7eff && padY == 0x7eff )
			{
				for (int i = 0; i < DirectionKeyNumber; i++)
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Up) + i] = false;
			}
			//ニュートラルじゃないなら
			else
			{
				//右
				if (padX == 0xffff)
				{
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Right)] = true;
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Left)] = false;
				}
				//左
				else if (padX == 0)
				{
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Left)] = true;
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Right)] = false;
				}
				//上		
				if (padY == 0)
				{
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Up)] = true;
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Down)] = false;
				}
				//下
				else if (padY == 0xffff)
				{
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Down)] = true;
					m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Up)] = false;
				}
			}
		}
		break;
	case MM_JOY1BUTTONDOWN:
		//ボタンが押されたとき
		for (int i = 0; i < UseButtonNumber - DirectionKeyNumber; i++)
		{
			if (static_cast<unsigned>( wp & (JOY_BUTTON1 << i) ) )
			{
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Button1) + i] = true;
				//メッセージでは1ずつ処理するので、ここで帰る
				break;
			}
		}
		break;
	case MM_JOY1BUTTONUP:
		//ボタンが上がった時
		for (int i = 0; i < UseButtonNumber - DirectionKeyNumber; i++)
		{
			if (static_cast<unsigned>(wp & (JOY_BUTTON1 << i)))
			{
				m_buttonStatus[JOYSTICKID1][static_cast<int>(PadButton::Button1) + i] = false;
				//メッセージでは1ずつ処理するので、ここで帰る
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