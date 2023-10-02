#include <iostream>
#include <vector>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "GLDebug/GLDebug.h"
#include "Shader/Shader.h"

#include "DeltaTime/DeltaTime.h"
#include "Camera.h"
#include "Player.h"

#include "glm/gtc/matrix_transform.hpp"
#include "Texture/TextureAtlas.h"
#include "Chunk/Chunk.h"
#include "ChunkMeshGenerator/ChunkMeshGenerator.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_pos_callback(GLFWwindow* window, double xPosIn, double yPosIn);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow* window);

int SCR_WIDTH = 1280;
int SCR_HEIGHT = 720;

Player player(Camera(SCR_WIDTH, SCR_HEIGHT, 45.f, 0.1f, 100.f));

bool glLine = false;
int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_pos_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window, key_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    Chunk chunk;
    ChunkMeshGenerator chunkGenerator;
    chunkGenerator.mesh(chunk);

    TextureAtlas textureAtlas("../res/textures/texture-atlas-old.png");
    Shader shader(
        "../res/shaders/basic.vert",
        "../res/shaders/basic.frag"
    );

    shader.bind();
    textureAtlas.bind();
    shader.setUniform1i("u_Texture", 0); // default texture slot

    // setting up 3D
    glm::mat4 model = glm::mat4(1.f);
    model = glm::translate(model, chunk.getPosition());
    const auto& view = player.getCamera().getView();
    const auto& projection = player.getCamera().getProjection();

    shader.setUniformMat4f("u_Model", model);
    shader.setUniformMat4f("u_View", view);
    shader.setUniformMat4f("u_Projection", projection);

    // render loop
    // -----------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    while (!glfwWindowShouldClose(window))
    {
        DeltaTime::newFrame(static_cast<float>(glfwGetTime()));
        processInput(window);
        player.updatePosition();
        // render
        // ------
        GLCall(glClearColor(0.f, .5f, 1.f, 1.f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        shader.bind();

        chunk.bind();
        // block.bind();
        GLCall(glDrawElements(GL_TRIANGLES, chunk.getIndexCount(), GL_UNSIGNED_INT, nullptr));
        shader.setUniformMat4f("u_View", player.getCamera().getView());

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    GLCall(glfwTerminate());
    return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    GLCall(glViewport(0, 0, width, height));
}

void processInput(GLFWwindow* window) {
    // processing keyboard inputs for player movement
    if(glfwGetKey(window, GLFW_KEY_W)) {
        player.moveForward();
    }
    if(glfwGetKey(window, GLFW_KEY_S)) {
        player.moveBackward();
    }
    if(glfwGetKey(window, GLFW_KEY_A)) {
        player.moveLeft();
    }
    if(glfwGetKey(window, GLFW_KEY_D)) {
        player.moveRight();
    }
}

void mouse_pos_callback(GLFWwindow* window, double xPosIn, double yPosIn) {
    player.lookAt(
        static_cast<float>(xPosIn),
        static_cast<float>(yPosIn)
    );
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // exiting the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        GLCall(glfwSetWindowShouldClose(window, true));
    }

    // toggle between wireframe and fill display mode
    if(key == GLFW_KEY_E && action == GLFW_PRESS) {
        if(glLine) {
            GLCall(glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ));
        }
        else {
            GLCall(glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ));
        }
        glLine = !glLine;
    }
}