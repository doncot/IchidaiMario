#include<Windows.h>
#include<tchar.h>
#include<memory>
#include<Inferno.h>

#include"MarioMain.h"

#pragma region DetectMemoryLeak
//メモリリーク検出用。
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif
#endif
#pragma endregion

using namespace Inferno;
using namespace std;

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE, LPTSTR, int nCmdShow)
{
	MSG msg;

	//グローバルエラーハンドラ
	try
	{
		//定型
		MarioGame game;
		game.Initialize();
		game.Show();

		while (true)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
			{
				//WM_QUITEがきたらGetMessageは0を返す
				if (!GetMessage(&msg, NULL, 0, 0)) break;
				TranslateMessage(&msg); //キーボード関連のメッセージを翻訳する
				DispatchMessage(&msg); //OSにメッセージを渡す（＝ウィンドウプロシージャに渡す）
			}
			else
			{
				//ゲームループ
				game.GameLoop();
				//描画
				game.Draw();
			}
			Sleep(1);
		}
	}
	catch (exception e)
	{
		MessageBox(nullptr, e.what(), "グローバルハンドルエラー", MB_OK | MB_ICONERROR );
		return 0;
	}

	return msg.wParam; //作法
}