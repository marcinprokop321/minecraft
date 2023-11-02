
using namespace std;

#include "Game.hpp"
game Game1;
void scroll(GLFWwindow* a, double x, double y)
{
	if (!Game1.canupdate)
		return;
	if (y < 0)
		Game1.player->witchblock--;
	if (y > 0)
		Game1.player->witchblock++;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void window_focus_callback(GLFWwindow* window, int focused)
{
	if (focused)
	{
		Game1.canupdate = true;
	}
	else
	{
		Game1.canupdate = false;
	}
}
void playerclick(GLFWwindow* window, int button, int action, int mods)
{
	if (!Game1.canupdate)
		return;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		Game1.updateplaceRay();
		if (!Game1.isend &&Game1.placeblock1.y>-1)
		{
			Game1.placechunk1->maparray[Game1.placeblock1.x + width1 * (Game1.placeblock1.y + height1 * Game1.placeblock1.z)] = Game1.player->witchblock;
			cout << "klik";
			cout << Game1.placeblock1.y << "\n";
		}
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		Game1.updateplaceRay();
		if (!Game1.isend&&Game1.placeblock.y>-1)
		{
			glm::ivec3 post = Game1.player->pos;
			if (post != Game1.placeblock)
				Game1.placechunk->maparray[Game1.placeblock.x + width1 * (Game1.placeblock.y + height1 * Game1.placeblock.z)] = 0;
		}
	}
}
int main() 
{
	glfwSetScrollCallback(Game1.window, scroll);
	glfwSetMouseButtonCallback(Game1.window, playerclick);
	glfwSetWindowFocusCallback(Game1.window, window_focus_callback);
	while (!glfwWindowShouldClose(Game1.window))
	{
		if (Game1.canupdate)
		{
			Game1.update();
		}
		else
		{
			Game1.deltaTime = 0;
			Game1.lastFrame5 = 0;
			Game1.deltatime();
		}
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}