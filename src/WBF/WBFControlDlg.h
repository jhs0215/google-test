#pragma once

#include "..\WBF_BASE\WBFDialog.h"

class CViewBase;
class CWBFControlDlg : public CWBFDialog
{

public:
	CWBFControlDlg(CDocBase* pDoc, CViewBase* pView, CWnd* pParent = nullptr);
	virtual ~CWBFControlDlg();

	enum { IDD = IDD_WBF_CONTROL_DLG };

public:
	BOOL Create(CWnd* pParent = nullptr);

private:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	virtual void OnCancel();

private:
	void SetControl();
	void Data2Dlg();
	BOOL Dlg2Data();
	BOOL CheckData();
	BOOL Execute();

private:
	afx_msg void OnClickedUpdate();
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP();

private:
	CViewBase* m_pView;
	
	CComboBox m_cobxType;

	// Polygon Option
	CComboBox m_cobxPolyFace;
	CComboBox m_cobxPolyMode;

	// Value
	CSliderCtrl m_slidRatio;

protected:
	BOOL m_bInitGTest;
	FILE* m_pConsoleStream;
};