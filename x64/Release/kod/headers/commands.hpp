#pragma once
#include "globalIncludes.hpp"
#include "map.h"
int load(const char* path, glm::vec3 size);
int save(const char* path, glm::vec3 size);
int saveLast();
int changeFps(int fps);
int changeDist(int dist);
void commands(bool stop);