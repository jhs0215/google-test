#pragma once

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CFactoryObjectBase : public CObject
{
public:
	CFactoryObjectBase();
	virtual ~CFactoryObjectBase();

public:
	virtual UINT GetType() = 0;

};

#include "HeaderPost.h"
