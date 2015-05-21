/*
共通処理ファイル
win32用
*/

#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H
#include<Windows.h>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p!=nullptr) { delete (p);     (p)=nullptr; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p!=nullptr) { delete[] (p);   (p)=nullptr; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=nullptr; } }
#endif

#ifndef ERROR_MESSAGE
#define ERROR_MESSAGE(x) { MessageBox(NULL,(x),TEXT("エラー"),MB_OK|MB_ICONERROR); }
#endif

#ifndef ERROR_EXIT
#define ERROR_EXIT(x) {	 const int msg_size=_MAX_FNAME + _MAX_EXT +512;\
	TCHAR msg[msg_size];\
	TCHAR drive[_MAX_DRIVE];\
	TCHAR dir[_MAX_DIR];\
	TCHAR fname[_MAX_FNAME];\
	TCHAR ext[_MAX_EXT];\
	_tsplitpath_s(TEXT(__FILE__),drive,_MAX_DRIVE,dir,_MAX_DIR,fname,_MAX_FNAME,ext,_MAX_EXT);\
	_stprintf_s(msg, msg_size, TEXT("%s\r\nファイル：%s%s\r\n行番号：%d"),x,fname,ext,__LINE__);\
	MessageBox(NULL,msg,TEXT("Error"),MB_OK|MB_ICONEXCLAMATION);\
	PostQuitMessage(1);\
}
#endif

#endif //INCLUDE_COMMON_H
