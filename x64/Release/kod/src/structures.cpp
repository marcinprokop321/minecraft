#include "map.h"
#include "structures.h"
void Map::generateStruct(int ID, int x, int y, int z,Chunk* chunk)
{
unsigned char* tempmap = structures[ID]->map;
	glm::ivec3 size = { structures[ID]->x,structures[ID]->y,structures[ID]->z };
	
		glm::ivec3 startpos = glm::ivec3{ x - int(size.x ),y,z - int(size.z ) };
		for (int xi = 0; xi <  size.x; xi++)
			for (int yi = 0; yi <  size.y; yi++)
				for (int zi = 0; zi <  size.z; zi++)
				{
					
					if((xi + startpos.x) + width1 * ((yi + startpos.y) + height1 * (zi + startpos.z))>=0&&
						(xi + startpos.x) + width1 * ((yi + startpos.y) + height1 * (zi + startpos.z))< 262144)
						if(tempmap[(xi)+size.x * ((yi)+size.y * ((zi)))]!=0)
						chunk->maparray[(xi + startpos.x) + width1 * ((yi + startpos.y) + height1 * (zi + startpos.z))] = tempmap[(xi) + size.x * ((yi ) + size.y * ((zi )))];
						
				}
	

}
void Map::loadStructs()
{
	//tree
	structure *tree= new structure;
	tree->map = new unsigned char[150];
	tree->x = 5; tree->y = 6; tree->z = 5;
	for (int x = 0; x < 5; x++)
		for (int y = 0; y < 6; y++)
			for (int z = 0; z < 5; z++)
				tree->map[x + 5 * (y + 6 * (z))] = 0;
	for (int x = 0; x < 5; x++)
		for (int y = 2; y < 4; y++)
			for (int z = 0; z < 5; z++)
			{
				tree->map[x + 5 * (y + 6 * (z))] = 5;
			}
	for (int x = 1; x < 4; x++)
		for (int y = 4; y < 6; y++)
			for (int z = 1; z < 4; z++)
			{
				tree->map[x + 5 * (y + 6 * (z))] = 5;
			}
	for (int y = 0; y < 5; y++)
		tree->map[2 + 5 * (y + 6 * (2))] = 42;
	structures[0] = tree;
}