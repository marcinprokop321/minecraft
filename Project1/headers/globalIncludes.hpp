#pragma once
#include <iostream>
#include <string>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <thread>
#include "texture.h"
#include "vertices.hpp"
#include "perlin.hpp" 
#include "shader_s.h"
#include "Object.h"
#include "Chunk.h"
#include <stdint.h>
#include <stddef.h>
#include <unordered_map>
constexpr float playerspeed = 0.1;
constexpr float gravitation = 0.1;
constexpr float PI = 3.141592653589793116f;
constexpr float FOV_HORIZONTAL = 90;
constexpr float FOV_VERTICAL = 58.75f;
constexpr double CAMERA_SPEED = 0.625;
static unsigned char width1 = 64, lenght1 = 64;
static unsigned short  height1 = 64;
struct Biome
{
	int weather;
	glm::vec3 watercolor;
	float rarity;
};
static std::string vectos(glm::ivec2 vec) {
	return string(to_string(vec.x) + to_string(vec.y));
}

constexpr 	Biome biomes[16]= { 1,glm::vec3(0,0,1),1 };
template <typename T>
T clip(const T& n, const T& lower, const T& upper) {
	return std::max(lower, std::min(n, upper));
}
static float get_degrees(float i_degrees)
{
	//Thank you, Stackoverflow!
	return static_cast<float>(fmod(360 + fmod(i_degrees, 360), 360));
}
static float deg_to_rad(float i_degrees)
{
	//After googling I found out that smart people use radians because of calculus.
	//I don't know what that word means so I'll keep using degrees.
	return PI * i_degrees / 180;
}
static 	Texture3D* textures[1];
static 	Texture* textures1[1];
static std::vector<int> cubeVertices;
static void loadtextures()
{
    srand(time(NULL));
	std::string paths[50];
	for (int i = 1; i < 51; i++)
		paths[i - 1] = std::string("res/blocks/block" + std::to_string(i) + ".png");
    textures[0] = new Texture3D(paths, glm::vec3{16,16,50},0);
	textures1[0] = new Texture("res/blocks.png", 0);
}
template <typename T>
struct vect3
{
	T x;
	T y;
	T z;
};
#define vecti3 vect3<int>
template <typename T>
struct vect2
{
	T x;
	T y;
};
#define vecti2 vect2<int>