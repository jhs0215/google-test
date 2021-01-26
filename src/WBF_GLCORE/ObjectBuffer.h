#pragma once

#include "..\WBF_LIB\FactoryObjectBase.h"
#include "ObjectBufferFactory.h"

#include "HeaderPre.h"

typedef struct tagObjectBuffer
{
	UINT uiVAO;
	UINT uiVBO;
	UINT uiEBO;
	UINT uiSize;

	tagObjectBuffer(UINT _uiVAO = 0, UINT _uiVBO = 0, UINT _uiEBO = 0, UINT _uiDataSize = 0)
		: uiVAO(_uiVAO), uiVBO(_uiVBO), uiEBO(_uiEBO), uiSize(_uiDataSize)
	{}

} TObjectBuffer, *LPObjectBuffer;

class CViewHelper;
class __MY_EXT_CLASS__ CObjectBuffer : public CFactoryObjectBase
{
public:
	CObjectBuffer();
	virtual ~CObjectBuffer();

public:
	virtual void GLRelease() = 0;
	virtual void GLBuild(CViewHelper * pHelper, UINT uiFlag) = 0;
	virtual long GetObjectBuffer(std::map<UINT, TObjectBuffer>& mObjectBuffer) = 0;
	
};

#include "HeaderPost.h"

#define DECLARE_DYNAMIC_BUFFER(class_name)\
DECLARE_DYNCREATE(class_name);\
virtual UINT GetType() override;

#define IMPLEMENT_DYNAMIC_BUFFER(class_name, type)\
IMPLEMENT_DYNCREATE(class_name, CObjectBuffer);\
UINT class_name::GetType() { return type; }\
BOOL b##class_name = CObjectBufferFactory::GetInstance().Register(type, RUNTIME_CLASS(class_name));