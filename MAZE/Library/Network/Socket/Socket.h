/**
 * @file   Socket.h
 * @brief  Socketクラスのヘッダファイル(未実装)
 * @author kotani
 */
#ifndef SOCKET_H
#define SOCKET_H

#ifdef _MSC_VER
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#endif

struct ConnectDataBase
{

};

/**
 * ソケットのラッパークラス
 */
class Socket
{
public:
	enum Type
	{
		TCP,
		UDP
	};

	Socket();
	~Socket();

	/**
	 * 初期化処理
	 * @param[in] _timeOut 通信待機のタイムアウト時間
	 * @return 成功すればtrue
	 */
	bool Initialize(int _timeOut);

private:
	WSADATA		 m_WsaData;
	sockaddr_in  m_Add;
	timeval		 m_TimeOut;
	fd_set		 m_Fds, m_ReadFds;


	SOCKET m_Socket;
};


#endif
