/*
“–‚½‚è”»’èŠÖ˜A‚Ì‚ ‚ê‚â‚±‚ê
Õ“Ë”»’è‚Æ
Õ“Ë‰“š—¼•û‚¢‚ê‚é
*/
#pragma once
#include"MyTypes.h"
#include<GameElements.h>

namespace Inferno
{
	//Õ“ËŒŸo
	bool IsPointInsideRect(const int x, const int y, const Rect& r);
	bool IsPointInsideRect(const Vec2<int>& v, const Rect& r);

	bool IsRect1HittingRect2(const Rect& r1, const Rect& r2);
	bool IsRect1NotHittingRect2(const Rect& r1, const Rect& r2);

	//Õ“Ë‰“š
	Vec2<int> KeepSubInsideRect(const Rect& r1, const Rect& r2);

}
