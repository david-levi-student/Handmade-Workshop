#pragma once
#include "Buffer.h"
#include "Model.h"
#include "Object.h"
#include "Shader.h"
#include "Tile.h"

class Axes : public Object
{

public:

	Axes(const std::string& filenameModel);
	Axes(GLint size = 15, GLfloat lineWidth = 5.0f);
	virtual ~Axes();

	void SetSize(GLint size);
	void SetLineWidth(GLfloat lineWidth);

	const glm::vec3& GetArrowTipPositionX() const;
	const glm::vec3& GetArrowTipPositionY() const;
	const glm::vec3& GetArrowTipPositionZ() const;

	virtual void Render(Shader& shader);
	virtual void Update(GLfloat deltaTime) {}
	virtual void SendToShader(Shader& shader) {}

private:

	void Create();

	GLint m_size{ 0 };
	GLfloat m_lineWidth{ 0.0f };
	bool m_isPrimitive{ false };

	glm::vec3 m_arrowTipPositionX{ 0.0f };
	glm::vec3 m_arrowTipPositionY{ 0.0f };
	glm::vec3 m_arrowTipPositionZ{ 0.0f };

	Model m_model;
	Buffer m_buffer;

	static GLuint s_totalObjects;

};