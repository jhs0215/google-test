#pragma once

#include "IFileManager.h"

#include "HeaderPre.h"

class CDocBase;
class __MY_EXT_CLASS__ CFileCtrlManager
{
public:
	CFileCtrlManager(CDocBase* pDoc);
	virtual ~CFileCtrlManager();

public:
	IFileManager* GetFileManager();

protected:
	CDocBase* m_pDoc;

	IFileManager* m_pFileManager;

};

#include "HeaderPost.h"
