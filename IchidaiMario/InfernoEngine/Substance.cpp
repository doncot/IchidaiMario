#define _USE_MATH_DEFINES //一番上にやる必要あり（プロジェクト設定からでもよい）
#include<cmath>

#include<GameElements.h>
#include"Graphics.h"
#include"Collision.h"

namespace Inferno
{
Substance::Substance() 
	: m_idea(nullptr), m_pos(Vec2<int>(0, 0)), m_attribute(0), m_angle(0), m_alpha(0xff)
{
	SetAttribute(GEAttribute::Visible, true);
}
Substance::Substance(const Idea& idea) 
	: m_idea(&idea), m_pos(Vec2<int>(0, 0)), m_attribute(0), m_angle(0), m_alpha(0xff)
{
	SetAttribute(GEAttribute::Visible, true);
}
Substance::~Substance() {}

void Substance::SetIdea(const Idea& idea)
{
	m_idea = &idea;
}

void Substance::AMove(const int x, const int y)
{
	if (CheckAttribute(GEAttribute::UserLock)) return;
	m_pos.x = x;
	m_pos.y = y;
}

void Substance::AMove(const Vec2<int>& c)
{
	AMove(c.x, c.y);
}

void Substance::RMove(const int x, const int y)
{
	if (CheckAttribute(GEAttribute::UserLock)) return;

	m_pos.x += x;
	m_pos.y += y;
}

void Substance::RMove(const Vec2<int>& c)
{
	RMove(c.x, c.y);
}

//左上座標で位置を指定
void Substance::SetPosofULCorner(const int x, const int y)
{
	if (CheckAttribute(GEAttribute::UserLock)) return;
	m_pos.x = x + m_idea->GetWidth()/2;
	m_pos.y = y + m_idea->GetHeight()/2;
}

void Substance::Rotate(const float angle) {	m_angle = angle; }

Vec2<int> Substance::GetPosition() const
{
	return m_pos;
}

Rect Substance::GetHitBox() const
{
	Rect r(m_pos, m_idea->GetHeight(), m_idea->GetWidth());
	return r;
}

bool Substance::CheckAttribute(GEAttribute attr) const
{
	return (m_attribute & attr) ? true : false;
}

void Substance::SetAttribute(GEAttribute attr, bool value)
{
	//ビットを立てる場合
	if (value)
	{
		m_attribute |= attr;
	}
	//ビットを降ろす場合
	else
	{
		m_attribute &= ~attr;
	}
}

void Substance::SetAlpha(const int alpha)
{
	m_alpha = alpha;
}

void Substance::Update()
{
	if (this->IsOutOfRange())
	{
		this->SetAttribute(GEAttribute::KillMe, true);
	}
}

void Substance::Draw(const Graphics& g) const
{
	//描画状態でない場合、帰る
	if (!CheckAttribute(GEAttribute::Visible)) return;

	D3DXMATRIX matWorld; //これをメンバにすれば省略できるがさてさて
	D3DXMatrixIdentity(&matWorld);

	//移動
	//ここからピクセル座標(int)よりスクリーン座標(float)へ変換をする
	matWorld._41 = static_cast<float>(m_pos.x);
	matWorld._42 = static_cast<float>(m_pos.y);
	//回転
	float radian = static_cast<float>(m_angle * M_PI / 180);
	matWorld._11 = std::cosf(radian);
	matWorld._12 = std::sinf(radian);
	matWorld._21 = -std::sinf(radian);
	matWorld._22 = std::cosf(radian);

	//値をセット
	g.GetSprite()->SetTransform(&matWorld);

	g.DrawSprite(m_idea->GetTexture()->GetTexture(),
		Vec2<float>( static_cast<float>(m_idea->GetDrawBase().x),static_cast<float>(m_idea->GetDrawBase().y) ),
		m_alpha
		);
}

Substance& Substance::operator=(const Substance& s)
{
	//自分自身がくる可能性を考慮する
	if (&s != this)
	{
		m_pos = s.m_pos;
		//イデアは同じ（定数なのに注意）
	}
	return *this;
}

//private
bool Substance::IsOutOfRange() const
{
	//範囲が設定されてないなら無視
	if (m_idea->m_activeRange.Width() == 0) return false;
	//画面外なら
	if (!IsPointInsideRect(m_pos, m_idea->m_activeRange))
	{
		return true;
	}
	else return false;
}

}