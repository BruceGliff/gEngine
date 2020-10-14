#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Renderer/TextureGL.h"

// This is should be at resource manager
#include "Resources/window/window_base.h"

//Easiest way of Vertex implimentation
// Vertex now has global coordinates
GLfloat points[] =
{
    -200.f, -200.f, 0.0f,
     0.0f,  200.f, 0.0f,
     200.f, -200.f, 0.0f
};
GLfloat colors[] = 
{
    1.f,    0.f,    0.f,
    0.0f,   1.f,    0.f,
    0.f,    0.f,    1.f
};
GLfloat texture_cords[] =
{
    0.f,    0.f,
    0.5f,   1.f,
    1.f,    0.f
};

// VS
char const* vertex_shader_PATH = "res/shaders/vertex.glsl";
// FS
char const* fragment_shader_PATH = "res/shaders/fragment.glsl";


int main(int argc, char * argv[])
{        
    Resources::glWindows win{};

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

    {// ResourceManager has shaders constext inside. so it has to be terminated before glfw
        Resources::ResourcesManager resMng{ argv[0] };
        auto pShaderProgram = resMng.loadShaders( "DefaultSahder", vertex_shader_PATH, fragment_shader_PATH );
        if (!pShaderProgram->IsCompiled())
        {
            std::cerr << "ERROR:: Creating Shader program in main\n" << std::endl;
            glfwTerminate();
            return -1;
        }

        auto texture = resMng.loadTexture("DefaultTexture", "res/textures/earth1.png");

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

        GLuint texture_vbo = 0;
        glGenBuffers(1, &texture_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texture_cords), texture_cords, GL_STATIC_DRAW);

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

        glEnableVertexAttribArray(1); // location = 1 <-> color
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2); // location = 2 <-> texture
        glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        // To activate shader program
        pShaderProgram->Use();
        pShaderProgram->SetID("tex", 0);

        //Transformation
        glm::mat4 modelMatrix = glm::mat4(1.f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3{ 320.f, 240.f, 0.f }); // to change from local to world position
        // view matrix is single matrix as we dont have camera
        // from view space to clip space should be ortographic matrix(or pesrpective for 3D)
        // 1000 and 800 is the screen size, but there is just temporary variables
        glm::mat4 projectionMatrix{ glm::ortho(0.f, 640.f, 0.f, 480.f, -100.f, 100.f) };
        // Now we should pass these matrix to uniform shader variable

        // We assume that camera don't move during the game, so we pass it once
        pShaderProgram->loadMatrix("projectionMatrix", projectionMatrix);

        // Now we are ready for drawing
        /* Loop until the user closes the window */
        while (!win)
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            // Drawing
            pShaderProgram->Use();
            // Now we connect vao to draw. it is already current, but it can be different for different obejcts in future
            glBindVertexArray(vao);
            // Make texture to draw active
            texture->bind();
            // Draw current VAO

            // Tranformation of the object occures every frame
            pShaderProgram->loadMatrix("modelMatrix", modelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            win.Draw();
        }
    } // ResourceManager is terminated

    return 0;
}
