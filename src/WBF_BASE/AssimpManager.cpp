#include "stdafx.h"
#include "AssimpManager.h"
#include "AssimpFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAssimpManager::CAssimpManager(CDocBase* pDoc)
	: m_pDoc(pDoc)
{
	m_aFileLoader.clear();
}

CAssimpManager::~CAssimpManager()
{
	for (auto pFileLoader : m_aFileLoader)
	{
		_SAFE_DELETE(pFileLoader);
	}

	m_aFileLoader.clear();
}

BOOL CAssimpManager::ImportFile(const CString & strFullPath)
{
	auto pFileLoader = new CAssimpFile();
	if (!pFileLoader->Import(strFullPath) ||
		!pFileLoader->MakeDB(m_pDoc))
	{
		ASSERT(g_warning);
		_SAFE_DELETE(pFileLoader);
		
		return FALSE;
	}

	m_aFileLoader.push_back(pFileLoader);

	return TRUE;
}
