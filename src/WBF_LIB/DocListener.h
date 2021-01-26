#pragma once

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CDocListener
{
public:
	static void DoNotifyMsg(CDocument* pDoc, WPARAM wParam, LPARAM lParam);

public:
	CDocListener();
	virtual ~CDocListener();

public:
	virtual void OnNotifyMsg(CDocument* pDoc, WPARAM wParam, LPARAM lParam) = 0;

protected:
	static std::vector<CDocListener*> g_lstObject;

};

#include "HeaderPost.h"