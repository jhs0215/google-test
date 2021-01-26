#include "stdafx.h"
#include "DocListener.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

std::vector<CDocListener*> CDocListener::g_lstObject;

void CDocListener::DoNotifyMsg(CDocument * pDoc, WPARAM wParam, LPARAM lParam)
{
	for (auto itr : g_lstObject)
		itr->OnNotifyMsg(pDoc, wParam, lParam);
}

CDocListener::CDocListener()
{
	g_lstObject.push_back(this);
}

CDocListener::~CDocListener()
{
	auto itr = std::find(g_lstObject.begin(), g_lstObject.end(), this);
	if (itr != g_lstObject.end())
		g_lstObject.erase(itr);
}