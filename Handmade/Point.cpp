#include "Point.h"

Point::Point(const std::string& tag, GLfloat pointSize, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	: Object(tag), m_buffer(tag, 1), m_pointSize(pointSize)
{
	glm::vec3 vertex = glm::vec3(0.0f);
	glm::vec4 color = glm::vec4(r, g, b, a);

	m_buffer.FillVBO(Buffer::VBO::VertexBuffer, &vertex.x, sizeof(vertex), Buffer::Fill::Ongoing);
	m_buffer.FillVBO(Buffer::VBO::ColorBuffer, &color.r, sizeof(color), Buffer::Fill::Ongoing);
}
//======================================================================================================
Point::~Point()
{
	m_buffer.Destroy(m_tag);
}
//======================================================================================================
void Point::SetColor(const glm::vec4& color)
{
	SetColor(color.r, color.g, color.b, color.a);
}
//======================================================================================================
void Point::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	glm::vec4 color = glm::vec4(r, g, b, a);
	m_buffer.FillVBO(Buffer::VBO::ColorBuffer, &color.r, sizeof(color), Buffer::Fill::Ongoing);
	m_color = glm::vec4(r, g, b, a);
}
//======================================================================================================
void Point::Render(Shader& shader)
{
	//TODO - Find a way to do this only once
	m_buffer.LinkVBO(shader.GetAttributeID("vertexIn"),
		Buffer::VBO::VertexBuffer, Buffer::ComponentSize::XYZ, Buffer::DataType::FloatData);
	m_buffer.LinkVBO(shader.GetAttributeID("colorIn"),
		Buffer::VBO::ColorBuffer, Buffer::ComponentSize::RGBA, Buffer::DataType::FloatData);

	Buffer::SetPointSize(m_pointSize);
	m_buffer.Render(Buffer::RenderMode::Points);
}