#pragma once
#include "globalIncludes.hpp"
class Camera
{
public:
	GLFWwindow* window;

	glm::vec2 direction;
	glm::vec3 cameraPos;
	glm::vec2 rotation;
	bool firstMouse = true;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float lastX = 1920.f / 2.0;
	float lastY = 1080 / 2.0;
	glm::vec3 cameraFront;
	// timing
	glm::vec3 velocity;
	glm::vec4 backs;
	void update()
	{
		double xpos, ypos;
		glfwGetCursorPos(window,&xpos, &ypos);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - 960;
		float yoffset = 540 - ypos; // reversed since y-coordinates go from bottom to top

		float sensitivity = 0.1f; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped

		if (pitch > 89.f)
			pitch = 89.f;
		if (pitch < -89.f)
			pitch = -89.f;
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		backs.x = cos(glm::radians(yaw));
		backs.y =  sin(glm::radians(yaw));
		backs.z = cos(glm::radians(yaw+90));
		backs.w = sin(glm::radians(yaw+90));


		cameraFront = glm::normalize(front);
		direction.x = yaw;
		glfwSetCursorPos(window, 960, 540);
		cameraPos += velocity;
		velocity = { 0,0,0 };
	}

};