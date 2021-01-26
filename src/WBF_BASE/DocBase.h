#pragma once

#include "HeaderPre.h"

class CViewBase;
class CFileCtrlManager;
class __MY_EXT_CLASS__ CDocBase : public CDocument
{
public:
	CDocBase();
	virtual ~CDocBase();
	
public:
	virtual CViewBase* GetActiveView();
	virtual CFileCtrlManager* GetFileCtrlManager();

protected:
	CFileCtrlManager* m_pFileCtrlManager;

};

#include "HeaderPost.h"
