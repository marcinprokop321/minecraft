#include "player.h"





void Player::update()
{
    jump1 = velocity.y == 0;
    pos += velocity;
    velocity = { 0,0,0 };
    camera.update();
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        switch1 = 1;
    else
        switch1 = 0;
    if (switch1)
        noclip = !noclip;
    if (!noclip)
    {
        int aha3 = 0;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            aha3++;
            velocity.x -= (playerspeed * camera.backs.z) * (*deltaTime * 60);
            velocity.z -= (playerspeed * camera.backs.w) * (*deltaTime * 60);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            aha3++;
            velocity.x += (playerspeed * camera.backs.z) * (*deltaTime * 60);
            velocity.z += (playerspeed * camera.backs.w) * (*deltaTime * 60);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            aha3++;
            velocity.x -= (playerspeed * camera.backs.x) * (*deltaTime * 60);
            velocity.z -= (playerspeed * camera.backs.y) * (*deltaTime * 60);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            aha3++;
            velocity.x += (playerspeed * camera.backs.x) * (*deltaTime * 60);
            velocity.z += (playerspeed * camera.backs.y) * (*deltaTime * 60);
        }
        if (aha3 != 0)
            velocity.x /= 2; velocity.z /= 2;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && jump == -1 && jump1)
        {
            jump = 0;
        }
    }
    else
    {
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            camera.velocity.x -= (CAMERA_SPEED * camera.backs.z) * (*deltaTime * 60);
            camera.velocity.z -= (CAMERA_SPEED * camera.backs.w) * (*deltaTime * 60);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camera.velocity.x += (CAMERA_SPEED * camera.backs.z) * (*deltaTime * 60);
            camera.velocity.z += (CAMERA_SPEED * camera.backs.w) * (*deltaTime * 60);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {

            camera.velocity.x -= (CAMERA_SPEED * camera.backs.x) * (*deltaTime * 60);
            camera.velocity.z -= (CAMERA_SPEED * camera.backs.y) * (*deltaTime * 60);
            camera.velocity.y -= (CAMERA_SPEED * camera.cameraFront.y) * (*deltaTime * 60);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {

            camera.velocity.x += (CAMERA_SPEED * camera.backs.x) * (*deltaTime * 60);
            camera.velocity.z += (CAMERA_SPEED * camera.backs.y) * (*deltaTime * 60);
            camera.velocity.y += (CAMERA_SPEED * camera.cameraFront.y) * (*deltaTime * 60);
        }
    }
    if (jump != -1)
    {
        if (jump > 15)
            jump = -1;
        else
        {
            velocity.y += (playerspeed * 2)* (*deltaTime * 60);

            jump += ((*deltaTime * 60));
        }
    }
    // if (pos.y < 0)
     //{
         //pos.y = 0;
     //}
    if (!noclip)
    {
        camera.cameraPos = { pos.x  /*(0.14 * -cos(deg_to_rad(get_degrees(camera.direction.x + 90))))*/,pos.y + 1.84
    ,pos.z };//+ (0.14 * sin(deg_to_rad(get_degrees(camera.direction.x + 90)))) };
    }
    //playermodel->pos = pos;
    //playermodel->angle = (((camera.direction.x)));
    //place
    velocity.y -= gravitation*(*deltaTime * 60);
}
