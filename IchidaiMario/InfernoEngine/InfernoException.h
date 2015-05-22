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

class MyExceptionBase_RuntimeError: public std::runtime_error{
public:
	//�p�������R���X�g���N�^
	MyExceptionBase_RuntimeError(const std::string& what_arg)
		:runtime_error(what_arg),m_message(what_arg) {};
	MyExceptionBase_RuntimeError(const char* what_arg)
		:runtime_error(what_arg),m_message(what_arg) {};

	//�f�X�g���N�^��Y�ꂸ�ɉ��z��
	virtual ~MyExceptionBase_RuntimeError() {}
    
	virtual const char* what() const { return m_message.c_str(); }

protected:
	const std::string m_message;
};

/*
IO�֘A�̃����^�C���G���[
*/
class IOException : public MyExceptionBase_RuntimeError{
public:
	IOException(const std::string& what_arg) : MyExceptionBase_RuntimeError(what_arg) {}
	IOException(const char* what_arg) : MyExceptionBase_RuntimeError(what_arg) {}
	virtual ~IOException(){}

	virtual const char* what() const { return MyExceptionBase_RuntimeError::what(); }

};

/*
�O���t�B�b�N�X�֘A�̃����^�C���G���[
*/
class GraphicsError : public MyExceptionBase_RuntimeError{
public:
	GraphicsError(const std::string& what_arg) : MyExceptionBase_RuntimeError(what_arg) {}
	GraphicsError(const char* what_arg) : MyExceptionBase_RuntimeError(what_arg) {}
	virtual ~GraphicsError(){}

	virtual const char* what() const { return MyExceptionBase_RuntimeError::what(); }
};

/*
�O���@��֘A�̃����^�C���G���[
*/
class ExternalDeviceError : public MyExceptionBase_RuntimeError{
public:
	ExternalDeviceError(const std::string& what_arg) : MyExceptionBase_RuntimeError(what_arg) {}
	ExternalDeviceError(const char* what_arg) : MyExceptionBase_RuntimeError(what_arg) {}
	virtual ~ExternalDeviceError(){}

	virtual const char* what() const { return MyExceptionBase_RuntimeError::what(); }
};

}
