/**
 * @file   Socket.cpp
 * @brief  Socketクラスの実装
 * @author kotani
 */
#include "Socket.h"


Socket::Socket() :
m_Socket(0)
{
}


Socket::~Socket()
{
}

bool Socket::Initialize(int _timeOut)
{
	/* 通信のタイムアウト時間の設定 */
	m_TimeOut.tv_sec = _timeOut;
	m_TimeOut.tv_usec = 0;

	if (WSAStartup(MAKEWORD(2, 0), &m_WsaData) != 0)
	{
		OutputDebugString("WSAStartupに失敗しました。");
		return false;
	}

	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_Socket == INVALID_SOCKET)
	{
		WSACleanup();
		OutputDebugString("ソケットの生成に失敗しました。");
		return false;
	}

	FD_SET(m_Socket, &m_ReadFds);

}
