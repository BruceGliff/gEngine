#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <iostream>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Renderer/TextureGL.h"

#include "Resources/window/window_base.h"

//Easiest way of Vertex implimentation
GLfloat points[] =
{
    -1.f,   -1.f,    0.f,
     0.f,    1.f,    0.f,
     1.f,   -1.f,    0.f
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
            glBindVertexArray(vao);
            // Make texture to draw active
            texture->bind();
            // Draw current VAO
            glDrawArrays(GL_TRIANGLES, 0, 3);

            win.Draw();
        }
    } // ResourceManager is terminated

    return 0;
}
