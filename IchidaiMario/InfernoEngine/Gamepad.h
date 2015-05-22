#pragma once
//Gamepad�ׂ̈ɕK�v
#include<Windows.h>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")

namespace Inferno
{
	enum KEY_CODE{
		KEY_UP = 0,
		KEY_RIGHT,
		KEY_DOWN,
		KEY_LEFT,

		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,

		KEY_L,
		KEY_R,

		KEY_L2,
		KEY_R2,

		KEY_START,
		KEY_SELECT,
	};

	const int MaxButtonNumber = 32;
	const int UseButtonNumber = 15; //���ۂɎg���{�^����
	const int MaxPadNumber = 2; //�����F���ł���p�b�h��API�d�l��2�܂�
	const int SensitivenessThreshold = 1000; //�����L�[�̊��x�i�������������x�������j

	class Gamepad
	{
	public:
		Gamepad();

		//�p�b�h�̏󋵂��|�[�����O����B�Q�[�����[�v���Ɏ��s
		void Polling();

	private:
		bool m_buttonStatus[MaxPadNumber][MaxButtonNumber];
	};



}