#define SDL_MAIN_HANDLED

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>

int main(void)
{
    GLFWwindow* glfwWindow;

    //Initialize GLFW library
    if (!glfwInit())
        return -1;

    //GLFW OpenGL property settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    //SDL initialization
    SDL_Init(SDL_INIT_EVERYTHING);

    //SDL OpenGL property settings
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); //SDL buffer size

    // Create a GLFW windowed mode window and its OpenGL context
    glfwWindow = glfwCreateWindow(640, 480, "Hello GLFW", NULL, NULL);
    if (!glfwWindow)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(glfwWindow);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Problem: glewInit failed, something is seriously wrong.
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
    }

    //Creates a SDL Window
    SDL_Window* sdlWindow = SDL_CreateWindow("Hello SDL", 200, 200, 640, 480, SDL_WINDOW_OPENGL);

    //Creates a context to add the window to it
    SDL_GLContext sdlContext = SDL_GL_CreateContext(sdlWindow);

    SDL_version sdlVersion{};
    SDL_VERSION(&sdlVersion);
    std::cout << "Status: Using SDL " << (int)sdlVersion.major << "." << (int)sdlVersion.minor << "." << (int)sdlVersion.patch << std::endl;
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "Status: Using GL " << glGetString(GL_VERSION) << std::endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(glfwWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(glfwWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}