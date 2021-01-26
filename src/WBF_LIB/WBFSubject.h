#pragma once

#include "HeaderPre.h"

class CWBFObserver;
class __MY_EXT_CLASS__ CWBFSubject
{
public:
	CWBFSubject();
	virtual ~CWBFSubject();

public:
	void Clear();
	void Attached(CWBFObserver* obj);
	void Dettached(CWBFObserver* obj);

	void Notify(UINT uiMsg, WPARAM wParam = NULL, LPARAM lParam = NULL);

protected:
	std::vector<CWBFObserver*> m_vObserver;
};
#include "HeaderPost.h"

