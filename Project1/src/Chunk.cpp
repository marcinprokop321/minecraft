#include "Chunk.h"
#include "globalIncludes.hpp"
#include "map.h"
void Map::drawchunk(Shader *ourShader,Chunk *chunk)
{
    unsigned int VAO1, VBO1;
    std::vector<float> vertice;
    std::unordered_map<std::string, Chunk*>::const_iterator right = chunks.find(vectos(glm::vec2{ chunk->pos.x + 1, chunk->pos.y }));
    std::unordered_map<std::string, Chunk*>::const_iterator left = chunks.find(vectos(glm::vec2{ chunk->pos.x - 1, chunk->pos.y }));
    std::unordered_map<std::string, Chunk*>::const_iterator front = chunks.find(vectos(glm::vec2{ chunk->pos.x , chunk->pos.y+1 }));
    std::unordered_map<std::string, Chunk*>::const_iterator back = chunks.find(vectos(glm::vec2{ chunk->pos.x, chunk->pos.y - 1 }));
    for (int x = 0; x < width1; x++)
    {
        for (int y = 0; y < height1; y++)
        {
            for (int z = 0; z < lenght1; z++)
            {
                int skrut = chunk->maparray[x+width1*(y+height1*z)];
                if (skrut)
                {
                    if (skrut == 4)
                    {
                        if (!chunk->maparray[x + width1 * ((y + 1) + height1 * z)])
                        {
                            chunk->vertice1.push_back(x);
                            chunk->vertice1.push_back(y);
                            chunk->vertice1.push_back(z);
                            chunk->vertice1.push_back(5);

                            chunk->vertice1.push_back(skrut);
                        }
                        continue;
                    }
                    bool aha9[6] = { 0,0,0,0,0,0 };
                    if ((chunk->maparray[x + width1 * ((y+1) + height1 * z)]|4) == 4)
                        aha9[5] = 1;
                    if (y && (chunk->maparray[x + width1 * ((y - 1) + height1 * z)]|4) ==4)
                        aha9[4] = 1;
                    //left
                    
                        if (x != (width1 - 1))
                        {
                            if ((chunk->maparray[(x + 1) + width1 * (y + height1 * z)] | 4) == 4)
                                aha9[3] = 1;
                        }

                        else
                        {
                            if (right != chunks.end() && (right->second->maparray[(x - 63) + width1 * (y + height1 * z)] | 4) == 4)
                                aha9[3] = 1;
                        }
                    
                    //right

                    
                        if (x)
                        {
                            if ((chunk->maparray[(x - 1) + width1 * (y + height1 * z)] | 4) == 4)
                                aha9[2] = 1;
                        }

                        else
                        {
                            if (left != chunks.end() && (left->second->maparray[(x + 63) + width1 * (y + height1 * z)] | 4) == 4)
                                aha9[2] = 1;
                        }
                    
  
                   
                        if (z != (lenght1 - 1))
                        {
                            if ((chunk->maparray[x + width1 * (y + height1 * (z + 1))] | 4) == 4)
                                aha9[1] = 1;
                        }

                        else
                        {
                            if (front != chunks.end() && (front->second->maparray[x + width1 * (y + height1 * (z - 63))] | 4) == 4)
                                aha9[1] = 1;
                        }
                    


                    //right
          
                   
                        if (z)
                        {
                            if ((chunk->maparray[x + width1 * (y + height1 * (z - 1))] | 4) == 4)
                                aha9[0] = 1;
                        }

                        else
                        {

                            if (back != chunks.end() && (back->second->maparray[x + width1 * (y + height1 * (z + 63))] | 4) == 4)
                                aha9[0] = 1;
                        }
                    
                    if (chunk->maparray[x + width1 * (y + height1 * z)] > 40)
                    {
                        for (int j = 0; j < 6; j++)
                        {
                            if (aha9[j])
                            {
                                vertice.push_back(x);
                                vertice.push_back(y);
                                vertice.push_back(z);
                                vertice.push_back(j);

                                vertice.push_back(special[skrut - 41][j]);

                            }
                        }
                    }
                    else
                    {
                            for (int j = 0; j < 6; j++)
                            {
                                if (aha9[j])
                                {
                                    vertice.push_back(x);
                                    vertice.push_back(y);
                                    vertice.push_back(z);
                                    vertice.push_back(j);

                                    vertice.push_back(skrut);

                                }
                            } 
                    }
                }
            }
        }

    }
    ourShader->setVec3("watercolor", glm::vec3(0,0,0));
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, vertice.size() * 4, &vertice[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(int), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(int), (void*)(3 * sizeof(int)));
    glEnableVertexAttribArray(1);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(chunk->pos.x * width1, 0, chunk->pos.y * lenght1));
    ourShader->setMat4("model", model);
    glBindVertexArray(VAO1);
    glDrawArrays(GL_POINTS, 0, vertice.size() / 5);
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);

    vertice.clear();
}
void Map::generate(long long int x, long long int y)
{
    Chunk* chunk=new Chunk();
    chunk->pos = { x,y };
    //gen
    //biome
    chunk->Biome = 0;
    siv::PerlinNoise perlin(seed);
    for (int x = 0; x < width1; x++)
    {
        for (int z = 0; z < lenght1; z++)
        {
            const double noise = perlin.octave2D_01(((x + (chunk->pos.x * width1)) * 0.01), ((z + (chunk->pos.y * lenght1)) * 0.01), 8);
            int noise1 = noise * height1;
            int dirtlayer = noise1 - 4;
            for (int y = 0; y < height1; y++)
            {
                if (y < noise1 && y >= dirtlayer)
                {
                    chunk->maparray[x + width1 * (y + height1 * z)] = 2;
                }
                else if (y < dirtlayer)
                {
                    chunk->maparray[x + width1 * (y + height1 * z)] = 1;
                }
                else
                {
                    chunk->maparray[x + width1 * (y + height1 * z)] = 0;
                }
                if (y < 20 && !chunk->maparray[x + width1 * (y + height1 * z)])
                    chunk->maparray[x + width1 * (y + height1 * z)] = 4;
            }
            if (noise1)
                chunk->maparray[x + width1 * ((noise1 - 1) + height1 * z)] = 41;
            else
                chunk->maparray[x + width1 * ((noise1)+height1 * z)] = 41;
        }
    }
    for (int x = 1; x < width1-1; x++)
    {
        for (int z = 1; z < lenght1-1; z++)
        {
            const double noise = perlin.octave2D_01(((x + (chunk->pos.x * width1)) * 0.01), ((z + (chunk->pos.y * lenght1)) * 0.01), 8);
            int noise1 = noise * height1;
            if (!(rand() % 150) && chunk->maparray[x + width1 * ((noise1)+height1 * z)] != 4)
                generateStruct(0, x + 3, noise1, z + 3, chunk);
        }
    }
    glm::ivec2 pos1 = { chunk->pos.x,chunk->pos.y };
    std::string pos2 = std::to_string(pos1.x) + std::to_string(pos1.y);
    chunks.insert({ pos2, chunk });
}
void Map::drawwater(Shader* ourShader, Chunk* chunk)
{

    if (chunk->vertice1.size() > 0)
    {
        unsigned int VAO1, VBO1;
        ourShader->setVec3("watercolor", biomes[chunk->Biome].watercolor);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(chunk->pos.x * width1, 0, chunk->pos.y * lenght1));
        ourShader->setMat4("model", model);
        glGenVertexArrays(1, &VAO1);
        glGenBuffers(1, &VBO1);
        glBindVertexArray(VAO1);
        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, chunk->vertice1.size() * 4, &chunk->vertice1[0], GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(int), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(int), (void*)(3 * sizeof(int)));
        glEnableVertexAttribArray(1);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_POINTS, 0, chunk->vertice1.size() / 5);
        glDeleteVertexArrays(1, &VAO1);
        glDeleteBuffers(1, &VBO1);
        chunk->vertice1.clear();
    }
}