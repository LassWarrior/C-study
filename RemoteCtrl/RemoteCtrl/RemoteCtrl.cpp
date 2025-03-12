// RemoteCtrl.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "framework.h"
#include "RemoteCtrl.h"
#include "ServerSocker.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // 初始化 MFC 并在失败时显示错误
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 在此处为应用程序的行为编写代码。
            wprintf(L"错误: MFC 初始化失败\n");
            nRetCode = 1;
        }
        else
        {
            
            // TODO: 在此处为应用程序的行为编写代码。
            //TODO:返回值处理
            int count{};
            if (Cserver->InitSocket() == false)
            {
                MessageBox(NULL, _T("检查网络"), _T("网络初始化错误"), MB_OK | MB_ICONERROR);

            }
            while(Cserver!=NULL)
            {
                
                if (Cserver->AcceptClient() == false)
                {
                    count++;
                    if (count == 3)
                    {
                        MessageBox(NULL, _T("多次无法接入用户，程序结束"), _T("接入用户失败"), MB_OK | MB_ICONERROR);
                        exit(0);
                    }
                    MessageBox(NULL, _T("无法接入用户"), _T("接入用户失败"), MB_OK | MB_ICONERROR);
                }
                int ret = Cserver->DealCommand();
            }
            
            
            //Cserver;
        }
    }
    else
    {
        // TODO: 更改错误代码以符合需要
        wprintf(L"错误: GetModuleHandle 失败\n");
        nRetCode = 1;
    }

    return nRetCode;
}
