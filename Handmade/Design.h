#pragma once
#include <deque>
#include <memory>
#include <vector>
#include <glm.hpp>
#include "Audio.h"
#include "Axes.h"
#include "Circle.h"
#include "Cuboid.h"
#include "FreeCamera.h"
#include "Grid.h"
#include "Light.h"
#include "Model.h"
#include "Object.h"
#include "Quad.h"
#include "Sphere.h"
#include "Shader.h"
#include "State.h"
#include "Text.h"

const auto MINOR = 0.15f;
const auto MAJOR = 0.85f;
const auto FONT_SIZE = 18.0f;
const auto UI_PADDING = 2.0f;
const auto MENU_BAR_HEIGHT = 24;
const auto MAX_CONSOLE_LOG_SIZE = 1000;

class Design : public State
{

public:

	Design() {}
	virtual ~Design() {}

	virtual bool OnEnter();
	virtual State* Update(int deltaTime);
	virtual bool Render();
	virtual void OnExit();

private:

	void RenderMenu();
	void RenderConsoleWindow();
	void RenderHierarchyWindow();
	void RenderPropertiesWindow();

	GLint m_minorWidth{ 0 };
	GLint m_majorWidth{ 0 };
	GLint m_minorHeight{ 0 };
	GLint m_majorHeight{ 0 };
	
	bool m_isStateComplete{ false };

	glm::ivec2 m_resolution{ 0U };
	glm::vec3 m_sceneRotation{ 45.0f, -30.0f, 0.0f };

	std::unique_ptr<Grid> m_grid;
	std::unique_ptr<Axes> m_axes;

	std::unique_ptr<Text> m_topText;
	std::unique_ptr<Text> m_bottomText;
	std::unique_ptr<Text> m_axesLabelText;

	std::unique_ptr<Shader> m_mainShader;
	std::unique_ptr<Shader> m_textShader;
	std::unique_ptr<Shader> m_lightShader;
	std::unique_ptr<Shader> m_testShader;

	std::unique_ptr<FreeCamera> m_sceneCamera;

	//For current testing===============================================
	/*std::unique_ptr<Audio> m_audio1;
	std::unique_ptr<Audio> m_audio2;
	std::unique_ptr<Audio> m_audio3;*/

	std::unique_ptr<Light> m_light;
	
	//Generic object (for testing)
	Object* m_activeObject{ nullptr };
	std::vector<std::unique_ptr<Object>> m_objects;

	//std::unique_ptr<Tile> m_labelX;
	//std::unique_ptr<Tile> m_labelY;
	//std::unique_ptr<Tile> m_labelZ;

	//Using static objects will enforce more copies being made 
	//especially if the vector container has not been reserved
	//Prefer to use smart pointer objects instead to avoid copies
	//std::vector<Text> m_text;
	//std::vector<Audio> m_audio;
	//==================================================================

	std::deque<std::string> m_consoleLog;

};