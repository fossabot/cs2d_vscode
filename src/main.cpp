#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.hpp"
#include "Managers/ResourceManager.hpp"
#include "Others/Game_Parameters.hpp"
#include "Others/Logger.hpp"
#include "Others/Timer.hpp"
#include "Managers/InputManager.hpp"
#include <memory>
#include <windows.h>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void character_callback(GLFWwindow *window, unsigned int codepoint);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

//Game_Parameters::LoadParameters();

std::unique_ptr<Game> cs2d(std::make_unique<Game>());

//Game cs2d(SCREEN_WIDTH, SCREEN_HEIGHT);

int nbFrames = 0;
int upFrames = 0;

int main(int argc, char *argv[])
{
	FreeConsole();
	//Logger::Start();
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT, "CS2D", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	glGetError(); // Call it once to catch glewInit()

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCharCallback(window, character_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPos(window, 1440 / 2, 900 / 2);

	// OpenGL configuration
	glViewport(0, 0, Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT);
	/*glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);*/
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glLineWidth(4.0F);

	Logger::StartApp();
	// Initialize game
	cs2d->Init();

#pragma region input
	for (int i = 0; i < 8; i++)
	{
		InputManager::mouseDown[i] = GLFW_PRESS;
		InputManager::mouseUp[i] = GLFW_RELEASE;
	}

	//32
	{
		InputManager::keyDown[32] = GLFW_PRESS;
		InputManager::keyUp[32] = GLFW_RELEASE;
	}
	//39
	{
		InputManager::keyDown[39] = GLFW_PRESS;
		InputManager::keyUp[39] = GLFW_RELEASE;
	}
	for (int i = 44; i < 58; i++)
	{
		InputManager::keyDown[i] = GLFW_PRESS;
		InputManager::keyUp[i] = GLFW_RELEASE;
	}
	//59
	{
		InputManager::keyDown[59] = GLFW_PRESS;
		InputManager::keyUp[59] = GLFW_RELEASE;
	}
	//61
	{
		InputManager::keyDown[61] = GLFW_PRESS;
		InputManager::keyUp[61] = GLFW_RELEASE;
	}
	for (int i = 65; i < 94; i++)
	{
		InputManager::keyDown[i] = GLFW_PRESS;
		InputManager::keyUp[i] = GLFW_RELEASE;
	}
	//96
	{
		InputManager::keyDown[96] = GLFW_PRESS;
		InputManager::keyUp[96] = GLFW_RELEASE;
	}
	for (int i = 161; i < 163; i++)
	{
		InputManager::keyDown[i] = GLFW_PRESS;
		InputManager::keyUp[i] = GLFW_RELEASE;
	}
	for (int i = 256; i < 349; i++)
	{
		InputManager::keyDown[i] = GLFW_PRESS;
		InputManager::keyUp[i] = GLFW_RELEASE;
	}
#pragma endregion
	// DeltaTime variables
	float lastFrame = 0.0F;
	float time = 0.0F;
	InputManager::m_fps = 0;
	int fps = 0;
	while (!glfwWindowShouldClose(window))
	{
		const float currentFrame = static_cast<float>(glfwGetTime());
		Timer::DeltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		time += Timer::DeltaTime;
		glfwPollEvents();
		nbFrames++;
		fps++;
		if (time >= 1.0F)
		{
			InputManager::m_fps = fps;
			time = 0.0F;
			fps = 0;
			//nbFrames = 0;
		}

#pragma region input_0
		int newState;
		//mouse
		for (int i = 0; i < 8; i++)
		{
			newState = glfwGetMouseButton(window, i);
			if (newState == GLFW_PRESS && InputManager::oldMouseDown[i] == GLFW_RELEASE)
			{
				InputManager::mouseDown[i] = true;
				InputManager::mousePress[i] = true;
			}
			InputManager::oldMouseDown[i] = newState;

			//newState = glfwGetMouseButton(window, i);
			if (newState == GLFW_RELEASE && InputManager::oldMouseUp[i] == GLFW_PRESS)
			{
				InputManager::mousePress[i] = false;
				InputManager::mouseUp[i] = true;
			}
			InputManager::oldMouseUp[i] = newState;
		}

		//32
		{
			newState = glfwGetKey(window, 32);
			if (newState == GLFW_PRESS && InputManager::oldKeyDown[32] == GLFW_RELEASE)
			{
				InputManager::keyDown[32] = true;
				InputManager::keyPress[32] = true;
			}
			InputManager::oldKeyDown[32] = newState;

			//newState = glfwGetMouseButton(window, i);
			if (newState == GLFW_RELEASE && InputManager::oldKeyUp[32] == GLFW_PRESS)
			{
				InputManager::keyPress[32] = false;
				InputManager::keyUp[32] = true;
			}
			InputManager::oldKeyUp[32] = newState;
		}
		//39
		{
			newState = glfwGetKey(window, 39);
			if (newState == GLFW_PRESS && InputManager::oldKeyDown[39] == GLFW_RELEASE)
			{
				InputManager::keyDown[39] = true;
				InputManager::keyPress[39] = true;
			}
			InputManager::oldKeyDown[39] = newState;

			//newState = glfwGetMouseButton(window, i);
			if (newState == GLFW_RELEASE && InputManager::oldKeyUp[39] == GLFW_PRESS)
			{
				InputManager::keyPress[39] = false;
				InputManager::keyUp[39] = true;
			}
			InputManager::oldKeyUp[39] = newState;
		}
		for (int i = 44; i < 58; i++)
		{
			newState = glfwGetKey(window, i);
			if (newState == GLFW_PRESS && InputManager::oldKeyDown[i] == GLFW_RELEASE)
			{
				InputManager::keyDown[i] = true;
				InputManager::keyPress[i] = true;
			}
			InputManager::oldKeyDown[i] = newState;

			//newState = glfwGetMouseButton(window, i);
			if (newState == GLFW_RELEASE && InputManager::oldKeyUp[i] == GLFW_PRESS)
			{
				InputManager::keyPress[i] = false;
				InputManager::keyUp[i] = true;
			}
			InputManager::oldKeyUp[i] = newState;
		}
		//59
		{
			newState = glfwGetKey(window, 59);
			if (newState == GLFW_PRESS && InputManager::oldKeyDown[59] == GLFW_RELEASE)
			{
				InputManager::keyDown[59] = true;
				InputManager::keyPress[59] = true;
			}
			InputManager::oldKeyDown[59] = newState;

			//newState = glfwGetMouseButton(window, i);
			if (newState == GLFW_RELEASE && InputManager::oldKeyUp[59] == GLFW_PRESS)
			{
				InputManager::keyPress[59] = false;
				InputManager::keyUp[59] = true;
			}
			InputManager::oldKeyUp[59] = newState;
		}
		//61
		{
			newState = glfwGetKey(window, 61);
			if (newState == GLFW_PRESS && InputManager::oldKeyDown[61] == GLFW_RELEASE)
			{
				InputManager::keyDown[61] = true;
				InputManager::keyPress[61] = true;
			}
			InputManager::oldKeyDown[61] = newState;

			//newState = glfwGetMouseButton(window, i);
			if (newState == GLFW_RELEASE && InputManager::oldKeyUp[61] == GLFW_PRESS)
			{
				InputManager::keyPress[61] = false;
				InputManager::keyUp[61] = true;
			}
			InputManager::oldKeyUp[61] = newState;
		}
		for (int i = 65; i < 94; i++)
		{
			newState = glfwGetKey(window, i);
			if (newState == GLFW_PRESS && InputManager::oldKeyDown[i] == GLFW_RELEASE)
			{
				InputManager::keyDown[i] = true;
				InputManager::keyPress[i] = true;
			}
			InputManager::oldKeyDown[i] = newState;

			//newState = glfwGetMouseButton(window, i);
			if (newState == GLFW_RELEASE && InputManager::oldKeyUp[i] == GLFW_PRESS)
			{
				InputManager::keyPress[i] = false;
				InputManager::keyUp[i] = true;
			}
			InputManager::oldKeyUp[i] = newState;
		}
		//96
		{
			newState = glfwGetKey(window, 96);
			if (newState == GLFW_PRESS && InputManager::oldKeyDown[96] == GLFW_RELEASE)
			{
				InputManager::keyDown[96] = true;
				InputManager::keyPress[96] = true;
			}
			InputManager::oldKeyDown[96] = newState;

			//newState = glfwGetMouseButton(window, i);
			if (newState == GLFW_RELEASE && InputManager::oldKeyUp[96] == GLFW_PRESS)
			{
				InputManager::keyPress[96] = false;
				InputManager::keyUp[96] = true;
			}
			InputManager::oldKeyUp[96] = newState;
		}
		for (int i = 161; i < 163; i++)
		{
			newState = glfwGetKey(window, i);
			if (newState == GLFW_PRESS && InputManager::oldKeyDown[i] == GLFW_RELEASE)
			{
				InputManager::keyDown[i] = true;
				InputManager::keyPress[i] = true;
			}
			InputManager::oldKeyDown[i] = newState;

			//newState = glfwGetMouseButton(window, i);
			if (newState == GLFW_RELEASE && InputManager::oldKeyUp[i] == GLFW_PRESS)
			{
				InputManager::keyPress[i] = false;
				InputManager::keyUp[i] = true;
			}
			InputManager::oldKeyUp[i] = newState;
		}
		for (int i = 256; i < 349; i++)
		{
			newState = glfwGetKey(window, i);
			if (newState == GLFW_PRESS && InputManager::oldKeyDown[i] == GLFW_RELEASE)
			{
				InputManager::keyDown[i] = true;
				InputManager::keyPress[i] = true;
			}
			InputManager::oldKeyDown[i] = newState;

			//newState = glfwGetMouseButton(window, i);
			if (newState == GLFW_RELEASE && InputManager::oldKeyUp[i] == GLFW_PRESS)
			{
				InputManager::keyPress[i] = false;
				InputManager::keyUp[i] = true;
			}
			InputManager::oldKeyUp[i] = newState;
		}

#pragma endregion
		// Manage user input
		cs2d->ProcessInput();
		//Logger::DebugLog(std::to_string(Game_Parameters::SCREEN_WIDTH));
		//Logger::DebugLog(std::to_string(Game_Parameters::SCREEN_HEIGHT));
		// Update Game state
		cs2d->Update();

		// Render
		glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cs2d->Render();

#pragma region input_1
		//mouse
		for (int i = 0; i < 8; i++)
		{
			InputManager::mouseDown[i] = false;
			InputManager::mouseUp[i] = false;
		}

		//32
		{
			InputManager::keyDown[32] = false;
			InputManager::keyUp[32] = false;
		}
		//39
		{
			InputManager::keyDown[39] = false;
			InputManager::keyUp[39] = false;
		}
		for (int i = 44; i < 58; i++)
		{
			InputManager::keyDown[i] = false;
			InputManager::keyUp[i] = false;
		}
		//59
		{
			InputManager::keyDown[59] = false;
			InputManager::keyUp[59] = false;
		}
		//61
		{
			InputManager::keyDown[61] = false;
			InputManager::keyUp[61] = false;
		}
		for (int i = 65; i < 94; i++)
		{
			InputManager::keyDown[i] = false;
			InputManager::keyUp[i] = false;
		}
		//96
		{
			InputManager::keyDown[96] = false;
			InputManager::keyUp[96] = false;
		}
		for (int i = 161; i < 163; i++)
		{
			InputManager::keyDown[i] = false;
			InputManager::keyUp[i] = false;
		}
		for (int i = 256; i < 349; i++)
		{
			InputManager::keyDown[i] = false;
			InputManager::keyUp[i] = false;
		}
#pragma endregion
		glfwSwapBuffers(window);
	}

	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();
	glfwDestroyWindow(window);
	glfwTerminate();
	//Logger::Stop();
	return 0;
}
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	/*if (action == GLFW_PRESS)
	{
	}
	else if (action == GLFW_RELEASE)
	{
	}*/
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	InputManager::mousePos = Vector2(static_cast<int>(xpos), static_cast<int>(ypos));
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	if (action == GLFW_RELEASE && upFrames != nbFrames)
	{
		//Logger::DebugLog("frame no: " + std::to_string(nbFrames) + "  up");
		InputManager::onMouseUp(button);
	}
	else if (action == GLFW_PRESS)
	{
		//Logger::DebugLog("frame no: " + std::to_string(nbFrames) + "  down");
		InputManager::onMouseDown(button);
		upFrames = nbFrames;
	}
}

void character_callback(GLFWwindow *window, unsigned int codepoint)
{
	InputManager::keycode = codepoint;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	//Logger::DebugLog(std::to_string(yoffset));
	InputManager::scroll = Vector2(static_cast<float>(xoffset), static_cast<float>(yoffset));
	InputManager::scrollYPressed = true;
}