#pragma once

#include "HeaderPre.h"

class CObjectBuffer;
class __MY_EXT_CLASS__ CObjectBufferManager
{
public:
	CObjectBufferManager();
	virtual ~CObjectBufferManager();

public:
	void InitialData(CView* pView);
	void Create();

	BOOL Exist(UINT uiType);
	CObjectBuffer* LookUp(UINT uiType);
	
	void GLBuild(UINT uiFlag);	
	void GLDelete();

protected:
	CView* m_pView;
	std::map<UINT, CObjectBuffer*> m_mObjectBuffer;

};

#include "HeaderPost.h"