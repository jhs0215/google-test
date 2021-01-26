#pragma once

#include "HeaderPre.h"

class CFactoryObjectBase;
class __MY_EXT_CLASS__ CFactoryBase
{
protected:
	typedef std::map<UINT, CRuntimeClass*> MAP_OBJECT;

public:
	CFactoryBase();
	virtual ~CFactoryBase();

public:
	virtual BOOL Register(UINT uiType, CRuntimeClass* pRuntime);
	virtual void Unregister(UINT uiType);
	virtual CFactoryObjectBase* CreateObject(UINT uiType);

	virtual long GetTypeList(std::vector<UINT>& lstType);

protected:
	MAP_OBJECT m_mObject;

};

#include "HeaderPost.h"