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

GLfloat verteces[] =
{
    // position          // color          // texture
    -1.f, -1.f,  0.f,    0.f, 1.f, 0.f,    0.f, 0.f,
    -1.f,  1.f,  0.f,    1.f, 0.f, 0.f,    0.f, 1.f,
     1.f,  1.f,  0.f,    0.f, 1.f, 0.f,    1.f, 1.f,
     1.f, -1.f,  0.f,    0.f, 0.f, 1.f,    1.f, 0.f
};
unsigned int indices[] =
{
    0, 2, 3,
    0, 1, 2
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

        auto texture = resMng.loadTexture("DefaultTexture", "res/textures/weed_pepe.jpg");

        // Vertex array object .. all together: vertices and indices
        unsigned int VAO = 0;
        glGenVertexArrays(1, &VAO);
        // Vertex buffer object .. vertices
        unsigned int VBO = 0;
        glGenBuffers(1, &VBO);
        // Element buffer object .. indices
        unsigned int EBO = 0;
        glGenBuffers(1, &EBO);
        
        glBindVertexArray(VAO);
        // copy our vertices array in a vertex buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verteces), verteces, GL_STATIC_DRAW);
        // copy our index array in a element buffer for OpenGL to use
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        // then set the vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);


        // To activate shader program
        pShaderProgram->Use();
        pShaderProgram->SetID("tex", 0);

        // Now we are ready for drawing
        /* Loop until the user closes the window */
        while (!win)
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            // Drawing
            pShaderProgram->Use();
            // Now we connect vao to draw. it is already current, but it can be different for different obejcts in future
            glBindVertexArray(VAO);
            // Make texture to draw active
            texture->bind();
            // Draw current VAO

            // Tranformation of the object occures every frame
//            pShaderProgram->loadMatrix("modelMatrix", modelMatrix);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            win.Draw();
        }
    } // ResourceManager is terminated

    return 0;
}
