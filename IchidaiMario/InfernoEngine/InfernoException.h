#pragma once
/*
�������g����O�N���X���܂Ƃ߂��w�b�_�[
�Ȃ�����ȉ���c++�W���݂̂ŏ����Ă���
*/
#include<exception>
#include<string>

namespace Inferno{
#define THROW_EXCEPTION(EXCEPTION_TYPE, message) \
  throw EXCEPTION_TYPE(message, __FILE__, __func__, __LINE__)  

class InfernoRuntimeError: public std::runtime_error{
public:
	//�p�������R���X�g���N�^
	InfernoRuntimeError(const std::string& what_arg)
		:runtime_error(what_arg),m_message(what_arg) {};
	InfernoRuntimeError(const char* what_arg)
		:runtime_error(what_arg),m_message(what_arg) {};

	//�f�X�g���N�^��Y�ꂸ�ɉ��z��
	virtual ~InfernoRuntimeError() {}
    
	virtual const char* what() const { return m_message.c_str(); }

protected:
	const std::string m_message;
};

/*
IO�֘A�̃����^�C���G���[
*/
class IOException : public InfernoRuntimeError{
public:
	IOException(const std::string& what_arg) : InfernoRuntimeError(what_arg) {}
	IOException(const char* what_arg) : InfernoRuntimeError(what_arg) {}
	virtual ~IOException(){}

	virtual const char* what() const { return InfernoRuntimeError::what(); }

};

/*
�O���t�B�b�N�X�֘A�̃����^�C���G���[
*/
class GraphicsError : public InfernoRuntimeError{
public:
	GraphicsError(const std::string& what_arg) : InfernoRuntimeError(what_arg) {}
	GraphicsError(const char* what_arg) : InfernoRuntimeError(what_arg) {}
	virtual ~GraphicsError(){}

	virtual const char* what() const { return InfernoRuntimeError::what(); }
};


}
