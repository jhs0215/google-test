#pragma once

#include "..\WBF_LIB\FactoryBase.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CRendererFactory : public CFactoryBase
{
public:
	static CRendererFactory& GetInstance();

public:
	CRendererFactory();
	virtual ~CRendererFactory();
};

#include "HeaderPost.h"


