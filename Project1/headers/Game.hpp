#pragma once
#include "globalIncludes.hpp"
#include "Chunk.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "commands.hpp"
#include "player.h"
#include "map.h"

class game
{
public:
	game();
	 float currentFrame;
	 float deltaTime;
	 float lastFrame5;
	 void deltatime();
	double previousTime = glfwGetTime();
	int frameCount = 0;
	Map map1;
	Shader ourShader;
	Shader guiShader;
	// defShader;
    GLFWwindow* window;
	void update();
	void render();
	void collision();
	Player* player;
	bool canupdate = true;
	void updateplaceRay();
	Chunk* placechunk;
	glm::ivec3 placeblock = { -1,-1 ,-1 };
	Chunk* placechunk1;
	bool isend;
	glm::ivec3 placeblock1 = { -1,-1 ,-1 };
	void processInput(GLFWwindow* window);
	const GLFWvidmode* mode;
	GLFWmonitor** monitors;
	glm::mat4 view = glm::mat4(1.0f);
	glm::fvec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    int monitor;
    int fps;
    siv::PerlinNoise::seed_type seed1;
};