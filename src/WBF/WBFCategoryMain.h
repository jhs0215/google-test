#pragma once

#include "WBFCategoryBase.h"

class CWBFCategoryMain : public CWBFCategoryBase
{
public:
	CWBFCategoryMain();
	virtual ~CWBFCategoryMain();

public:
	virtual void OnInitial(CMFCRibbonBar* pRibbonBar);

protected:
	CMFCRibbonBar* m_pRibbonBar;
	CMFCRibbonCategory* m_pCategory;
	CMFCRibbonPanel* m_pPanel;
	CMFCRibbonButton* m_pButton;
};

