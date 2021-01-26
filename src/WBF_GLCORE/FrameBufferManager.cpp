#include "stdafx.h"
#include "FrameBufferManager.h"
#include "FrameBuffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFrameBufferManager::CFrameBufferManager()
{
	memset(m_aFBO, 0, sizeof(m_aFBO));
}

CFrameBufferManager::~CFrameBufferManager()
{
}

void CFrameBufferManager::GLCreate()
{
	for (UINT uiType = E_FBO_SCREEN; uiType < E_FBO_NUM; ++uiType)
	{
		m_aFBO[uiType] = new CFrameBuffer;

		switch (uiType)
		{
		case E_FBO_SCREEN: break; // Unknown
		default:
			{
				int aViewport[4] = {0};
				glGetIntegerv(GL_VIEWPORT, aViewport);

				auto width = aViewport[2] - aViewport[0];
				auto height = aViewport[3] - aViewport[1];

				m_aFBO[uiType]->GLGeneralFrameBuffer();
				m_aFBO[uiType]->GLBind();
				{
					if (!m_aFBO[uiType]->GLAttachColorTexture2D(GL_COLOR_ATTACHMENT0, width, height) ||
						!m_aFBO[uiType]->GLAttachDepthStencilRender(width, height) ||
						!m_aFBO[uiType]->IsValidFrameBuffer())
					{
						m_aFBO[uiType]->GLDeleteColorTexture2D();
						m_aFBO[uiType]->GLDeleteDepthStencilRender();
						m_aFBO[uiType]->GLDeleteFrameBuffer();
					}
				}
				m_aFBO[uiType]->GLUnbind();
			}
			break;
		}
	}
}

void CFrameBufferManager::GLDelete()
{
	for (UINT uiType = 0; uiType < E_FBO_NUM; ++uiType)
	{
		m_aFBO[uiType]->GLDeleteFrameBuffer();
		m_aFBO[uiType]->GLDeleteColorTexture2D();
		m_aFBO[uiType]->GLDeleteDepthStencilRender();		

		_SAFE_DELETE(m_aFBO[uiType]);
	}
}

void CFrameBufferManager::GLResize(int x, int y)
{
	for (UINT uiType = E_FBO_SCREEN; uiType < E_FBO_NUM; ++uiType)
	{
		m_aFBO[uiType]->GLBind();
		{
			m_aFBO[uiType]->GLResizeColorTexture2D(x, y);
			m_aFBO[uiType]->GLResizeDepthStencilRender(x, y);
			m_aFBO[uiType]->IsValidFrameBuffer();
		}
		m_aFBO[uiType]->GLUnbind();
	}
}

void CFrameBufferManager::GLBind(UINT uiType)
{
	m_aFBO[uiType]->GLBind();
}

void CFrameBufferManager::GLUnbind(UINT uiType)
{
	m_aFBO[uiType]->GLUnbind();
}

void CFrameBufferManager::GLBindColorTex2D(UINT uiType)
{
	m_aFBO[uiType]->GLBindColorTex2D();
}

void CFrameBufferManager::GLUnbindColorTex2D(UINT uiType)
{
	m_aFBO[uiType]->GLUnbindColorTex2D();
}
