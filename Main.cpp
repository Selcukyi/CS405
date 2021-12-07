#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "gtc/constants.hpp"
#include "gtx/rotate_vector.hpp"
#include "gtx/transform.hpp"
#include "common.hpp"
#include "gtc/type_ptr.hpp"
#include "stb_image.h"
#include "mesh_generation.h"
#include "opengl_utilities.h"
#include "Window.hpp"
#include "GameObj3D.hpp"
#include "ShaderProgram.hpp"
#include "Camera.hpp"
#include "Parametric3DShape.hpp"
#include <iostream>
#include <vector>
using namespace std;

// Globals
int u_transform, u_pv, u_frame;
int moveFront = 0, moveRight = 0;
float mouseX = 0, mouseY = 0;

void keyCallback(GLFWwindow* _, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        moveFront = 1;
    }
    else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
    {
        moveFront = 0;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        moveFront = -1;
    }
    else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
    {
        moveFront = 0;
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        moveRight = 1;
    }
    else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
    {
        moveRight = 0;
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        moveRight = -1;
    }
    else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
    {
        moveRight = 0;
    }
}

static void cursorPositionCallback(GLFWwindow* _, double x, double y)
{
    mouseX = 2.0 * ((float)x / Window::width) - 1;
    mouseY = 2.0 * (1 - ((float)y / Window::height)) - 1;
}

int main()
{
    // init window
    Window::init(800, 800, "my window");

    glfwSetKeyCallback(Window::window, keyCallback);
    glfwSetCursorPosCallback(Window::window, cursorPositionCallback);

    // init objects
    Model3D sphereModel = Parametric3DShape::generate(ParametricLine::halfCircle, 50, 50);
    GameObj3D sphere(sphereModel);
    sphere.translate(0, 0, 0);
    sphere.scale(1.0, 1.0, 1.0);

    vector<glm::vec3> positions = {
        // front
        glm::vec3(1.0, 1.0, 1.0),
        glm::vec3(1.0, -1.0, 1.0),
        glm::vec3(-1.0, -1.0, 1.0),
        glm::vec3(-1.0, 1.0, 1.0),
        // back
        glm::vec3(1.0, 1.0, -1.0),
        glm::vec3(1.0, -1.0, -1.0),
        glm::vec3(-1.0, -1.0, -1.0),
        glm::vec3(-1.0, 1.0, -1.0),
        // right
        glm::vec3(1.0, 1.0, -1.0),
        glm::vec3(1.0, -1.0, -1.0),
        glm::vec3(1.0, -1.0, 1.0),
        glm::vec3(1.0, 1.0, 1.0),
        // left
        glm::vec3(-1.0, 1.0, 1.0),
        glm::vec3(-1.0, -1.0, 1.0),
        glm::vec3(-1.0, -1.0, -1.0),
        glm::vec3(-1.0, 1.0, -1.0),
        // top
        glm::vec3(1.0, 1.0, -1.0),
        glm::vec3(1.0, 1.0, 1.0),
        glm::vec3(-1.0, 1.0, 1.0),
        glm::vec3(-1.0, 1.0, -1.0),
        // bottom
        glm::vec3(1.0, -1.0, -1.0),
        glm::vec3(1.0, -1.0, 1.0),
        glm::vec3(-1.0, -1.0, 1.0),
        glm::vec3(-1.0, -1.0, -1.0) };
    vector<glm::vec3> normals = {
        // front
        glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 1.0),
        // back
        glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 0.0, -1.0),
        // right
        glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0),
        // left
        glm::vec3(-1.0, 0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0),
        // top
        glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0),
        // bottom
        glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, -1.0, 0.0) };
    vector<unsigned int> indices = {
        // front
        0,
        1,
        2,
        2,
        3,
        0,
        // back
        4,
        5,
        6,
        6,
        7,
        4,
        // right
        8,
        9,
        10,
        10,
        11,
        8,
        // left
        12,
        13,
        14,
        14,
        15,
        12,
        // top
        16,
        17,
        18,
        18,
        19,
        16,
        // bottom
        20,
        21,
        22,
        22,
        23,
        20,
    };

    Model3D cubeModel(positions, normals, indices);
    GameObj3D cube(cubeModel);
    cube.translate(-1.0, 0, 1.0);
    cube.scale(3.0, 0.0, 3.0);

    /*
    * Model3D sphereModel(positions, normals, indices);
    GameObj3D sphere(sphereModel);
    sphere.translate(0.4, 0, 1.7);
    sphere.scale(0.2, 0.4, 0.2);
    */

    // create shader
    ShaderProgram sp("shader/vertex.vert", "shader/frag.frag");
    u_transform = glGetUniformLocation(sp.id, "u_transform");
    u_pv = glGetUniformLocation(sp.id, "u_pv");
    u_frame = glGetUniformLocation(sp.id, "u_frame");
    sp.use();

    // game loop
    while (!Window::isClosed())
    {
        // update camera
        Camera::rotation = glm::vec3(180 * mouseY, -180 * mouseX, 0);
        Camera::moveFront(moveFront * 0.01);
        Camera::moveRight(moveRight * 0.01);
        //Camera::moveUp(moveUp * 0.1);

        // update uniforms
        glUniformMatrix4fv(u_pv, 1, GL_FALSE, glm::value_ptr(Camera::getProjMatrix() * Camera::getViewMatrix()));
        glUniform1i(u_frame, 1);

        // draw
        glUniformMatrix4fv(u_transform, 1, GL_FALSE, glm::value_ptr(sphere.getTransform()));
        sphere.draw();

        glUniformMatrix4fv(u_transform, 1, GL_FALSE, glm::value_ptr(cube.getTransform()));
        cube.draw();

        //glUniformMatrix4fv(u_transform, 1, GL_FALSE, glm::value_ptr(cube.getTransform()));
        //cube.draw();

        // update the scene
        Window::refresh();
    }

    Window::terminate();

    return 0;
}