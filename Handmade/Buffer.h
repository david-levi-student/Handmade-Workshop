#pragma once
#include <array>
#include <map>
#include <string>
#include "GLAD/gl.h"

class Buffer
{

public:

	enum class Fill
	{
		Once = GL_STATIC_DRAW,
		Ongoing = GL_DYNAMIC_DRAW
	};

	enum class ComponentSize
	{
		XY = 2,
		XYZ = 3,
		XYZW = 4,
		RGB = 3,
		RGBA = 4,
		UV = 2
	};

	enum class DataType
	{
		IntData = GL_INT,
		FloatData = GL_FLOAT,
		DoubleData = GL_DOUBLE,
		UintData = GL_UNSIGNED_INT
	};

	enum class VBO
	{
		VertexBuffer,
		ColorBuffer,
		TextureBuffer,
		NormalBuffer
	};

	enum class RenderMode
	{
		Lines = GL_LINES,
		Points = GL_POINTS,
		Triangles = GL_TRIANGLES,
		LineLoop = GL_LINE_LOOP,
		LineStrip = GL_LINE_STRIP,
		TriangleFan = GL_TRIANGLE_FAN
	};

	enum class RenderStyle
	{
		Shaded = GL_FILL,
		Polygonal = GL_LINE
	};

	enum class Culling
	{
		None = 0,
		BackFace = GL_BACK,
		FrontFace = GL_FRONT,
	};

	static void SetPointSize(GLfloat size);
	static void SetLineWidth(GLfloat lineWidth);
	static void SetCullingMode(Culling culling);
	static void Destroy(const std::string& tag = "");
	static void SetRenderStyle(RenderStyle renderStyle);

	Buffer(const std::string& tag = "",
		GLsizei totalVertices = 0, bool hasEBO = false);

	const std::string& GetTag() const;
	void SetBuffer(const std::string& tag);

	void FillEBO(const GLuint* data,
		GLsizeiptr bufferSize, Fill fill = Fill::Once);
	void FillVBO(VBO vbo, const void* data,
		GLsizeiptr bufferSize, Fill fill = Fill::Once);

	void AppendEBO(const GLuint* data,
		GLsizeiptr size, GLuint offset);
	void AppendVBO(VBO vbo,
		const void* data, GLsizeiptr size, GLuint offset);

	void LinkEBO();
	void LinkVBO(GLint attributeID,
		VBO vbo, ComponentSize componentSize, DataType dataType);

	void Render(RenderMode renderMode,
		GLuint index = 0, GLuint totalRenderVertices = 0);

private:

	GLuint m_VAO = 0;
	GLuint m_EBO = 0;
	std::array<GLuint, 4> m_VBOs = { 0, 0, 0, 0 };

	bool m_hasEBO;
	std::string m_tag;
	GLsizei m_totalVertices;

	static std::map<std::string, Buffer> s_buffers;

};