#pragma once

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CFileCtrl
{
public:
	CFileCtrl();
	CFileCtrl(const CString& strFilePath);
	virtual ~CFileCtrl();

public:
	void SetFilePath(const CString& strFilePath);
	BOOL Exist();
	CString GetPathNameExt();
	CString GetPathName();
	CString GetPath();
	CString GetName();
	CString GetExt();

public:
	static BOOL Exist(const CString& strFullPath);
	static CString Absolute2Relative(const CString& src, const CString& trg);

protected:
	CString m_strFullPath;
	CString m_strPath;
	CString m_strName;
	CString m_strExt;

};

#include "HeaderPost.h"