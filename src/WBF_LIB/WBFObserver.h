#pragma once

#include "HeaderPre.h"
class __MY_EXT_CLASS__ CWBFObserver
{
public:
	CWBFObserver();
	virtual ~CWBFObserver();

public:
	virtual void NotifyMessage(UINT uiMsg, WPARAM wParam, LPARAM lParam) = 0;

};

#include "HeaderPost.h"