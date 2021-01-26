#pragma once

#include "HeaderPre.h"

class CDataRenderer;
class __MY_EXT_CLASS__ CRendererManager
{
public:
	CRendererManager();
	virtual ~CRendererManager();
	
public:
	void InitialData(CView* pView);
	void CreateRenderer();

	void GLBuild(UINT uiFlag);
	void GLDelete();
	void GLDrawScene();

protected:
	CView* m_pView;
	std::map<UINT, CDataRenderer*> m_mRenderer;
};

#include "HeaderPost.h"

