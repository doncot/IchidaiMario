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

class RuntimeException: public std::runtime_error{
public:
	//継承したコンストラクタ
	RuntimeException(const std::string& what_arg)
		:runtime_error(what_arg),m_message(what_arg) {};
	RuntimeException(const char* what_arg)
		:runtime_error(what_arg),m_message(what_arg) {};

	//デストラクタを忘れずに仮想化
	virtual ~RuntimeException() {}
    
	virtual const char* what() const { return m_message.c_str(); }

protected:
	const std::string m_message;
};

/*
IO関連のランタイムエラー
*/
class IOException : public RuntimeException{
public:
	IOException(const std::string& what_arg) : RuntimeException(what_arg) {}
	IOException(const char* what_arg) : RuntimeException(what_arg) {}
	virtual ~IOException(){}

	virtual const char* what() const { return RuntimeException::what(); }

};

/*
グラフィックス関連のランタイムエラー
*/
class GraphicsError : public RuntimeException{
public:
	GraphicsError(const std::string& what_arg) : RuntimeException(what_arg) {}
	GraphicsError(const char* what_arg) : RuntimeException(what_arg) {}
	virtual ~GraphicsError(){}

	virtual const char* what() const { return RuntimeException::what(); }
};


}
