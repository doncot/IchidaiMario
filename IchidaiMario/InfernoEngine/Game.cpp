#include<Game.h>
#include<Gamepad.h>
#include"Graphics.h"


namespace
{
	Inferno::Input* InputHandle;
	LRESULT WINAPI MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
}

namespace Inferno
{
Game::Game()
	:m_IsInitialized(false), m_elapsedFrame(0), m_frameCount(0)
{
	InputHandle = &m_input;
}

Game::~Game()
{
	m_graphics.Finalize();

	InputHandle = nullptr;
}

void Game::Initialize()
{
	//ウィンドウの初期化
	Base::Initialize();
	Base::Resize(800, 600);
	Base::SetPos(Base::Center, Base::Center);
	Base::Show();

	//ウィドウプロシージャを書き換え
	::SetWindowLongPtr(GetHWND(), GWLP_WNDPROC, (LONG_PTR)MessageHandler);

	//IME無効化
	m_input.DisableIME(GetHWND());

	//グラフィックスの初期化
	m_graphics.Initialize(GetHWND());

	//タイマーをスタート


}

void Game::SetClientSize(const int width, const int height)
{
	Base::Resize(width, height);
	Base::SetPos(Base::Center, Base::Center);
	m_graphics.FlashBackScreen(0, 0, 128);
}

void Game::GameLoop()
{
	//フレーム管理
	static int previousFrame = 0;
	m_frameCount = m_elapsedFrame - previousFrame;
	m_elapsedFrame++;
	previousFrame = m_elapsedFrame;

	//ポーリング
	m_input.Polling();

#ifdef _DEBUG
	//Escキーでゲーム終了
	if (m_input.IsKeyPressed(VK_ESCAPE))
	{
		Exit();
	}
#endif //_DEBUG
}

void Game::Draw() const {}

void Game::Exit()
{
	Base::Terminate();
}

bool Game::BeginDrawing() const
{
	return m_graphics.BeginScene() && m_graphics.BeginSprite();
}

void Game::EndDrawing() const
{
	m_graphics.EndSprite();
	m_graphics.EndScene();
}

}

namespace
{
	LRESULT WINAPI MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;
		}

		//入力を処理
		InputHandle->InputProc(hWnd, msg, wParam, lParam);

		return (DefWindowProc(hWnd, msg, wParam, lParam));
	}
}