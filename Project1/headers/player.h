#pragma once
#include "Object.h"
#include "shader_s.h"
#include "Chunk.h"
#include "Camera.h"

class Player : public Object
{
public:
    Camera camera;
    GLFWwindow* window;
    bool noclip;
    glm::fvec3 velocity;

    float renderDist;
    bool switch1 = false;
    float jump = -1;
    bool jump1;
    float *deltaTime;
    bool placeswitch = false;
    bool placeswitch1 = false;
    int witchblock = 1;
    void load(GLFWwindow *windo1)
    {
        //playermodel = new Model("res/FinalBaseMesh.obj", "res/Grass_Block_TEX.png",glm::vec3(0.1,0.1,0.1));
        //playermodel->pos = { 0,0,0 };
        std::cout << "RENDER:";
        std::cin >> renderDist;
        if (!renderDist)
        {
            renderDist = 1;
            std::cout << "minimum render distance is 1!" << "\n";
        }
        window = windo1;
        camera.window = windo1;
    }
    void update();
    //refresh map

};