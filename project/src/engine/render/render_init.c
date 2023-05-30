#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "../types.h"
#include "../util.h"
#include "../global.h"

#include "render.h"
#include "render_internal.h"

GLFWwindow* render_init_window(u32 width, u32 height)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(width, height, "SuperBoxCrate", NULL, NULL);
    if(window == NULL)
    {
        ERROR_EXIT("Failed to create GLFW window");
        glfwTerminate();
        //return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, process_input_callback);
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ERROR_EXIT("Failed to initialize GLAD\n");
        //return -1;
    } 

    return window;

}

void render_init_quad(u32 *vao, u32 *vbo, u32 *ebo)
{
    f32 vertices[] = {
    //       positions    texture coords
    //    X      Y     Z     U     V
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f, 0.0f, 1.0f    // top left 
    }; 

    u32 indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenBuffers(1, vbo); 
    glGenBuffers(1, ebo);
    glGenVertexArrays(1, vao);

    glBindVertexArray(*vao);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // position attribute (xyz)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(u32), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute (uv)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(u32), (void*)(3 * sizeof(u32)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure th\e viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void process_input_callback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

void render_init_color_texture(u32 *texture)
{
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    
    u8 solid_white[4] = {255, 255, 255, 255};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, solid_white);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void render_init_shaders(Render_State_Internal *state)
{
    state->shader_default = render_shader_create("./shaders/default.vert", "./shaders/default.frag");

    glm_ortho(0, global.render.width, 0, global.render.height, -2, 2, state->projection);

    glUseProgram(state->shader_default);
    glUniformMatrix4fv(
        glGetUniformLocation(state->shader_default, "projection"),
        1,
        GL_FALSE,
        &state->projection[0][0]
    );


}
u32 render_shader_create(const char *path_vert, const char *path_frag);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input_callback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods);

