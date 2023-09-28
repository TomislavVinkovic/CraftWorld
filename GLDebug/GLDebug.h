#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <csignal>


# define ASSERT(x) if(!(x)) raise(SIGTRAP);
# define GLCall(x) GlClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__)); \

void GlClearError();
bool GLLogCall(const char* function, const char* file, int line);