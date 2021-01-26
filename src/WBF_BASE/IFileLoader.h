#pragma once

class CDocBase;
class IFileLoader
{
public:
	IFileLoader();
	virtual ~IFileLoader();

public:
	virtual BOOL Import(const CString& strFullPath) = 0;
	virtual BOOL MakeDB(CDocBase* pDoc) = 0;

};

