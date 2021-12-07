#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

class Window
{
public:
    static unsigned width, height;
    static unsigned long long frameCount;
    static bool init(unsigned width, unsigned height, const char* name);
    static bool isClosed();
    static void refresh();
    static void terminate();
    static GLFWwindow* window;

private:
    Window();
};

GLFWwindow* Window::window = nullptr;

unsigned Window::width = 0;

unsigned Window::height = 0;

unsigned long long Window::frameCount = 0;

bool Window::init(unsigned width, unsigned height, const char* name)
{
    if (window != nullptr) return true;

    Window::width = width;
    Window::height = height;

    // init glfw
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW!" << endl;
        return false;
    }

    // glfw window hints

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, name, NULL, NULL);

    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        return false;
    }

    glfwMakeContextCurrent(window);

    // init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return false;
    }

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    return true;
}

bool Window::isClosed() {
    return glfwWindowShouldClose(window);
}

void Window::refresh() {
    glfwSwapBuffers(window);
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Window::frameCount++;
}

void Window::terminate() {
    glfwTerminate();
}

#endif