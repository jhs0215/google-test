#pragma once

#include "GLView.h"
#include "Camera.h"
#include "FrameBufferManager.h"
#include "ObjectBufferManager.h"
#include "RendererManager.h"
#include "ShaderManager.h"

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CGLCtrlView : public CGLView
{
public:
	CGLCtrlView();
	virtual ~CGLCtrlView();

public:
	virtual void OnDraw(CDC* /*pDC*/);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

public:
	CFrameBufferManager* GetFrameBufferManager() { return &m_FrameBufferManager; }
	CObjectBufferManager* GetObjectBufferManager() { return &m_ObjectBufferManager; }
	CRendererManager* GetRendererManager() { return &m_RendererManager; }
	CShaderManager* GetShaderManager() { return &m_ShaderManager; }

	glm::vec3 GetEyePosition();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetModelViewProjectionMatrix();

protected:
	void GLBindFrameBuffer(UINT uiType);
	void GLUnbindFrameBuffer(UINT uiType);
	void GLCreateScreen();
	void GLPrepareScene();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP();

protected:
	CCamera m_Camera;
	
	CShaderManager m_ShaderManager;
	CRendererManager m_RendererManager;
	CObjectBufferManager m_ObjectBufferManager;
	CFrameBufferManager m_FrameBufferManager;	

	UINT m_uiScreenVAO;
	UINT m_uiScreenVBO;
};

#include "HeaderPost.h"