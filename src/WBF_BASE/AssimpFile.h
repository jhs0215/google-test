#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "IFileLoader.h"

class CAssimpFile : public IFileLoader
{
public:
	CAssimpFile();
	virtual ~CAssimpFile();

public:
	virtual BOOL Import(const CString& strFullPath) override;
	virtual BOOL MakeDB(CDocBase* pDoc) override;

protected:
	CString m_strFullPath;

	Assimp::Importer m_Importer;

};