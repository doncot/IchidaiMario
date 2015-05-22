#include"MarioMain.h"
#include<Game.h>
#include<Input.h>
#include<GameElements.h>

using namespace Inferno;

namespace
{
	//�G�L�����Ȃǂ̕ϐ��͂����ɏ�����
	Instant teki;

}

//������
void MarioGame::Initialize()
{
	Base::Initialize();
	SetTitleText("�s��}���I"); //�E�B���h�E�^�C�g���ɕ\�����镶����

	//�������珉��������
	teki.Initialize();
	teki.LoadTextureFromFile(m_graphics, "Resource\\teki.bmp");


}

//�Q�[�����[�v�i�����͂����ɏ����Ă����j
void MarioGame::GameLoop()
{
	Base::GameLoop();

	//��������Q�[���{�̏���

	//���͗�
	if (m_input.IsKeyPressed('A'))
	{
		MessageBox(nullptr,"A��������܂���","Message",MB_OK);
	}

	//�G�𓮂���
	teki.AMove(200, 200);

}

//�`��
void MarioGame::Draw()
{
	if (m_graphics.BeginScene() && Base::m_graphics.BeginSprite())
	{
		//�����ɕ`�揈��������
		teki.Draw(m_graphics);

	}
	m_graphics.EndSprite();
	m_graphics.EndScene();
}