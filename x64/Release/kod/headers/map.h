#pragma once
#include "globalIncludes.hpp"
#include "player.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include "structures.h"
class Map
{
public:
	Map()
	{
		NULL;
	}
	void loadBiomes();
	Player player;
	std::unordered_map<std::string, Chunk*> chunks;
	siv::PerlinNoise::seed_type seed;
	vector<Chunk*> chunkstoLoad;
	std::vector <Object*> objects;
	void Draw(Shader *ourShader);
	void load(int width, int lenght);
	void refresh();
	void generateStruct(int ID,int x,int y,int z,Chunk *chunk);
	structure* structures[10];
	void loadStructs();
	void drawchunk(Shader* ourShader, Chunk* chunk);
	void drawwater(Shader* ourShader, Chunk* chunk);
	void generate(long long int x, long long int y);



};