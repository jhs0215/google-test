#pragma once

#include "HeaderPre.h"

class CFrameBufferManager;
class CObjectBufferManager;
class CRendererManager;
class CShaderManager;
class __MY_EXT_CLASS__ CViewHelper
{
public:
	CViewHelper();
	virtual ~CViewHelper();

public:
	CDocument* GetDocument();
	CView* GetView();
	CFrameBufferManager* GetFrameBufferManager();
	CObjectBufferManager* GetObjectBufferManager();
	CRendererManager* GetRendererManager();	
	CShaderManager* GetShaderManager();

public:
	void InitialData(CView* pView) { m_pView = pView; }
	BOOL IsValidData();

protected:
	CView* m_pView;
};

#include "HeaderPost.h"
