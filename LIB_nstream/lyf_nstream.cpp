

#include "stdafx.h"


#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "lyf_nstream.h"
#include "winsock2.h"
#include <sstream>
#include <fstream>

#pragma comment (lib, "ws2_32.lib")

LYF_LIB_BEGIN

inline SOCKET& ptr_2_socket(void* &ptr)
{
	return (SOCKET&)ptr;
}

bool nstream_startup()
{
	WSADATA  wsaData;
	if (int Ret = WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
	{
		cout << "WSAStartup failed with error " << Ret <<endl;
		return false;
	}
	else
		return true;
}

void nstream_shutdown()
{
	if (WSACleanup() == SOCKET_ERROR)
	{
		printf("WSACleanup failed with error %d /n", WSAGetLastError());
	}
}

nstream::nstream()
{
	SOCKET& sock = ptr_2_socket(m_platformImpl);
	sock = 0;
}

nstream::~nstream()
{
	close();
}

bool nstream::open(const string& server, unsigned short port/*=80*/)
{
	hostent* remoteHost;
	if ((remoteHost = gethostbyname(server.c_str())) == nullptr)       //通过主机名获取地址
	{
		printf("can't get serverIP:\"%s\" ,error %d /n", server.c_str(), WSAGetLastError());
		return false;
	}

	SOCKET& sock = ptr_2_socket(m_platformImpl);
	sock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN tcpaddr;
	tcpaddr.sin_family = AF_INET;
	tcpaddr.sin_port = htons(port);
	tcpaddr.sin_addr.s_addr = *((unsigned long *)*remoteHost->h_addr_list);  //转换地址

	if (connect(sock, (const sockaddr *)&tcpaddr, sizeof(tcpaddr)) == SOCKET_ERROR)
	{
		printf("connect error!");
		return false;
	}

	return true;
}

void nstream::close()
{
	SOCKET& sock = ptr_2_socket(m_platformImpl);
	closesocket(sock);
}


nstream& nstream::operator<<(const char* lpString)
{
	SOCKET& sock = ptr_2_socket(m_platformImpl);
	if (send(sock, lpString, strlen(lpString), 0) == SOCKET_ERROR)
		cout << "send request to srever failed\n";

	return *this;
}

nstream& nstream::operator<<(const stringstream& ss)
{
	return *this;
}

nstream& nstream::operator >> (string& s)
{
	SOCKET& sock = ptr_2_socket(m_platformImpl);
	char buffer[4 * 1024];
	int sum = 0;
	int recvd_size = 0;

	ostringstream sout(ios::binary);
	while (1)
	{
		recvd_size = recv(sock, buffer, sizeof(buffer), 0);
		if (recvd_size <= 0)
			break;
		sum += recvd_size;
		sout.write(buffer, recvd_size);
	}
	s = sout.str();

	return *this;
}

nstream& nstream::operator >> (stringstream& ss)
{
	return *this;
}




LYF_LIB_END
