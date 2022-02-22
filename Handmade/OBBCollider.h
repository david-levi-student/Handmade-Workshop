#pragma once

/*===================================================================#
| 'OBBCollider' source files last updated on 22 February 2022        |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include <array>
#include "GLAD/gl.h"
#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include "BoxCollider.h"
#include "SphereCollider.h"

class OBBCollider
{

public:

	OBBCollider();

	const glm::vec3& GetScale() const;
	const glm::vec3& GetPosition() const;
	const glm::quat& GetRotation() const;
	const glm::vec3& GetDimension() const;

	void SetScale(const glm::vec3& scale);
	void SetScale(GLfloat x, GLfloat y, GLfloat z);

	void SetPosition(const glm::vec3& position);
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);

	void SetRotation(const glm::quat& rotation);
	void SetRotation(const glm::vec3& eulerAngles);
	void SetRotation(GLfloat pitch, GLfloat yaw, GLfloat roll);

	void SetDimension(const glm::vec3& dimension);
	void SetDimension(GLfloat width, GLfloat height, GLfloat depth);

	bool IsColliding(const OBBCollider& secondBox) const;
	bool IsColliding(const BoxCollider& secondBox) const;
	bool IsColliding(const SphereCollider& secondSphere) const;

	glm::vec3 PointOnBox(const glm::vec3& point) const;
	glm::vec3 PointOnBox(GLfloat x, GLfloat y, GLfloat z) const;

	void Update();
	void Render() { /*debug only*/ }

private:

	glm::vec3 m_upAxis{ 0.0f, 1.0f, 0.0f };
	glm::vec3 m_rightAxis{ 1.0f, 0.0f, 0.0f };
	glm::vec3 m_forwardAxis{ 0.0f, 0.0f, -1.0f };
	std::array<glm::vec3, 8> m_corners{ glm::vec3(0.0f) };

	glm::vec3 m_scale{ 1.0f };
	glm::vec3 m_position{ 0.0f };
	glm::vec3 m_dimension{ 1.0f };
	glm::vec3 m_halfDimension{ 0.5f };
	glm::vec4 m_color{ 1.0f, 0.5f, 0.0f, 0.4f };
	glm::quat m_rotation{ 1.0f, 0.0f, 0.0f, 0.0f };

};