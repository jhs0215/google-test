#include "stdafx.h"
#include "Camera.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Default camera values
const float g_YAW = -90.0f;
const float g_PITCH = 0.0f;
const float g_SPEED = 1.5f;
const float g_SENSITIVITY = 0.1f;
const float g_ZOOM = 45.0f;

CCamera::CCamera()
	: m_eMode(E_MODE_MODELER)
{
	m_aCameraPos = glm::vec3(0.f, 0.f, 10.f);
	m_aCameraDir = glm::vec3(0.f, 0.f, -1.f);
	m_aCameraUp = glm::vec3(0.f, 1.f, 0.f);
	m_aCameraRight = glm::vec3(1.f, 0.f, 0.f);
	m_aWorldUp = glm::vec3(0.f, 1.f, 0.f);
	m_aWorldCenter = glm::vec3(0.f, 0.f, 0.f);

	m_fYaw = g_YAW;
	m_fPitch = g_PITCH;
	m_fMovementSpeed = g_SPEED;
	m_fMouseSensitivity = g_SENSITIVITY;

	UpdateCameraVectors(0.f, 0.f);
}

CCamera::~CCamera()
{
}

glm::mat4 CCamera::GetViewMatrix()
{
	switch (m_eMode)
	{
	case E_MODE_FPS:
		return glm::lookAt(m_aCameraPos - m_aCameraDir, m_aCameraPos, m_aCameraUp);
	case E_MODE_MODELER:
		return glm::lookAt(m_aCameraPos, m_aCameraPos + m_aCameraDir, m_aCameraUp);
	}

	ASSERT(g_warning);
	return glm::lookAt(m_aCameraPos - m_aCameraDir, m_aCameraPos, m_aCameraUp);
}

glm::mat4 CCamera::GetProjectionMatrix()
{
	glm::mat4 proj(1.f);
	return glm::perspective(glm::radians(30.f), (float)(m_Viewport.Width()) / (float)(m_Viewport.Height()), 0.0001f, 1000.f);
}

void CCamera::SetViewSize(CRect& rect)
{
	m_Viewport = rect;
}

void CCamera::SetViewCenter(glm::vec3 & vPosition)
{
	m_aWorldCenter = vPosition;
}

void CCamera::SetCameraPosition(glm::vec3& vPosition)
{
	m_aCameraPos = vPosition;
}

void CCamera::SetMousePosition(CPoint& point)
{
	m_MousePoint = point;
}

void CCamera::OnKeyboardDown(E_CAMERA_MOVEMENT eMovement, float deltaTime)
{
	auto fVelocity = m_fMovementSpeed * deltaTime;
	switch (eMovement)
	{
	case E_CAMERA_FORWARD:
		{
			m_aCameraPos += m_aCameraDir * fVelocity;
		}
		break;
	case E_CAMERA_BACKWARD:
		{
			m_aCameraPos -= m_aCameraDir * fVelocity;
		}
		break;
	case E_CAMERA_LEFT:
		{
			m_aCameraPos -= m_aCameraRight * fVelocity;
		}
		break;
	case E_CAMERA_RIGHT:
		{
			m_aCameraPos += m_aCameraRight * fVelocity;
		}
		break;
	case E_CAMERA_BOTTOM:
		{
			m_aCameraPos -= m_aCameraUp * fVelocity;
		}
		break;
	case E_CAMERA_TOP:
		{
			m_aCameraPos += m_aCameraUp * fVelocity;
		}
		break;
	}
}

void CCamera::OnMouseMove(CPoint point)
{

	auto MouseOffset = m_MousePoint - point;
	auto fOffsetX = (float)MouseOffset.cx * m_fMouseSensitivity;
	auto fOffsetY = (float)MouseOffset.cy * m_fMouseSensitivity;
	m_MousePoint = point;

	UpdateCameraVectors(fOffsetX, fOffsetY);
}

void CCamera::UpdateCameraVectors(float fOffsetX, float fOffsetY)
{
	switch (m_eMode)
	{
	case E_MODE_FPS:
		{
			m_fYaw += fOffsetX;
			m_fPitch += -fOffsetY;

			glm::vec3 aDirection;
			aDirection.x = cos(glm::radians(m_fPitch)) * cos(glm::radians(m_fYaw));
			aDirection.y = sin(glm::radians(m_fPitch));
			aDirection.z = cos(glm::radians(m_fPitch)) * sin(glm::radians(m_fYaw));

			m_aCameraDir = aDirection;
			m_aCameraRight = glm::normalize(glm::cross(m_aCameraDir, m_aWorldUp));
			m_aCameraUp = glm::normalize(glm::cross(m_aCameraRight, m_aCameraDir));
		}
		break;
	case E_MODE_MODELER:
		{
			// Rotate Yaw
			{
				glm::vec3 aUp = m_aCameraUp;
				glm::vec3 aTargetPos = m_aCameraPos;
				glm::vec3 aTargetDir = m_aCameraPos + m_aCameraDir;
				glm::vec3 aCenter = m_aWorldCenter;

				glm::mat4 matRotate(1.f);
				matRotate = glm::rotate(matRotate, glm::radians(-fOffsetX), aUp);
				matRotate = glm::translate(matRotate, -aCenter);

				aTargetPos = matRotate * glm::vec4(aTargetPos, 1.f);
				aTargetDir = matRotate * glm::vec4(aTargetDir, 1.f);

				glm::mat4 matTranslate(1.f);
				matTranslate = glm::translate(matTranslate, aCenter);

				aTargetPos = matTranslate * glm::vec4(aTargetPos, 1.f);
				aTargetDir = matTranslate * glm::vec4(aTargetDir, 1.f);

				m_aCameraPos = aTargetPos;
				m_aCameraDir = glm::normalize(aTargetDir - aTargetPos);
				m_aCameraRight = glm::normalize(glm::cross(m_aCameraDir, m_aCameraUp));
			}

			// Rotate Pitch
			{
				glm::vec3 aUp = m_aCameraRight;
				glm::vec3 aTargetPos = m_aCameraPos;
				glm::vec3 aTargetDir = m_aCameraPos + m_aCameraDir;
				glm::vec3 aCenter = m_aWorldCenter;

				glm::mat4 matRotate(1.f);
				matRotate = glm::rotate(matRotate, glm::radians(fOffsetY), aUp);
				matRotate = glm::translate(matRotate, -aCenter);

				aTargetPos = matRotate * glm::vec4(aTargetPos, 1.f);
				aTargetDir = matRotate * glm::vec4(aTargetDir, 1.f);

				glm::mat4 matTranslate(1.f);
				matTranslate = glm::translate(matTranslate, aCenter);

				aTargetPos = matTranslate * glm::vec4(aTargetPos, 1.f);
				aTargetDir = matTranslate * glm::vec4(aTargetDir, 1.f);

				m_aCameraPos = aTargetPos;
				m_aCameraDir = glm::normalize(aTargetDir - aTargetPos);
				m_aCameraUp = glm::normalize(glm::cross(m_aCameraRight, m_aCameraDir));
			}
		}
		break;
	default:
		{
			ASSERT(g_warning);
		}
		break;
	}
}