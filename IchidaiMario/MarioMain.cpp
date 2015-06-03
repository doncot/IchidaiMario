#include"MarioMain.h"
#include<Inferno.h>
#include"Player.h"

using namespace Inferno;

#define GROUND_Y 500


//�ʒu���擾
//TODO:�����ɃI�u�W�F�N�g��n��
static struct xy_coord_t getPos(Instant target){
	struct xy_coord_t pos;

	pos.x = target.GetPosition().x;
	pos.y = target.GetPosition().y;

	return pos;
}

namespace
{
	//�G�L�����Ȃǂ̕ϐ��͂����ɏ���
	Texture playerTex;
	Idea player_;
	Player player;

	Instant background;

}

//������
void MarioGame::Initialize()
{
	Base::Initialize();
	SetTitleText("�s��}���I"); //�E�B���h�E�^�C�g���ɕ\�����镶����
	SetClientSize(800, 600);

	//�������珉��������
	playerTex.LoadImageFile(m_graphics, "Resource\\player.bmp");
	player_.SetTexture(playerTex);
	player.SetIdea(player_);
	player.AMove(0, GROUND_Y);
	player.SetAttribute(GEAttribute::Visible, true);

	//enemy[0].SetIdea(enemy_);
	//enemy2.SetIdea(enemy_);
	//enemy3.SetIdea(enemy_);

	background.Initialize();
	background.LoadTextureFromFile(m_graphics, "Resource\\background.png");
	background.SetPosofULCorner(0, 0);

}

//�Q�[�����[�v�i�����͂����ɏ����Ă����j
void MarioGame::GameLoop()
{
	Base::GameLoop();
	//��������Q�[���{�̏���
	player.Move(m_input);


}

//�`��
void MarioGame::Draw()
{
	if (BeginDrawing() == true)
	{
		//�����ɕ`�揈���������i��ɏ����������珇�Ԃɕ`�悳���j
		background.Draw(m_graphics);

		player.Draw(m_graphics);

	}
	EndDrawing();
}