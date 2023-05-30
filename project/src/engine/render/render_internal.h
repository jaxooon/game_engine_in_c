//all the functions and types that are strictly internal to the renderer are defined
#pragma once

#include <GLFW/glfw3.h>
#include "../types.h"
#include "render.h"

typedef struct render_state_internal {
    u32 vao_quad;
    u32 vbo_quad;
    u32 ebo_quad;
    u32 shader_default;
    u32 texture_color;
    mat4 projection;
} Render_State_Internal;

GLFWwindow* render_init_window(u32 width, u32 height);
void render_init_quad(u32 *vao, u32 *vbo, u32 *ebo);
void render_init_color_texture(u32 *texture);
void render_init_shaders(Render_State_Internal *state);
u32 render_shader_create(const char *path_vert, const char *path_frag);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input_callback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods);