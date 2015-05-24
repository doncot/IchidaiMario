/*
Input.h
���͋@��
*/

#pragma once
#include<Windows.h>

/*
VKEY�����\
VK_ESCAPE	0x1B
VK_LEFT	0x25	�������L�[
VK_UP	0x26	������L�[
VK_RIGHT	0x27	�E�����L�[
VK_DOWN	0x28	�������L�[
*/

namespace InputNS {
	//�L�[�{�[�h�L�[�̌�
	const int KeyLen = 256;

	const int MaxButtonNumber = 32;
	const int UseButtonNumber = 16; //���ۂɎg���{�^����
	const int MaxPadNumber = 2; //�����F���ł���p�b�h��API�d�l��2�܂�
	const int DirectionKeyNumber = 4;
	const int SensitivenessThreshold = 1000; //�����L�[�̊��x�i�������������x�������j
}

namespace Inferno
{
	enum class PadButton : char
	{
		Button1 = 0, //PS�R���ł́�
		Button2, //PS�R���ł́�
		Button3, //PS�R���ł́~
		Button4, //PS�R���ł́�
		Button5, //PS�R���ł�L2
		Button6, //PS�R���ł�R2
		Button7, //PS�R���ł�L
		Button8, //PS�R���ł�Start
		Button9, //PS�R���ł�Select
		Button10, //PS�R���ł͖��g�p
		//�����L�[�iPS�R���ł�Analog�I�t�̎��j
		Up = 12,
		Right,
		Down,
		Left
	};

class Input
{
public:
	Input();

#pragma region �}�E�X
	int GetMouseX() const;
	int GetMouseY() const;
	bool IsMouseLButtonPressed() const;
	void ClearMouseLButton();
#pragma endregion

#pragma region �L�[�{�[�h
	//Key��������Ă����Ԃ��H
	bool IsKeyDown(const unsigned char vkey) const;
	//IskeyPressed���^�ɂȂ����ꍇ�A�Ăяo����Y���L�[�̓��Z�b�g�����i���Z�b�g���Ȃ��o�[�W���������v����΍��\��j�B
	//�΂ߓ��͂⓯�����͌��o���ɂ͒��ӁB
	bool IsKeyPressed(const unsigned char vkey);
	bool IsAnyKeyPressed() const;
	void ClearKeys();
#pragma endregion

#pragma region �Q�[���p�b�h�֘A
	//�ǂ̃{�^����������Ă����Ԃ�����B1P�p
	bool IsButtonDown(PadButton btn);
	//�|�[�����O�B�Q�[�����[�v�ɒu��
	void Polling();
#pragma endregion

	//���̑�
	//���͐�p�C�x���g�n���h��
	bool InputProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
	//IME
	void DisableIME(HWND hWnd);
	void EnableIME(HWND hWnd);

private:
	//�}�E�X�֘A
	bool m_LButtonDown;
	bool m_LButtonPressed;
	int m_mouseX;
	int m_mouseY;
	//�L�[�{�[�h�֘A
	bool m_keysDown[InputNS::KeyLen];
	bool m_keysPressed[InputNS::KeyLen];
	//�Q�[���p�b�h�֘A
	bool m_buttonStatus[InputNS::MaxPadNumber][InputNS::MaxButtonNumber];

	//���̓R���e�L�X�g�n���h���iIME�𖳌��ɂ���ەۑ����Ă����A�ĂїL���ɖ߂��ۂɎg���j
	HIMC m_hIMC;
};
}


