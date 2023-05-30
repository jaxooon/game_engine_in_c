//where all the functions and types that are used elsewhere are defined
#pragma once

#include <GLFW/glfw3.h>
#include "../types.h"

typedef struct render_state {
    GLFWwindow* window;
    f32 width;
    f32 height;
} Render_State;

void render_init(void);
void render_begin(void);
void render_end(void);
void render_quad(vec2 pos, vec2 size, vec4 colour);
