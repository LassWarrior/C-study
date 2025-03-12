#include "pch.h"
#include "ServerSocker.h"
CServerSocker* CServerSocker::m_instance=NULL;//私有静态可以声明
CServerSocker::CHelper CServerSocker::m_helper;//私有静态可以声明
CServerSocker* Cserver = CServerSocker::getinstance();//私有静态不能访问
 //CServerSocker Cserver;