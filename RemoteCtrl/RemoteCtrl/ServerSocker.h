#pragma once
#include "framework.h"
#include "pch.h"
class CServerSocker
{
public:
	static CServerSocker* getinstance()
	{
		if (m_instance == NULL)
		{
			m_instance = new CServerSocker();
		}
		return m_instance;
	}
	bool InitSocket()
	{
		struct sockaddr_in seraddr, cliaddr;
		
		if (server != -1)
		{
			return false;
		}
		memset(&seraddr, 0, sizeof(seraddr));
		seraddr.sin_family = AF_INET;
		seraddr.sin_addr.s_addr = INADDR_ANY;//arpa
		seraddr.sin_port = htons(5535);
		int ret = bind(server, (const sockaddr*)&seraddr, sizeof(seraddr));
		if (ret == -1)
		{
			return false;
		}
		ret = listen(server, 1); //受控方只监控一个
		if (ret == -1)
		{
			return false;
		}
		return true;
	}
	bool AcceptClient()//accept
	{
		struct sockaddr_in  cliaddr;
		int cliaddrlen = sizeof(cliaddr);
		client = accept(server, (struct sockaddr*)&cliaddr, &cliaddrlen);
		if (client == -1) return false;
		return true;
	}
	int DealCommand()//处理接收数据
	{
		char buffer[1024];
		if (client = -1)
			return false;
		while(true)
		{
			if (recv(client, buffer, sizeof(buffer), 0)<=0)
			{
				return -1;
			}
		
		}
		
	}
	bool Senddata(const char* pData, int nSize)
	{
		if (server = -1)
			return false;
		return send(client, pData, nSize, 0)>0;
	}
private:
	SOCKET server;
	SOCKET client;
	CServerSocker& operator=(const CServerSocker&) {}
	CServerSocker(const CServerSocker& ss) 
	{
		server = ss.server;
		client = ss.client;
	}
	CServerSocker()
	{
		client = INVALID_SOCKET;//初始化成员 server在下方初始化
		if(!InitSocketEnv())
		{ 
			MessageBox(NULL, _T("无法初始化套接字环境"), _T("初始化错误"), MB_OK|MB_ICONERROR);
			exit(0);
		}
		 server = socket(PF_INET, SOCK_STREAM, 0);//构造函数中初始化
	}
	~CServerSocker() {
		WSACleanup();
		closesocket(server);//析构中释放套接字
	}
	BOOL InitSocketEnv()
	{
		WSADATA data;
		if (WSAStartup(MAKEWORD(1, 1), &data) != 0)
		{
			return FALSE;
		}
		else
			return TRUE;
	}
	static void releaseInstance()
	{
		if (m_instance != NULL)
		{
			CServerSocker* tmp = CServerSocker::m_instance;
			CServerSocker::m_instance = NULL;
			delete tmp;
		}
	}
	static CServerSocker* m_instance;
	class CHelper
	{
	public:
		CHelper()
		{
			CServerSocker::getinstance();
		}
		~CHelper() 
		{
			CServerSocker::releaseInstance();
		}
	};
	static CHelper m_helper;
};
extern CServerSocker* Cserver;
