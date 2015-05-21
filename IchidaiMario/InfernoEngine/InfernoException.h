#pragma once
/*
自分が使う例外クラスをまとめたヘッダー
なおこれ以下はc++標準のみで書いている
*/
#include<exception>
#include<string>

namespace Inferno{
#define THROW_EXCEPTION(EXCEPTION_TYPE, message) \
  throw EXCEPTION_TYPE(message, __FILE__, __func__, __LINE__)  

class MyExceptionBase_RuntimeError: public std::runtime_error{
public:
	//継承したコンストラクタ
	MyExceptionBase_RuntimeError(const std::string& what_arg)
		:runtime_error(what_arg),m_message(what_arg) {};
	MyExceptionBase_RuntimeError(const char* what_arg)
		:runtime_error(what_arg),m_message(what_arg) {};

	//デストラクタを忘れずに仮想化
	virtual ~MyExceptionBase_RuntimeError() {}
    
	virtual const char* what() const { return m_message.c_str(); }

protected:
	const std::string m_message;
};

/*
IO関連のランタイムエラー
*/
class IOException : public MyExceptionBase_RuntimeError{
public:
	IOException(const std::string& what_arg) : MyExceptionBase_RuntimeError(what_arg) {}
	IOException(const char* what_arg) : MyExceptionBase_RuntimeError(what_arg) {}
	virtual ~IOException(){}

	virtual const char* what() const { return MyExceptionBase_RuntimeError::what(); }

};

/*
グラフィックス関連のランタイムエラー
*/
class GraphicsError : public MyExceptionBase_RuntimeError{
public:
	GraphicsError(const std::string& what_arg) : MyExceptionBase_RuntimeError(what_arg) {}
	GraphicsError(const char* what_arg) : MyExceptionBase_RuntimeError(what_arg) {}
	virtual ~GraphicsError(){}

	virtual const char* what() const { return MyExceptionBase_RuntimeError::what(); }
};


}
