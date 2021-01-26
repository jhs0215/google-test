#pragma once

class IFileManager
{
public:
	IFileManager();
	virtual ~IFileManager();

public:
	virtual BOOL ImportFile(const CString& strFullPath) = 0;

};