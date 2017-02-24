#pragma once

//=======================================================================
// 自己尝试实作的c++网络库。目标：
// 1，以stream的方式处理网络数据
// 2，封装操作系统，用户不必知道是用winsock实现还是linux实现
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
// 暂定类，有待扩充                                                                
//=======================================================================
//struct http;

//=======================================================================
// nstream类，以stl标准stream的方式处理http和持续连接等不同形式的数据流  
// 目前只有http实现
//=======================================================================
//template<typename PROTOCOL = http>
class nstream
{
public:
	nstream();
	~nstream();

	bool open(const string& server, unsigned short port=80);
	void close();

	nstream& operator << (const stringstream& ss);//raw data stream,用于和服务器发送数据指令
	nstream& operator << (const char* lpString);//向服务器发送字符串命令，用于http协议
	nstream& operator << (const string& s) { return *this << s.c_str(); }

	nstream& operator >> (stringstream& ss);//接受原始数据
	nstream& operator >> (string& s);
private:
	void* m_platformImpl;
};



LYF_LIB_END

