#include <iostream>
#include <vector>
#include <gtc\matrix_transform.hpp>
#include "ScreenManager.h"
#include "ShaderManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
ScreenManager::ScreenManager()
{

	m_width = 0;
	m_height = 0;
	m_pixelsPerUnit = 0;
	
	m_windowHandle = 0;
	m_window = nullptr;
	m_context = 0;

	m_projectionUniformID = 0;
	
}
//------------------------------------------------------------------------------------------------------
//getter function that returns pixel scale value
//------------------------------------------------------------------------------------------------------
int ScreenManager::GetPixelsPerUnit()
{

	return m_pixelsPerUnit;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns Windows handle of SDL game window
//------------------------------------------------------------------------------------------------------
HWND ScreenManager::GetWindowHandle()
{

	return m_windowHandle;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns SDL game window
//------------------------------------------------------------------------------------------------------
SDL_Window* ScreenManager::GetWindow()
{

	return m_window;

}
//------------------------------------------------------------------------------------------------------
//getter function that creates screen size vector and returns it
//------------------------------------------------------------------------------------------------------
glm::vec2 ScreenManager::GetScreenSize()
{

	return glm::vec2(m_width, m_height);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns a pre-defined color value for clearing the screen
//------------------------------------------------------------------------------------------------------
void ScreenManager::SetClearColor(Color& color)
{

	glClearColor(color.R, color.G, color.B, color.A);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns projection matrix's shader uniform ID  
//------------------------------------------------------------------------------------------------------
void ScreenManager::SetProjectionUniformID(std::string uniformID)
{

	m_projectionUniformID = TheShader::Instance()->GetUniformID(uniformID.c_str());

}
//------------------------------------------------------------------------------------------------------
//setter function that sets up rectangular viewport section of screen 
//------------------------------------------------------------------------------------------------------
void ScreenManager::SetViewport(int x, int y, int width, int height)
{

	glViewport(x, y, width, height);

}
//------------------------------------------------------------------------------------------------------
//setter function that creates a 2D orthographic projection 
//------------------------------------------------------------------------------------------------------
void ScreenManager::Set2DScreen(ScreenOrigin2D screenOrigin)
{

	//disable Z-buffering because in
	//2D the depth buffer isn't needed 
	glDisable(GL_DEPTH_TEST);	

	//if screen origin passed is set as top left of screen 
	//create orthographic view so that Y is positive downward 
	if (screenOrigin == TOP_LEFT)
	{
		m_projectionMatrix = glm::ortho(0.0f, (float)m_width, (float)m_height, 0.0f);
	}

	//if screen origin passed is set as bottom left of screen 
	//create orthographic view so that Y is positive upward 
	else if (screenOrigin == BOTTOM_LEFT)
	{
		m_projectionMatrix = glm::ortho(0.0f, (float)m_width, 0.0f, (float)m_height);
	}

	//send projection matrix to vertex shader
	TheShader::Instance()->SetUniformMatrix(m_projectionUniformID, &m_projectionMatrix[0][0]);

}
//------------------------------------------------------------------------------------------------------
//setter function that creates a 3D perspective projection 
//------------------------------------------------------------------------------------------------------
void ScreenManager::Set3DScreen(float fieldOfView, float nearClip, float farClip)
{

	//enable Z-buffering so that vertices
	//are drawn in the correct order
	glEnable(GL_DEPTH_TEST);

	//determine the aspect ratio based on width and height of screen
	float aspectRatio = (float)m_width / (float)m_height;

	//create a 3D perspective projection using passed FOV angle, aspect ratio and clipping planes
	m_projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearClip, farClip);

	//send projection matrix to vertex shader
	TheShader::Instance()->SetUniformMatrix(m_projectionUniformID, &m_projectionMatrix[0][0]);

}
//------------------------------------------------------------------------------------------------------
//function that initializes the screen including the SDL, OpenGL and GLEW subsystems   
//------------------------------------------------------------------------------------------------------
bool ScreenManager::Initialize(const char* windowTitle, int width, int height, int pixelsPerUnit,
							   int major, int minor, bool compatibleContext, bool fullscreen)
{

	//initialize SDL subsystem by enabling the entire SDL package
	//if SDL initialization fails, display error message and return false
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL did not initialize properly." << std::endl;
		return false;
	}

	//set frame buffer attributes so that we have 32-bit color
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	//enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//set up anti-aliasing 
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	
	//assign OpenGL profile to compatibile or core profile based on flag passed 
	int profile = (compatibleContext) ? SDL_GL_CONTEXT_PROFILE_COMPATIBILITY
									  : SDL_GL_CONTEXT_PROFILE_CORE;

	//set OpenGL context and profile using values assigned earlier
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, profile);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);

	//assign normal window or fullscreen flag based on value passed
	Uint32 screenFlag = (fullscreen) ? SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN
		                             : SDL_WINDOW_OPENGL;

	//create a game window using caption, width, height and screen mode flag
	m_window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		                        width, height, screenFlag);

	//if game window could not be created, display error message and return false
	if (m_window == 0)
	{
		std::cout << "Game window could not be created." << std::endl;
		return false;
	}

	//create OpenGL context using SDL window created earlier
	m_context = SDL_GL_CreateContext(m_window);
	
	//if OpenGL context could not be created, display error message and return false
	if (m_context == 0)
	{
		std::cout << "OpenGL context " << major << "." << minor << " could not be created. The "
			         "context is either invalid or not supported by your graphics card." << std::endl;
		return false;
	}

	//variable to store window data in
	SDL_SysWMinfo systemInfo;

	//first store SDL version info
	SDL_VERSION(&systemInfo.version);

	//aquire main window data from SDL created game window
	SDL_GetWindowWMInfo(m_window, &systemInfo);

	//set GLEW flag to combat potential errors for core mode
	glewExperimental = GL_TRUE;

	//initialize GLEW and if it fails, display error message and return false
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW could not be initialized.";
		return false;
	}

	//enable vertical syncing so that screen monitor and frame buffer refresh rate are synchronized 
	//if there was an error setting this value, display error message and return false 
	if (SDL_GL_SetSwapInterval(1) == -1)
	{
		std::cout << "VSync not supported." << std::endl;
		return false;
	}
	
	//store width and height properties for later 
	//use when setting up 2D and 3D projections
	m_width = width;
	m_height = height;

	//store pixel scale value for use with 2D applications
	m_pixelsPerUnit = pixelsPerUnit;

	//store window handle for use with Windows specific functions
	m_windowHandle = systemInfo.info.win.window;

	//enable blending for transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that aquires and displays graphics card extensions
