#pragma once

#include "..\WBF_LIB\FactoryBase.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CObjectBufferFactory : public CFactoryBase
{
public:
	static CObjectBufferFactory& GetInstance();

public:
	CObjectBufferFactory();
	virtual ~CObjectBufferFactory();
};

#include "HeaderPost.h"

