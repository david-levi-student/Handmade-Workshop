#pragma once

/*===================================================================#
| 'Object' source files last updated on 23 February 2022             |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
#===================================================================*/

#include "GLAD/gl.h"
#include <glm.hpp>
#include <string>
#include "Shader.h"
#include "Transform.h"

class Object
{

public:

	Object(Object* parent = nullptr);
	virtual ~Object() = 0 {}

	bool IsLit() const;
	bool IsAlive() const;
	bool IsActive() const;
	bool IsVisible() const;
	bool IsTextured() const;

	void IsLit(bool flag);
	void IsAlive(bool flag);
	void IsActive(bool flag);
	void IsVisible(bool flag);
	void IsTextured(bool flag);

	GLuint GetPriority() const;
	const std::string& GetTag();

	Transform& GetTransform();

	void SetPriority(GLuint priority);
	void SetTag(const std::string& tag);

	virtual void Render(Shader& shader) = 0;
	virtual void Update(GLfloat deltaTime) = 0;
	virtual void SendToShader(Shader& shader) = 0;

protected:

	bool m_isLit{ false };
	bool m_isAlive{ true };
	bool m_isActive{ true };
	bool m_isVisible{ true };
	bool m_isTextured{ false };

	GLuint m_priority{ 0 };
	glm::vec4 m_color{ 1.0f };
	glm::mat3 m_normalMatrix{ 1.0f };

	Object* m_parent;
	std::string m_tag;
	Transform m_transform;

};