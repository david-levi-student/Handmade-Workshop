#pragma once
#include "GLAD/gl.h"
#include <glm.hpp>
#include "Buffer.h"
#include "Object.h"

//TODO - Refine class such that it follows newer design
//TODO - Add support for spot, directional and point lights

class Light : public Object
{

public:

	static int GetTotalLights();

	Light(const std::string& tag, GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);
	virtual ~Light();

	void SetAttenuationLinear(GLfloat linear);
	void SetAttenuationConstant(GLfloat constant);
	void SetAttenuationQuadratic(GLfloat quadratic);
	void SetAttenuation(GLfloat constant, GLfloat linear, GLfloat quadratic);

	void SetAmbient(const glm::vec3& ambient);
	void SetAmbient(GLfloat r, GLfloat g, GLfloat b);

	void SetDiffuse(const glm::vec3& diffuse);
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);

	void SetSpecular(const glm::vec3& specular);
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b);

	virtual void Render(Shader& shader); /*debug only*/
	virtual void Update(GLfloat deltaTime) { /*debug only*/ }
	virtual void SendToShader(Shader& shader);

private:

	static GLuint s_totalLights;

	GLuint m_lightNumber{ s_totalLights++ };

	GLfloat m_attenuationLinear{ 0.05f };
	GLfloat m_attenuationConstant{ 0.2f };
	GLfloat m_attenuationQuadratic{ 0.05f };

	glm::vec3 m_ambient{ 1.0f };
	glm::vec3 m_diffuse{ 1.0f };
	glm::vec3 m_specular{ 1.0f };

	Buffer m_buffer;

};