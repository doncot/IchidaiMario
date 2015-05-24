/*
Input.h
入力機器
*/

#pragma once
#include<Windows.h>

/*
VKEY早見表
VK_ESCAPE	0x1B
VK_LEFT	0x25	左方向キー
VK_UP	0x26	上方向キー
VK_RIGHT	0x27	右方向キー
VK_DOWN	0x28	下方向キー
*/

namespace InputNS {
	//キーボードキーの個数
	const int KeyLen = 256;

	const int MaxButtonNumber = 32;
	const int UseButtonNumber = 16; //実際に使うボタン数
	const int MaxPadNumber = 2; //同時認識できるパッドはAPI仕様上2つまで
	const int DirectionKeyNumber = 4;
	const int SensitivenessThreshold = 8000; //方向キーの感度（大きい方が感度が高い）
}

namespace Inferno
{
	enum class PadButton : char
	{
		Button1 = 0, //PSコンでは△
		Button2, //PSコンでは○
		Button3, //PSコンでは×
		Button4, //PSコンでは□
		Button5, //PSコンではL2
		Button6, //PSコンではR2
		Button7, //PSコンではL
		Button8, //PSコンではStart
		Button9, //PSコンではSelect
		Button10, //PSコンでは未使用
		//方向キー（PSコンではAnalogオフの時）
		Up = 12,
		Right,
		Down,
		Left
	};

class Input
{
public:
	Input();

#pragma region マウス
	int GetMouseX() const;
	int GetMouseY() const;
	bool IsMouseLButtonPressed() const;
	void ClearMouseLButton();
#pragma endregion

#pragma region キーボード
	//Keyが押されている状態か？
	bool IsKeyDown(const unsigned char vkey) const;
	//IskeyPressedが真になった場合、呼び出し後該当キーはリセットされる（リセットしないバージョンも需要あれば作る予定）。
	//斜め入力や同時入力検出時には注意。
	bool IsKeyPressed(const unsigned char vkey);
	bool IsAnyKeyPressed() const;
	void ClearKeys();
#pragma endregion

#pragma region ゲームパッド関連
	//どのボタンが押されている状態か判定。1P用
	bool IsButtonDown(PadButton btn);
	//ポーリング。ゲームループに置く
	void Polling();
#pragma endregion

	//その他
	//入力専用イベントハンドラ
	bool InputProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
	//IME
	void DisableIME(HWND hWnd);
	void EnableIME(HWND hWnd);

private:
	//マウス関連
	bool m_LButtonDown;
	bool m_LButtonPressed;
	int m_mouseX;
	int m_mouseY;
	//キーボード関連
	bool m_keysDown[InputNS::KeyLen];
	bool m_keysPressed[InputNS::KeyLen];
	//ゲームパッド関連
	bool m_buttonStatus[InputNS::MaxPadNumber][InputNS::MaxButtonNumber];

	//入力コンテキストハンドル（IMEを無効にする際保存しておき、再び有効に戻す際に使う）
	HIMC m_hIMC;
};
}


