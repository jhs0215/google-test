#pragma once

enum E_CATEGORY_TYPE
{
	E_CAT_UNKNOWN = 0,
	E_CAT_MAIN,

	E_CAT_NUM

};

class CWBFCategoryBase;
class CWBFCategoryManager
{
public:
	CWBFCategoryManager();
	virtual ~CWBFCategoryManager();

public:
	void OnInitial(CMFCRibbonBar* pRibbonBar);

protected:
	std::map<UINT, CWBFCategoryBase*> m_mCategory;

};

