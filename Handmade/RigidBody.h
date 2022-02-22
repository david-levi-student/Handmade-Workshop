#pragma once

/*===================================================================#
| 'RigidBody' source files last updated on 22 February 2022          |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include "GLAD/gl.h"
#include <glm.hpp>
#include <gtc/quaternion.hpp>

const GLdouble GRAVITY = 1.0000000000667;

class RigidBody
{

public:

	static glm::vec3 GravityForce(GLdouble mass_1,
		GLdouble mass_2, const glm::vec3& distance);
	static glm::vec3 TorqueForce(const glm::vec3& force,
		const glm::vec3& contactPosition, const glm::vec3& centreOfMass);

	RigidBody();

	GLdouble GetAngle() const;
	GLdouble GetAngularVelocity() const;

	const glm::vec3& GetForce() const;
	const glm::vec3& GetTorque() const;
	const glm::vec3& GetPosition() const;
	const glm::vec3& GetVelocity() const;

	void SetMass(GLdouble mass);
	void SetAngle(GLdouble angle);
	void SetAngularMass(GLdouble mass);
	void SetAngularVelocity(GLdouble velocity);

	void SetForce(const glm::vec3& force);
	void SetTorque(const glm::vec3& torque);
	void SetPosition(const glm::vec3& position);
	void SetVelocity(const glm::vec3& velocity);

	void AddForce(const glm::vec3& force);
	void AddTorque(const glm::vec3& force, const glm::vec3& contactPoint);

	void Update(GLfloat deltaTime);

private:

	GLdouble m_mass{ 0.0 };
	GLdouble m_angle{ 0.0 };
	GLdouble m_angularMass{ 0.0 };
	GLdouble m_angularVelocity{ 0.0 };
	GLdouble m_angularAcceleration{ 0.0 };

	glm::vec3 m_force{ 0.0f };
	glm::vec3 m_torque{ 0.0f };
	glm::vec3 m_position{ 0.0f };
	glm::vec3 m_velocity{ 0.0f };
	glm::vec3 m_acceleration{ 0.0f };
	glm::quat m_orientation{ 1.0f, 0.0f, 0.0f, 0.0f };

	//TODO - Fix this later
	//glm::vec3 m_angularVelocity;
	//glm::vec3 m_angularAcceleration;
};