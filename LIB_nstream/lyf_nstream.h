#pragma once

//=======================================================================
// �Լ�����ʵ����c++����⡣Ŀ�꣺
// 1����stream�ķ�ʽ������������
// 2����װ����ϵͳ���û�����֪������winsockʵ�ֻ���linuxʵ��
//=======================================================================
//======================================================================= 

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

#ifndef LYF_LIB
#define LYF_LIB
#define LYF_LIB_BEGIN  namespace lyf {
#define LYF_LIB_END		};
#endif


LYF_LIB_BEGIN

bool nstream_startup();
void nstream_shutdown();

//=======================================================================
// �ݶ��࣬�д�����                                                                
//=======================================================================
//struct http;

//=======================================================================
// nstream�࣬��stl��׼stream�ķ�ʽ����http�ͳ������ӵȲ�ͬ��ʽ��������  
// Ŀǰֻ��httpʵ��
//=======================================================================
//template<typename PROTOCOL = http>
class nstream
{
public:
	nstream();
	~nstream();

	bool open(const string& server, unsigned short port=80);
	void close();

	nstream& operator << (const stringstream& ss);//raw data stream,���ںͷ�������������ָ��
	nstream& operator << (const char* lpString);//������������ַ����������httpЭ��
	nstream& operator << (const string& s) { return *this << s.c_str(); }

	nstream& operator >> (stringstream& ss);//����ԭʼ����
	nstream& operator >> (string& s);
private:
	void* m_platformImpl;
};



LYF_LIB_END

