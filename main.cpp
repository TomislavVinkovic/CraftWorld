#include <iostream>
#include <vector>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "GLDebug/GLDebug.h"
#include "Shader/Shader.h"

#include "DeltaTime.h"
#include "Camera.h"
#include "Player.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "VertexArray/VertexArray.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_pos_callback(GLFWwindow* window, double xPosIn, double yPosIn);
void processInput(GLFWwindow* window);

int SCR_WIDTH = 1280;
int SCR_HEIGHT = 720;

Player player(Camera(SCR_WIDTH, SCR_HEIGHT, 45.f, 0.1f, 100.f));

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

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // WINDOW CONFIGURATION END

    // DRAWING A CUBE
    std::vector<float> vertices {
            1.f, 0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 1.f, 0.f,
            0.f, 1.f, 0.f, 1.f, 1.f,
            1.f, 1.f, 0.f, 0.f, 1.f,

            // Front
            0.f, 0.f, 1.f, 0.f, 0.f,
            1.f, 0.f, 1.f, 1.f, 0.f,
            1.f, 1.f, 1.f, 1.f, 1.f,
            0.f, 1.f, 1.f, 0.f, 1.f,

            // Right
            1.f, 0.f, 1.f, 0.f, 0.f,
            1.f, 0.f, 0.f, 1.f, 0.f,
            1.f, 1.f, 0.f, 1.f, 1.f,
            1.f, 1.f, 1.f, 0.f, 1.f,

            // Left
            0.f, 0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 1.f, 0.f,
            0.f, 1.f, 1.f, 1.f, 1.f,
            0.f, 1.f, 0.f, 0.f, 1.f,

            // Top
            0.f, 1.f, 1.f, 0.f, 0.f,
            1.f, 1.f, 1.f, 1.f, 0.f,
            1.f, 1.f, 0.f, 1.f, 1.f,
            0.f, 1.f, 0.f, 0.f, 1.f,

            // Bottom
            0.f, 0.f, 0.f, 0.f, 0.f,
            1.f, 0.f, 0.f, 1.f, 0.f,
            1.f, 0.f, 1.f, 1.f, 1.f,
            0.f, 0.f, 1.f, 0.f, 1.f
    };

    std::vector<unsigned int> indices {
            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            6, 7, 4,

            8, 9, 10,
            10, 11, 8,

            12, 13, 14,
            14, 15, 12,

            16, 17, 18,
            18, 19, 16,

            20, 21, 22,
            22, 23, 20
    };

    VertexArray vao;

    VertexBuffer vbo(vertices);
    VertexBufferLayout layout;
    layout.push<float>(3); // position
    layout.push<float>(2); // texture coordinates

    IndexBuffer ibo(indices);

    vao.addBuffers(vbo, ibo, layout);

//    // array buffer
//    unsigned int VAO;
//    GLCall(glCreateVertexArrays(1, &VAO));
//    GLCall(glBindVertexArray(VAO));
//
//    // vertex buffer
//    unsigned int VBO;
//    GLCall(glCreateBuffers(1, &VBO));
//    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
//    GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW));
//
//    // vertex buffer layout
//    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) nullptr));
//    GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
//    GLCall(glEnableVertexAttribArray(0));
//    GLCall(glEnableVertexAttribArray(1));
//
//    // index buffer
//    unsigned int IBO;
//    GLCall(glCreateBuffers(1, &IBO));
//    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
//    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));


    // shader
    Shader shader(
        "../res/shaders/basic.vert",
        "../res/shaders/basic.frag"
    );

    shader.bind();

    // setting up 3D
    glm::mat4 model = glm::mat4(1.f);
    model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
    const auto& view = player.getCamera().getView();
    const auto& projection = player.getCamera().getProjection();

    shader.setUniformMat4f("u_Model", model);
    shader.setUniformMat4f("u_View", view);
    shader.setUniformMat4f("u_Projection", projection);

    // render loop
    // -----------
    glEnable(GL_DEPTH_TEST);
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
        vao.bind();
        GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr));
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

    // exiting the application
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        GLCall(glfwSetWindowShouldClose(window, true));
    }
}

void mouse_pos_callback(GLFWwindow* window, double xPosIn, double yPosIn) {
    player.lookAt(
        static_cast<float>(xPosIn),
        static_cast<float>(yPosIn)
    );
}