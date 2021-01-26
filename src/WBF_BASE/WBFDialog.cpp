#include "stdafx.h"
#include "WBFDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFDialog::CWBFDialog(CDocBase * pDoc)
	: CDialog(), m_pMyDoc(pDoc), m_bModeless(TRUE)
{
}

CWBFDialog::CWBFDialog(UINT uiResID, CDocBase * pDoc, CWnd * pParent)
	: CDialog(uiResID, pParent), m_pMyDoc(pDoc), m_bModeless(TRUE)
{
}

CWBFDialog::~CWBFDialog()
{
}

INT_PTR CWBFDialog::DoModal()
{
	m_bModeless = FALSE;

	return CDialog::DoModal();
}

void CWBFDialog::OnOK()
{
	CDialog::OnOK();

	if (m_bModeless) CDialog::DestroyWindow();
}

void CWBFDialog::OnCancel()
{
	CDialog::OnCancel();

	if (m_bModeless) CDialog::DestroyWindow();
}

void CWBFDialog::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	
	if (m_bModeless) delete this;
}