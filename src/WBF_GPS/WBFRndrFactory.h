#pragma once

#include <vector>
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CWBFRndrFactory
{
public:
	static CWBFRndrFactory* GetInstance();

public:
	CWBFRndrFactory();
	~CWBFRndrFactory();

public:
	void AddRegister(CRuntimeClass* pClass);

protected:
	std::vector<CRuntimeClass*> m_vObject;

};

#include "HeaderPost.h"

