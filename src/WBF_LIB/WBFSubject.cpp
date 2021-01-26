#include "stdafx.h"
#include "WBFSubject.h"
#include "WBFObserver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFSubject::CWBFSubject()
{
}


CWBFSubject::~CWBFSubject()
{
	Clear();
}

void CWBFSubject::Clear()
{
	m_vObserver.clear();
}

void CWBFSubject::Attached(CWBFObserver * obj)
{
	auto itr = std::find(m_vObserver.begin(), m_vObserver.end(), obj);
	if (itr != m_vObserver.end())
	{
		ASSERT(g_warning);
		m_vObserver.erase(itr);
	}

	m_vObserver.push_back(obj);
}

void CWBFSubject::Dettached(CWBFObserver * obj)
{
	auto itr = std::find(m_vObserver.begin(), m_vObserver.end(), obj);
	if (itr != m_vObserver.end())
		m_vObserver.erase(itr);
	else
		ASSERT(g_warning);
}

void CWBFSubject::Notify(UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	for (auto obj : m_vObserver)
	{
		obj->NotifyMessage(uiMsg, wParam, lParam);
	}
}
