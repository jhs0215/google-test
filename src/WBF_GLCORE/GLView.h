#pragma once

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CGLView : public CView
{
public:
	CGLView();
	virtual ~CGLView();

public:
	void BeginwglCurrent();
	void EndwglCurrent();
	void SwapBuffers();

protected:
	void CreateWGL();
	void DeleteWGL();
	void GLInitial();
	void GLInitialPalette();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);

	DECLARE_MESSAGE_MAP();

protected:
	HDC m_hDC; // m_hWnd ÀÇ DC
	HGLRC m_hRC; // m_hDC ÀÇ RC
	CPalette m_Palette;

};

#include "HeaderPost.h"