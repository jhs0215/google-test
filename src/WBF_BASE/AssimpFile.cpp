#include "stdafx.h"
#include "AssimpFile.h"

#include "..\WBF_LIB\StringConverter.h"
#include "..\WBF_LIB\FileCtrl.h"
#include "..\WBF_BASE\DocBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAssimpFile::CAssimpFile()
{
	m_strFullPath = _T("");
}

CAssimpFile::~CAssimpFile()
{
}

BOOL CAssimpFile::Import(const CString & strFullPath)
{
	m_strFullPath = strFullPath;

	auto strFilePath = CStringConverter::CSTR2STR(strFullPath, CP_UTF8);
	const aiScene* pScene = m_Importer.ReadFile(strFilePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode) // if is Not Zero
	{
		TRACE(m_Importer.GetErrorString());
		return FALSE;
	}

	return TRUE;
}

BOOL CAssimpFile::MakeDB(CDocBase * /*pDoc*/)
{
	return TRUE;
}
