#include "Raycast.h"

//======================================================================================================
Raycast::Raycast() {}
//======================================================================================================
const glm::vec3& Raycast::GetOrigin() const
{
	return m_origin;
}
//======================================================================================================
const glm::vec3& Raycast::GetDirection() const
{
	return m_direction;
}
//======================================================================================================
void Raycast::SetOrigin(const glm::vec3& origin)
{
	m_origin = origin;
}
//======================================================================================================
void Raycast::SetOrigin(GLfloat x, GLfloat y, GLfloat z)
{
	m_origin.x = x;
	m_origin.y = y;
	m_origin.z = z;
}
//======================================================================================================
void Raycast::SetDirection(const glm::vec3& direction)
{
	m_direction = direction;
}
//======================================================================================================
void Raycast::SetDirection(GLfloat x, GLfloat y, GLfloat z)
{
	m_direction.x = x;
	m_direction.y = y;
	m_direction.z = z;
}