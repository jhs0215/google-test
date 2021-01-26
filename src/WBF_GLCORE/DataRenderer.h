#pragma once

#include "..\WBF_LIB\FactoryObjectBase.h"
#include "RendererFactory.h"

#include "HeaderPre.h"

class CViewHelper;
class __MY_EXT_CLASS__ CDataRenderer : public CFactoryObjectBase
{
public:
	CDataRenderer();
	virtual ~CDataRenderer();

public:
	virtual void GLRelease() {}
	virtual void GLBuild(CViewHelper * pHelper, UINT uiFlag) = 0;
	virtual void GLDraw(CViewHelper * pHelper) = 0;
};

#include "HeaderPost.h"

#define DECLARE_DYNAMIC_RENDERER(class_name)\
DECLARE_DYNCREATE(class_name);\
virtual UINT GetType() override;

#define IMPLEMENT_DYNAMIC_RENDERER(class_name, type)\
IMPLEMENT_DYNCREATE(class_name, CDataRenderer);\
UINT class_name::GetType() { return type; }\
BOOL b##class_name = CRendererFactory::GetInstance().Register(type, RUNTIME_CLASS(class_name));