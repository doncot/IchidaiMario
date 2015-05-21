#include<Windows.h>
#include<tchar.h>

#include<Game.h>

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

using namespace Inferno;

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE, LPTSTR, int nCmdShow)
{
	//SVShooter game;
	//game.Initialize();
	//game.SetTitleText(_T("フライ・お空ちゃん・フライ！"));
	//game.Show();

	Game game;
	game.Initialize();
	game.SetTitleText("市大マリオ");

	MSG msg;
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
		}
		Sleep(1);
	}
	return msg.wParam; //作法
}