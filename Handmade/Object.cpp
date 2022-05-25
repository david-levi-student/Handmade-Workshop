#include <assert.h>
#include <deque>
#include "Object.h"
#include "Shader.h"

Object::Object(const std::string& tag) : m_tag(tag) {}
//======================================================================================================
bool Object::IsLit() const
{
	return m_isLit;
}
//======================================================================================================
bool Object::IsAlive() const
{
	return m_isAlive;
}
//======================================================================================================
bool Object::IsActive() const
{
	return m_isActive;
}
//======================================================================================================
bool Object::IsVisible() const
{
	return m_isVisible;
}
//======================================================================================================
bool Object::IsTextured() const
{
	return m_isTextured;
}
//======================================================================================================
void Object::IsLit(bool flag)
{
	m_isLit = flag;
}
//======================================================================================================
void Object::IsAlive(bool flag)
{
	m_isAlive = flag;
}
//======================================================================================================
void Object::IsActive(bool flag)
{
	m_isActive = flag;
}
//======================================================================================================
void Object::IsVisible(bool flag)
{
	m_isVisible = flag;
}
//======================================================================================================
void Object::IsTextured(bool flag)
{
	m_isTextured = flag;
}
//======================================================================================================
GLuint Object::GetPriority() const
{
	return m_priority;
}
//======================================================================================================
const std::string& Object::GetTag() const
{
	return m_tag;
}
//======================================================================================================
const glm::vec4& Object::GetColor() const
{
	return m_color;
}
//======================================================================================================
const std::vector<Object*>& Object::GetChildren() const
{
	return m_children;
}
//======================================================================================================
Transform& Object::GetTransform()
{
	return m_transform;
}
//======================================================================================================
void Object::SetPriority(GLuint priority)
{
	m_priority = priority;
}
//======================================================================================================
void Object::SetTag(const std::string& tag)
{
	m_tag = tag;
}
//======================================================================================================
void Object::AddChild(Object* child)
{
	assert(child->m_parent == nullptr);
	m_children.emplace_back(child);
	m_children.back()->m_parent = this;
}
//======================================================================================================
glm::mat4 Object::GetFinalMatrix()
{
	std::deque<glm::mat4> matrices;
	matrices.emplace_front(m_transform.GetMatrix());

	auto parent = m_parent;

	while (parent)
	{
		matrices.emplace_front(parent->GetTransform().GetMatrix());
		parent = parent->m_parent;
	}

	auto finalMatrix = glm::mat4(1.0f);

	for (auto& matrix : matrices)
	{
		finalMatrix *= matrix;
	}

	return finalMatrix;
}