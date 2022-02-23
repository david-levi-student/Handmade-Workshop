#pragma once

/*===================================================================#
| 'OrbitCamera' source files last updated on 23 February 2022        |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include "Camera.h"

class OrbitCamera : public Camera
{

public:

	OrbitCamera();
	virtual ~OrbitCamera() {}

	void SetSensitivity(GLfloat sensitivity);
	void SetPitchRange(const glm::vec2& range);
	void SetPitchRange(GLfloat min, GLfloat max);

	void SetZoomDistanceRange(const glm::vec2& range);
	void SetZoomDistanceRange(GLfloat min, GLfloat max);

	void Zoom(GLint motion);
	void Rotate(const glm::ivec2& motion);
	void Rotate(GLint motionX, GLint motionY);

	virtual void Render(Shader& shader) {};
	virtual void Update(GLfloat deltaTime);
	virtual void SendToShader(Shader& shader);

private:

	GLfloat m_sensitivity{ 0.0f };
	GLfloat m_zoomDistance{ 5.0f };

	glm::vec3 m_target{ 0.0f };
	glm::vec2 m_pitchRange{ -89.0f, 89.0f };
	glm::vec2 m_zoomDistanceRange{ 0.5f, 50.0f };

};