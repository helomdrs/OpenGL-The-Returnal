#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

//Window dimensions
const GLint WINDOW_WIDTH = 640, WINDOW_HEIGHT = 480;

const GLchar* vertexShaderSource = "#version 330 core\nlayout(location = 0) in vec3 position;\nvoid main()\n{\ngl_Position = vec4(position, 1.0);\n}\n";
const GLchar* fragmentShaderSource = "#version 330 core\nout vec4 color;\nvoid main()\n{\ncolor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}\n";

int main(void)
{
    //Initialize GLFW library
    if (!glfwInit())
        return -1;

    //GLFW OpenGL property settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFW windowed mode window and its OpenGL context
    GLFWwindow *glfwWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello GLFW", NULL, NULL);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(glfwWindow, &screenWidth, &screenHeight);

    if (!glfwWindow)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(glfwWindow);

    //Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Problem: glewInit failed, something is seriously wrong.
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    std::cout << "Status: Using GL " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

    //Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);

    //Build vertex and fragmant shaders
    GLint success;
    GLchar infoLog[512];

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR: Vertex Shader compilation failed: " << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR: Fragment Shader compilation failed: " << infoLog << std::endl;
    }

    //Shader program linking and compiling 
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR: Shader program linking failed: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //Creating the vertex data to draw the triangle
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, //bottom left
         0.5f, -0.5f, 0.0f, //bottom right
         0.0f,  0.5f, 0.0f  //top middle
    };

    //creating and binding vertex buffer and array objects
    GLuint vertexBufferObject, vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(glfwWindow))
    {
        //Check if any input events have been activated and call corresponding response function
        glfwPollEvents();


        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(glfwWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //Cleanup
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);


    glfwTerminate();
    return 0;
}