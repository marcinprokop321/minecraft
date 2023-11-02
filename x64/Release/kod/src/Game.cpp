#include "Game.hpp"
#include "globalIncludes.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
bool canupdate = true;
void game::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void game::update()
{

		string frames;
		double currentTime = glfwGetTime();
		frameCount++;
		if (currentTime - previousTime >= 1.0)
		{
			frames = to_string(frameCount);
			frameCount = 0;
			previousTime = currentTime;
			//system("cls");
			cout << "Position:   " << player->pos.x- 4096<< "   " << player->pos.y << "   " << player->pos.z - 4096 << "    FPS:" << frames << "   CHUNKS:" << map1.chunkstoLoad.size()<< "\n";
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//loop
		//imgui
		deltatime();
		processInput(window);
		map1.refresh();
		collision();
		player->update();
		glm::mat4 projection = glm::perspective(glm::radians(FOV_HORIZONTAL), (float)mode->width / (float)mode->height, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		view = glm::lookAt(player->camera.cameraPos,player->camera.cameraPos + player->camera.cameraFront, cameraUp);
		ourShader.setMat4("view", view);
		map1.Draw(&ourShader);
		for (unsigned int i = 0; i < map1.objects.size(); i++)
		{
			map1.objects[i]->draw(&ourShader);
		}
		glfwSwapBuffers(window);
	
}
game::game()
{

	cout << "FPS:";
	cin >> fps;
	cout << "MONITOR:";
	cin >> monitor;
	cout << "SEED:";
	cin >> seed1;
	
	map1.seed = seed1;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int count = 2;
	monitors = glfwGetMonitors(&count);
mode = glfwGetVideoMode(monitors[monitor]);
	window = glfwCreateWindow(mode->width, mode->height, "LearnOpenGL", monitors[monitor], NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	loadtextures();
	map1.player.load(window);
	map1.load(32, 32);
	guiShader.load("shaders/shadervs1.vs",
		"shaders/shaderfs1.fs");
	//defShader.load("C:/Users/Admin/source/repos/Project1/Project1/shaders/default.vs",
		//"C:/Users/Admin/source/repos/Project1/Project1/shaders/defaultf.fs");
	ourShader.load("shaders/shadervs.vs",
		"shaders/shaderfs.fs"
		, "shaders/gomentry.gs");
	//player->map1.objects.push_back(player->playermodel);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glEnable(GL_TEXTURE_3D);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(window, 960.f, 540);
	glfwSwapInterval(fps);
	glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
	textures[0]->bind(0);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
	player = &map1.player;
	map1.player.deltaTime = &deltaTime;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
	ourShader.use();
	deltaTime = 0;
	lastFrame5 = 0;
	deltatime();
}
void game::collision()
{


	glm::ivec3 col;
	glm::ivec3 boundry = player->pos + player->velocity;
	if (!boundry.x)
		player->velocity.x = 0;
	if (!boundry.z)
		player->velocity.z = 0;
		//x
		Chunk* chunk= map1.chunkstoLoad[map1.chunkstoLoad.size() / 2] ;
		glm::fvec2 pos = map1.chunkstoLoad[map1.chunkstoLoad.size()/2]->pos;
		col = { int(player->pos.x + player->velocity.x) - (pos.x * 64), player->pos.y, int(player->pos.z) - (pos.y * 64) };
		if (col.x < 0)
		{
			chunk= map1.chunkstoLoad[(map1.chunkstoLoad.size() / 2) - (player->renderDist * 2)];
			col.x += 64;
		}
		else if (col.x > 63)
		{
			chunk =map1.chunkstoLoad[(map1.chunkstoLoad.size() / 2) + (player->renderDist * 2)];
			col.x -= 64;
		}
		if (chunk->maparray[col.x + width1 * (col.y + height1 * col.z)] && chunk->maparray[col.x + width1 * (col.y + height1 * col.z)] !=4)
			player->velocity.x = abs(int(col.x) - col.x);
		//y
		chunk = map1.chunkstoLoad[map1.chunkstoLoad.size() / 2];
		 pos = map1.chunkstoLoad[map1.chunkstoLoad.size() / 2]->pos;
		col = { int(player->pos.x) - (pos.x * 64) ,player->pos.y + player->velocity.y, int(player->pos.z) - (pos.y * 64) };
		if (chunk->maparray[col.x + width1 * (col.y + height1 * col.z)] && chunk->maparray[col.x + width1 * (col.y + height1 * col.z)] != 4)
			player->velocity.y = abs(int(col.y) - col.y);

		//z
		chunk = map1.chunkstoLoad[map1.chunkstoLoad.size() / 2];
		pos = map1.chunkstoLoad[map1.chunkstoLoad.size() / 2]->pos;
		col = { int(player->pos.x) - (pos.x * 64),player->pos.y, int(player->pos.z + player->velocity.z) - (pos.y * 64) };
		if (col.z < 0)
		{
			chunk = map1.chunkstoLoad[(map1.chunkstoLoad.size() / 2) - 1];
			col.z += 64;
		}
		else if (col.z > 63)
		{
			chunk = map1.chunkstoLoad[(map1.chunkstoLoad.size() / 2) + 1];
			col.z -= 64;
		}
		if (chunk->maparray[col.x + width1 * (col.y + height1 * col.z)] && chunk->maparray[col.x + width1 * (col.y + height1 * col.z)] != 4)
			player->velocity.z = abs(int(col.z) - col.z);
	
}

void game::updateplaceRay()
{
	float fDistance = 0.0f;
	glm::vec3 intersection;
	float fMaxDistance = 5.0f;
	glm::fvec3 past;
	Chunk* pastc;
	Chunk *chun = map1.chunkstoLoad[map1.chunkstoLoad.size() / 2];
	glm::ivec3 blok = { 0,0,0 };
	isend = 1;
	while (fDistance < fMaxDistance)
	{
		placeblock1 = blok;
		placechunk1 = chun;
		intersection.x = (player->camera.cameraPos.x) + (fDistance * player->camera.cameraFront.x);
		intersection.z = (player->camera.cameraPos.z ) + (fDistance * player->camera.cameraFront.z);
		intersection.y = player->camera.cameraPos.y + (fDistance * player->camera.cameraFront.y);
		blok = { int(intersection.x) % 64,int(intersection.y),int(intersection.z) % 64 };
		int intersectx = intersection.x / 64; int intersecty = intersection.z / 64;
		if(intersecty<chun->pos.y)
			chun = map1.chunkstoLoad[(map1.chunkstoLoad.size() / 2)-1];
		if (intersecty > chun->pos.y)
			chun = map1.chunkstoLoad[(map1.chunkstoLoad.size() / 2) + 1];
		if (intersectx < chun->pos.x)
			chun = map1.chunkstoLoad[(map1.chunkstoLoad.size() / 2) - (player->renderDist * 2)];
		if (intersectx > chun->pos.x)
			chun = map1.chunkstoLoad[(map1.chunkstoLoad.size() / 2) + (player->renderDist * 2)];
		if (chun==nullptr)
			break;
		if (chun->maparray[blok.x + width1 * (blok.y + height1 * blok.z)] != 0)
		{
			placeblock = blok;
			placechunk = chun;
			isend = 0;
			break;
		}

		fDistance += 0.2;
	}
}
void game::deltatime()
{
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame5;
	lastFrame5 = currentFrame;
}
