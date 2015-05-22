#include<Windows.h>
#include<tchar.h>
#include<memory>

#include"MarioMain.h"

#pragma region DetectMemoryLeak
//���������[�N���o�p�B
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

	//�O���[�o���G���[�n���h��
	try
	{
		//��^
		MarioGame game;
		game.Initialize();
		game.Show();

		while (true)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
			{
				//WM_QUITE��������GetMessage��0��Ԃ�
				if (!GetMessage(&msg, NULL, 0, 0)) break;
				TranslateMessage(&msg); //�L�[�{�[�h�֘A�̃��b�Z�[�W��|�󂷂�
				DispatchMessage(&msg); //OS�Ƀ��b�Z�[�W��n���i���E�B���h�E�v���V�[�W���ɓn���j
			}
			else
			{
				//�Q�[�����[�v
				game.GameLoop();
				//�`��
				game.Draw();
			}
			Sleep(1);
		}
	}
	catch (exception e)
	{
		e.what();
	}

	return msg.wParam; //��@
}