#pragma once
#include "GLAD/gl.h"
#include <glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include "Transform.h"

class Object
{

public:

	Object(const std::string& tag);
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
	const std::string& GetTag() const;
	const glm::vec4& GetColor() const;

	Transform& GetTransform();

	void SetPriority(GLuint priority);
	void SetTag(const std::string& tag);

	void AddChild(Object* child);

	virtual void SetColor(const glm::vec4& color) {}
	virtual void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {}

	virtual void Render(Shader& shader);
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
	glm::mat4 m_finalMatrix{ 1.0f };
	glm::mat3 m_normalMatrix{ 1.0f };

	std::string m_tag;
	Transform m_transform;

	Object* m_parent{ nullptr };
	std::vector<Object*> m_children;

};