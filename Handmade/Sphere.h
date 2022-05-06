#pragma once
#include "GLAD/gl.h"
#include <glm.hpp>
#include "Buffer.h"
#include "Object.h"

class Sphere : public Object
{

public:

	static int GetTotalSpheres();

	Sphere(const std::string& tag, GLfloat radius = 1.0f, GLuint segments = 25, GLuint slices = 25,
		GLfloat r = 0.5f, GLfloat g = 0.5f, GLfloat b = 0.5f, GLfloat a = 1.0f);
	virtual ~Sphere();

	void SetRadius(GLfloat radius);

	virtual void SetColor(const glm::vec4& color);
	virtual void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	virtual void Render(Shader& shader);
	virtual void Update(GLfloat deltaTime) {}
	virtual void SendToShader(Shader& shader) {}

private:

	static int s_totalSpheres;

	Buffer m_buffer;
	GLuint m_slices;
	GLfloat m_radius;
	GLuint m_segments;

};