#pragma once

#include "HeaderPre.h"

class CDocBase;
class __MY_EXT_CLASS__ CWBFDialog : public CDialog
{
public:
	CWBFDialog(CDocBase* pDoc);
	CWBFDialog(UINT uiResID, CDocBase* pDoc, CWnd* pParent = nullptr);
	virtual ~CWBFDialog();

public:
	virtual INT_PTR DoModal();

protected:
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();

protected:
	BOOL m_bModeless; // default true
	CDocBase* m_pMyDoc;
};

#include "HeaderPost.h"