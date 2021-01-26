#pragma once
class CWBFCategoryBase
{
public:
	CWBFCategoryBase();
	virtual ~CWBFCategoryBase();

public:
	virtual void OnInitial(CMFCRibbonBar* pRibbonBar) = 0;
};

