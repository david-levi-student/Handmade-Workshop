#pragma once
#include "Buffer.h"
#include "Object.h"

class Circle : public Object
{

public:

	Circle(Object* parent, GLfloat radius = 1.0f, GLuint slices = 25,
		GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f);
	virtual ~Circle();

	void SetRadius(GLfloat radius);
	
	virtual void SetColor(const glm::vec4& color);
	virtual void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	virtual void Render(Shader& shader);
	virtual void Update(GLfloat deltaTime) {}
	virtual void SendToShader(Shader& shader) {}

private:

	GLuint m_slices;
	GLfloat m_radius;
	Buffer m_buffer;

};