#include "map.h"
void Map::Draw(Shader *ourShader)
{
	for (auto& a : chunkstoLoad)
	{
		drawchunk(ourShader, a);
	}
	for (auto& a : chunkstoLoad)
	{

			drawwater(ourShader, a);
	}
}
void Map::load(int width, int lenght)
{
	loadStructs();
	glm::ivec2 randsp = { rand() % 64 + 1,rand() % 64 + 1 };
	glm::ivec2 spawn = { 4096 + randsp.x, 4096+ randsp.y };
	glm::ivec2 spawnc = { spawn.x / 64,spawn.y / 64 };
	int zasieg =6;
	
	{
		for (int x = -zasieg; x < zasieg + 1; x++)
		{
			for (int y = -zasieg; y < zasieg + 1; y++)
			{
				if (!chunks.contains(vectos({ spawnc.x + x, spawnc.y + y })))
					generate(spawnc.x + x, spawnc.y + y);
			}
		}
	}
	if (!chunks.contains(vectos({ spawnc.x , spawnc.y  })))
		generate(spawnc.x, spawnc.y );
	for (int i = 5; i < 64; i++)
	{
		if (!chunks[vectos(spawnc)]->maparray[(spawn.x%64) + width1 * ((i) + height1 * (spawn.y % 64))])
		{
			player.pos = { spawn.x,i,spawn.y };
			std::cout << i << "!!!";
			break;
		}
	}
}
void Map::refresh()
{
	chunkstoLoad.clear();
	glm::i32vec2 temp1 = { int(player.pos.x / 64),int(player.pos.z / 64)};
	for (int x = -player.renderDist; x < player.renderDist + 1; x++)
	{
		for (int y = -player.renderDist; y < player.renderDist + 1; y++)
		{

				
					float lam = sqrt((abs(x) * abs(x)) + (abs(y) * abs(y)));
					if ((lam) <= player.renderDist)
					{
						glm::vec2 temp2 = { temp1.x + x, temp1.y + y };
						if (!chunks.contains(vectos(temp2)))
							generate(temp1.x + x, temp1.y + y);
						chunkstoLoad.push_back(chunks[vectos(temp2)]);
					}
				
			
		}
	}

}