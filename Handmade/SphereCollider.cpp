#include <algorithm>
#include "SphereCollider.h"

//======================================================================================================
SphereCollider::SphereCollider() {}
//======================================================================================================
float SphereCollider::GetScale() const
{
	return m_scale;
}
//======================================================================================================
float SphereCollider::GetRadius() const
{
	return m_radius;
}
//======================================================================================================
float SphereCollider::GetRadiusScaled() const
{
	return m_radiusScaled;
}
//======================================================================================================
const glm::vec3& SphereCollider::GetPosition() const
{
	return m_position;
}
//======================================================================================================
void SphereCollider::SetScale(GLfloat scale)
{
	m_scale = scale;
}
//======================================================================================================
void SphereCollider::SetRadius(GLfloat radius)
{
	m_radius = radius;
}
//======================================================================================================
void SphereCollider::SetPosition(const glm::vec3& position)
{
	m_position = position;
}
//======================================================================================================
void SphereCollider::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}
//======================================================================================================
bool SphereCollider::IsColliding(const BoxCollider& secondBox) const
{
	return secondBox.IsColliding(*this);
}
//======================================================================================================
bool SphereCollider::IsColliding(const LineSegment& secondLine) const
{
	return secondLine.IsColliding(*this);
}
//======================================================================================================
bool SphereCollider::IsColliding(const SphereCollider& secondSphere) const
{
	return (glm::length(m_position - secondSphere.m_position) <=
		(m_radius + secondSphere.m_radius));
}
//======================================================================================================
void SphereCollider::Update()
{
	m_radiusScaled = m_radius * m_scale;
}