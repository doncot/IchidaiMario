/*
Input.h
���͋@��
*/

#pragma once
#include<Windows.h>
#include<Gamepad.h>

/*
VKEY�����\
VK_ESCAPE	0x1B
VK_LEFT	0x25	�������L�[
VK_UP	0x26	������L�[
VK_RIGHT	0x27	�E�����L�[
VK_DOWN	0x28	�������L�[
*/

namespace InputNS {
	const int KeyLen = 256;
}

namespace Inferno
{
class Input
{
public:
	Input();

	//�}�E�X�֘A
	int GetMouseX() const;
	int GetMouseY() const;
	bool IsMouseLButtonPressed() const;
	void ClearMouseLButton();

	//�L�[�{�[�h�֘A
	//Key��������Ă����Ԃ��H
	bool IsKeyDown(const unsigned char vkey) const;
	//IskeyPressed���^�ɂȂ����ꍇ�A�Ăяo����Y���L�[�̓��Z�b�g�����i���Z�b�g���Ȃ��o�[�W���������v����΍��\��j�B
	bool IsKeyPressed(const unsigned char vkey);
	bool IsAnyKeyPressed() const;

	void ClearKeys();

	void DisableIME(HWND hWnd);
	void EnableIME(HWND hWnd);

	//�|�[�����O�B�Q�[�����[�v�ɒu��
	void Polling();

	//���͐�p�C�x���g�n���h��
	bool InputProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

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
	Gamepad m_pad;

	//���̓R���e�L�X�g�n���h���iIME�𖳌��ɂ���ەۑ����Ă����A�ĂїL���ɖ߂��ۂɎg���j
	HIMC m_hIMC;
};
}

