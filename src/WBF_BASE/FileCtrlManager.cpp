#include "stdafx.h"
#include "FileCtrlManager.h"
#include "AssimpManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFileCtrlManager::CFileCtrlManager(CDocBase* pDoc)
	: m_pDoc(pDoc)
{
	m_pFileManager = new CAssimpManager(pDoc);
}

CFileCtrlManager::~CFileCtrlManager()
{
	_SAFE_DELETE(m_pFileManager);
}

IFileManager * CFileCtrlManager::GetFileManager()
{
	return m_pFileManager;
}
