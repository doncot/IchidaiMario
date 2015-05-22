#pragma once
//Gamepadの為に必要
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
	const int UseButtonNumber = 15; //実際に使うボタン数
	const int MaxPadNumber = 2; //同時認識できるパッドはAPI仕様上2つまで
	const int SensitivenessThreshold = 1000; //方向キーの感度（小さい方が感度が高い）

	class Gamepad
	{
	public:
		Gamepad();

		//パッドの状況をポーリングする。ゲームループ毎に実行
		void Polling();

	private:
		bool m_buttonStatus[MaxPadNumber][MaxButtonNumber];
	};



}