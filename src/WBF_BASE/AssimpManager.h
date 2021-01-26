#pragma once

#include "IFileManager.h"
#include "IFileLoader.h"

class CDocBase;
class CAssimpManager : public IFileManager
{
public:
	CAssimpManager(CDocBase* pDoc);
	virtual ~CAssimpManager();

public:
	virtual BOOL ImportFile(const CString & strFullPath) override;

protected:
	CDocBase* m_pDoc;
	std::vector<IFileLoader*> m_aFileLoader;

};