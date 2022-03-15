#pragma once
#include <string>
#include "GLAD/gl.h"
#include <glm.hpp>
#include "Buffer.h"
#include "Object.h"
#include "Texture.h"

class Tile : public Object
{

public:

	Tile(Object* parent, const std::string& filename,
		GLfloat width = 1.0f, GLfloat height = 1.0f,
		GLuint spriteSheetCol = 1, GLuint spriteSheetRow = 1);
	virtual ~Tile();

	bool IsAnimationDead() const;
	bool IsAnimationLooping() const;

	void IsAnimated(bool flag);
	void IsAnimationLooping(bool flag);

	void SetTileIndex(GLuint tileIndex);
	void SetTileIndex(GLuint column, GLuint row);
	void SetAnimationVelocity(GLfloat velocity);

	void SetDimension(const glm::vec3& dimension);
	void SetDimension(GLfloat width, GLfloat height);
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	virtual void Render(Shader& shader);
	virtual void Update(GLfloat deltaTime) {}
	virtual void SendToShader(Shader& shader);

private:

	bool m_isAnimated = false;
	bool m_isAnimationDead = false;
	bool m_isAnimationLooping = false;
	bool m_isAnimationLoopFinal = false;

	GLuint m_tileIndex{ 0 };
	GLuint m_spriteSheetCol;
	GLuint m_spriteSheetRow;
	GLfloat m_animationVelocity{ 0.1f };

	Buffer m_buffer;
	Texture m_texture;

	glm::vec2 m_dimension;
	glm::vec4 m_color{ 1.0f };

	const GLuint CORNERS = 4;
	const GLuint VERTICES_PER_TILE = 6;

};