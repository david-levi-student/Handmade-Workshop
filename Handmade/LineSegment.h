#pragma once

/*===================================================================#
| 'LineSegment' source files last updated on 22 November 2021        |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include "GLAD/gl.h"
#include <glm.hpp>

class Plane;
class SphereCollider;

class LineSegment
{

public:

	LineSegment();

	void SetScale(GLfloat scale);

	void SetStartPoint(const glm::vec3& startPoint);
	void SetStartPoint(GLfloat x, GLfloat y, GLfloat z);

	void SetEndPoint(const glm::vec3& endPoint);
	void SetEndPoint(GLfloat x, GLfloat y, GLfloat z);

	bool IsColliding(const Plane& secondPlane) const;
	bool IsColliding(const SphereCollider& secondSphere) const;

	glm::vec3 PointOnLine(const glm::vec3& point) const;
	glm::vec3 PointOnLine(GLfloat x, GLfloat y, GLfloat z) const;

	void Update() {}
	void Render() { /*debug only*/ }

private:

	GLfloat m_scale{ 1.0f };
	glm::vec3 m_endPoint{ 0.0f };
	glm::vec3 m_startPoint{ 0.0f };
	glm::vec4 m_color{ 1.0f, 0.0f, 1.0f, 1.0f };

};