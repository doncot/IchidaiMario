/*
�����蔻��֘A�̂���₱��
�Փ˔����
�Փˉ������������
*/
#pragma once
#include"MyTypes.h"
#include<GameElements.h>

namespace Inferno
{
	//�Փˌ��o
	bool IsPointInsideRect(const int x, const int y, const Rect& r);
	bool IsPointInsideRect(const Vec2<int>& v, const Rect& r);

	bool IsRect1HittingRect2(const Rect& r1, const Rect& r2);
	bool IsRect1NotHittingRect2(const Rect& r1, const Rect& r2);

	//�Փˉ���
	Vec2<int> KeepSubInsideRect(const Rect& r1, const Rect& r2);

}
