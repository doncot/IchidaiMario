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

class InfernoRuntimeError: public std::runtime_error{
public:
	//継承したコンストラクタ
	InfernoRuntimeError(const std::string& what_arg)
		:runtime_error(what_arg),m_message(what_arg) {};
	InfernoRuntimeError(const char* what_arg)
		:runtime_error(what_arg),m_message(what_arg) {};

	//デストラクタを忘れずに仮想化
	virtual ~InfernoRuntimeError() {}
    
	virtual const char* what() const { return m_message.c_str(); }

protected:
	const std::string m_message;
};

/*
IO関連のランタイムエラー
*/
class IOException : public InfernoRuntimeError{
public:
	IOException(const std::string& what_arg) : InfernoRuntimeError(what_arg) {}
	IOException(const char* what_arg) : InfernoRuntimeError(what_arg) {}
	virtual ~IOException(){}

	virtual const char* what() const { return InfernoRuntimeError::what(); }

};

/*
グラフィックス関連のランタイムエラー
*/
class GraphicsError : public InfernoRuntimeError{
public:
	GraphicsError(const std::string& what_arg) : InfernoRuntimeError(what_arg) {}
	GraphicsError(const char* what_arg) : InfernoRuntimeError(what_arg) {}
	virtual ~GraphicsError(){}

	virtual const char* what() const { return InfernoRuntimeError::what(); }
};


}
