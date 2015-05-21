#include<Game.h>
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
	//�E�B���h�E�̏�����
	Base::Initialize();
	Base::Resize(800, 600);
	Base::SetPos(Base::Center, Base::Center);
	Base::Show();

	//�E�B�h�E�v���V�[�W������������
	::SetWindowLongPtr(GetHWND(), GWLP_WNDPROC, (LONG_PTR)MessageHandler);

	//IME������
	m_input.DisableIME(GetHWND());

	//�O���t�B�b�N�X�̏�����
	m_graphics.Initialize(GetHWND());

	//�^�C�}�[���X�^�[�g


}

void Game::SetClientSize(const int width, const int height)
{
	Base::Resize(width, height);
	Base::SetPos(Base::Center, Base::Center);
	m_graphics.FlashBackScreen(0, 0, 128);
}

void Game::GameLoop()
{
	//�t���[���Ǘ�
	static int previousFrame = 0;
	m_frameCount = m_elapsedFrame - previousFrame;
	m_elapsedFrame++;
	previousFrame = m_elapsedFrame;

#ifdef _DEBUG
	//Esc�L�[�ŃQ�[���I��
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

		//���͂�����
		InputHandle->InputProc(hWnd, msg, wParam, lParam);

		return (DefWindowProc(hWnd, msg, wParam, lParam));
	}
}