#pragma once

/*===================================================================#
| 'Capsule' source files last updated on 22 February 2022            |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include "GLAD/gl.h"
#include <glm.hpp>
#include "SphereCollider.h"
//#include "LineSegment.h"

class Capsule
{

public:

	Capsule();
	Capsule(const glm::vec3& vertex1, const glm::vec3& vertex2, GLfloat radius);

	bool IsColliding(const SphereCollider& secondSphere) const;

private:

	//LineSegment m_linesegment;
	GLfloat m_radius{ 0.0f };

};