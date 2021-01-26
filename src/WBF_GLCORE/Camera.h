#pragma once

#ifndef DEF_CAMERA
#define DEF_CAMERA

#include "HeaderPre.h"

enum E_CAMERA_MOVEMENT
{
	E_CAMERA_FORWARD = 0,
	E_CAMERA_BACKWARD,
	E_CAMERA_LEFT,
	E_CAMERA_RIGHT,
	E_CAMERA_BOTTOM,
	E_CAMERA_TOP,
	E_CAMERA_NUM
};

enum E_CAMERA_MODE
{
	E_MODE_FPS = 0,
	E_MODE_MODELER,
	E_MODE_NUM
};

class __MY_EXT_CLASS__ CCamera
{
public:
	CCamera();
	virtual ~CCamera();

public:
	glm::vec3 GetEyePos() { return m_aCameraPos; }
	glm::vec3 GetEyeDir() { return m_aCameraDir; }
	glm::vec3 GetEyeUp() { return m_aCameraUp; }
	glm::vec3 GetEyeRight() { return m_aCameraRight; }
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

public:
	void SetViewSize(CRect& rect);
	void SetViewCenter(glm::vec3& vPosition);
	void SetCameraPosition(glm::vec3& vPosition);
	void SetMousePosition(CPoint& point);	

	void OnKeyboardDown(E_CAMERA_MOVEMENT eMovement, float deltaTime);
	void OnMouseMove(CPoint point);

protected:
	void UpdateCameraVectors(float fOffsetX, float fOffsetY);

protected:
	E_CAMERA_MODE m_eMode;

	CRect m_Viewport;
	CPoint m_MousePoint; // Mouse Move

	glm::vec3 m_aCameraPos;
	glm::vec3 m_aCameraDir;
	glm::vec3 m_aCameraUp;
	glm::vec3 m_aCameraRight;
	glm::vec3 m_aWorldUp;
	glm::vec3 m_aWorldCenter;

	float m_fYaw;
	float m_fPitch;
	float m_fMovementSpeed;
	float m_fMouseSensitivity;
};

#include "HeaderPost.h"

#endif // !DEF_CAMERA