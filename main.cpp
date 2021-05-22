#include <iostream>
#include "libs.h"
#include "shaderprogram.h"
#include "quad.h"
#include "sprite.h"

using namespace std;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Engine", nullptr, nullptr);
    glViewport(0, 0, 800, 600);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cout << "Error, unable to init glew!" << std::endl;
        return -1;
    }
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    auto texture_shader = std::make_unique<ShaderProgram>("/Users/edoardobiasio/Desktop/programmi_fallimentari/cpp_engine/bizlib2/Resources/Shaders/texture.vert",
            "/Users/edoardobiasio/Desktop/programmi_fallimentari/cpp_engine/bizlib2/Resources/Shaders/texture.frag");

    Sprite::shader_program = texture_shader.get();
    //Quad quad(0, 0, 600, 400, false);
    Sprite quad(0, 0, 600, 400, "/Users/edoardobiasio/Desktop/programmi_fallimentari/cpp_engine/bizlib2/Resources/Images/mod.png");
    Sprite opengl(100, 100, 400, 200, "/Users/edoardobiasio/Desktop/programmi_fallimentari/cpp_engine/bizlib2/Resources/Images/opengl.png");
    Sprite obama(200, 200, 100, 100, "/Users/edoardobiasio/Desktop/programmi_fallimentari/cpp_engine/bizlib2/Resources/Images/obamium.png");
    Sprite marco(400, 400, 100, 100, "/Users/edoardobiasio/Desktop/programmi_fallimentari/cpp_engine/bizlib2/Resources/Images/marco.jpg");
    quad.scale(Vector2<f32>(0.5, 0.5));
    f32 vx = 5, vy = -5;
    f32 x = 1, y = 1;
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        quad.rotate(0.01);
        opengl.rotate(-0.04);
        opengl.translate(Vector2<f32>(sin(glfwGetTime()) * 4, cos(glfwGetTime()) * 4));
        x += vx;
        y += vy;
        if (x < 0) vx *= -1;
        if (x > 800 - 300) { vx *= -1; x = 800 - 301; }
        if (y < 0) vy *= -1;
        if (y > 600 - 200) { vy *= -1; y = 600 - 201; }
        quad.translate(Vector2<f32>(x, y) - quad.getPosition());
        obama.scale(Vector2<f32>(sin(glfwGetTime()) * 2, sin(glfwGetTime()) * 2));

        marco.translate(Vector2<f32>(sin(glfwGetTime() * 10), 0));

        //std::cout << x << ":" << quad.getPosition().x << "," << y << ":" << quad.getPosition().y << std::endl;

        //quad.m_position.y -= 0.01f;
        //quad.rotation += glm::radians(0.4);
        //quad.applyTransform();
        glClearColor(sin(glfwGetTime()), cos(glfwGetTime()), sin(glfwGetTime()) * cos(glfwGetTime()), 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        opengl.render();
        obama.render();
        quad.render();
        marco.render();


        glfwSwapBuffers(window);
        glFlush();
    }

    return 0;
}
