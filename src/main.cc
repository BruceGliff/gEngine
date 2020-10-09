#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int g_sizeX = 640;
int g_sizeY = 480;


/// Functions what overrides behavior
// Override size changes
void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    g_sizeX = width;
    g_sizeY = height;
    glViewport(0, 0, g_sizeX, g_sizeY);
}
// Override keyboard events
void glfwKeyCallback(GLFWwindow* window, int key, int scanmode, int action, int mode)
{
    // Close window due to escape
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        // Set up window property what is has to be closed
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cerr << "glfl initialization failed!" << std::endl;
        return -1;
    }
        
    /* Setup version of OpenGL. If not compared then terminated */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "gEngine", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "glfl window creating failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Set up my own function */
    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);

    /* Initialize glad */
    if (!gladLoadGL())
    {
        std::cerr << "Cannot initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL ver: " << glGetString(GL_VERSION) << std::endl;


    glClearColor(0.f, 1.f, 0.f, 1.f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
