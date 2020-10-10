#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer/ShaderProgram.h"

int g_sizeX = 640;
int g_sizeY = 480;


//Easiest way of Vertex implimentation
GLfloat points[] =
{
    0.5f,   0.f,    0.f,
    0.0f,   0.5f,   0.f,
    0.f,    0.f,    0.f
};
GLfloat colors[] = 
{
    1.f,    0.f,    0.f,
    0.0f,   1.f,    0.f,
    0.f,    0.f,    1.f
};

// VS
// color for FS for interpoliation. 
// gl_position must be normalize, but we already have it in propreate form
// gl_position is a vec4 with additional perspective value
char const* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"    color = vertex_color;"
"    gl_Position = vec4(vertex_position, 1.0);"
"}";
// FS
// color for each fragment(mb pixel) 
// color actually is a vec4 with additioanly alpha channel
char const* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"    frag_color = vec4(color, 1.0);"
"}";
// Now sheders have to pass in GPU

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

    // Fill bachground with color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // Shader program
    Renderer::ShaderProgram shaderProgram{ std::string{vertex_shader}, std::string{fragment_shader} };
    if (!shaderProgram.IsCompiled())
    {
        std::cerr << "ERROR:: Creating Shader program in main\n" << std::endl;
        glfwTerminate();
        return -1;
    }

    // VBO = Vertex buffer object
    // We have to pass data to the GPU
    GLuint point_vbo = 0;
    // Generate 1 vbo
    glGenBuffers(1, &point_vbo);
    // Now we have to bind to make it current buffer
    glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
    // Finnaly load data to GPU. This command executes for current buffer (prev step)
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint color_vbo = 0;
    glGenBuffers(1, &color_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // To bind our variables and variables on GPU we should create VAO = vertex array object
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // By default layaout disabled, so we have to enable it
    glEnableVertexAttribArray(0); // location = 0 <-> position
    // Should make point_vbo current buffer as we change it to color_vbo. CURRENT IS ONLY ONE
    glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
    // Bind data. location, vec3 for 3 vertexies(3 = vertexies), 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    // For color
    glEnableVertexAttribArray(1); // location = 1 <-> color
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    // Now we are ready for drawing

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Drawing
        shaderProgram.Use();
        // Now we connect vao to draw. it is already current, but it can be different for different obejcts in future
        glBindVertexArray(vao);
        // Draw current VAO
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