//------------------------------------------------------------------------------------------------------
void ScreenManager::DisplayExtensions()
{

	//variables to store the total extension amount
	//and each extension in string format
	GLint totalExtensions;
	std::vector<std::string> extensions;

	//get total amount of extensions from OpenGL
	glGetIntegerv(GL_NUM_EXTENSIONS, &totalExtensions);

	//loop through all extensions and store 
	//each one in the vector container
	for (GLint i = 0; i < totalExtensions; i++)
	{
		std::string temp = (const char*)glGetStringi(GL_EXTENSIONS, i);
		extensions.push_back(temp);
	}

	//display all graphics card supported extensions on the console window 
	system("cls");
	std::cout << "---------------------------------------------------------------" << std::endl;
	std::cout << "The following extensions are supported by your graphics card : " << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	//loop through all extensions and display them
	for (size_t j = 0; j < extensions.size(); j++)
	{
		std::cout << "Extension #" << j << " : " << extensions[j] << std::endl;
	}

}
//------------------------------------------------------------------------------------------------------
//function that aquires and displays OpenGL profile data
//------------------------------------------------------------------------------------------------------
void ScreenManager::DisplayGraphicsProfile()
{

	//create variables for storing OpenGL profile data and get the data from OpenGL
	std::string vendor = (const char*)(glGetString(GL_VENDOR));
	std::string renderer = (const char*)(glGetString(GL_RENDERER));
	std::string versionGL = (const char*)(glGetString(GL_VERSION));
	std::string versionGLSL = (const char*)(glGetString(GL_SHADING_LANGUAGE_VERSION));

	//display all OpenGL profile data on the console window
	system("cls");
	std::cout << "--------------------------------------------------------------------" << std::endl;
	std::cout << "Your graphics card profile is as follows : " << std::endl;
	std::cout << "--------------------------------------------------------------------" << std::endl;
	std::cout << "Graphics Card Vendor : " << vendor << std::endl;
	std::cout << "Graphics Card Model : " << renderer << std::endl;
	std::cout << "OpenGL Version : " << versionGL << std::endl;
	std::cout << "GLSL Version : " << versionGLSL << std::endl;

	//display all OpenGL supported versions on the console window 
	std::cout << "--------------------------------------------------------------------" << std::endl;
	std::cout << "The following OpenGL contexts are currently available : " << std::endl;
	std::cout << "--------------------------------------------------------------------" << std::endl;

	//call specific GLEW functions to check if OpenGL contexts are supported
	//these outcomes are based on what OpenGL context was configured previously
	if (GLEW_VERSION_1_1)   std::cout << "Version 1.1" << std::endl;
	if (GLEW_VERSION_1_2)   std::cout << "Version 1.2" << std::endl;
	if (GLEW_VERSION_1_2_1) std::cout << "Version 1.2.1" << std::endl;
	if (GLEW_VERSION_1_3)   std::cout << "Version 1.3" << std::endl;
	if (GLEW_VERSION_1_4)   std::cout << "Version 1.4" << std::endl;
	if (GLEW_VERSION_1_5)   std::cout << "Version 1.5" << std::endl;
	if (GLEW_VERSION_2_0)   std::cout << "Version 2.0" << std::endl;
	if (GLEW_VERSION_2_1)   std::cout << "Version 2.1" << std::endl;
	if (GLEW_VERSION_3_0)   std::cout << "Version 3.0" << std::endl;
	if (GLEW_VERSION_3_1)   std::cout << "Version 3.1" << std::endl;
	if (GLEW_VERSION_3_2)   std::cout << "Version 3.2" << std::endl;
	if (GLEW_VERSION_3_3)   std::cout << "Version 3.3" << std::endl;
	if (GLEW_VERSION_4_0)   std::cout << "Version 4.0" << std::endl;
	if (GLEW_VERSION_4_1)   std::cout << "Version 4.1" << std::endl;
	if (GLEW_VERSION_4_2)   std::cout << "Version 4.2" << std::endl;
	if (GLEW_VERSION_4_3)   std::cout << "Version 4.3" << std::endl;
	if (GLEW_VERSION_4_4)   std::cout << "Version 4.4" << std::endl;
	if (GLEW_VERSION_4_5)   std::cout << "Version 4.5" << std::endl;

}
//------------------------------------------------------------------------------------------------------
//function that clears the frame buffer
//------------------------------------------------------------------------------------------------------
void ScreenManager::Update()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
//------------------------------------------------------------------------------------------------------
//function that swaps the frame buffer
//------------------------------------------------------------------------------------------------------
void ScreenManager::Draw()
{

	SDL_GL_SwapWindow(m_window);

}
//------------------------------------------------------------------------------------------------------
//function that closes down SDL, OpenGL and destroys the game window
//------------------------------------------------------------------------------------------------------
void ScreenManager::ShutDown()
{

	//free OpenGL context
	SDL_GL_DeleteContext(m_context);

	//free game screen and window
	SDL_DestroyWindow(m_window);

	//shut down all SDL sub-systems
	SDL_Quit();

}