#pragma once
#include "Object.h"
#include "globalIncludes.hpp"
struct Chunk
{
public:
    unsigned char maparray[64*64*64];
    glm::ivec2 pos;
    unsigned char Biome;
    std::vector<float> vertice1;
};
