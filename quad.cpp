#include "quad.h"



Quad::Quad(i32 x, i32 y, i32 w, i32 h, bool textured)
    : m_position(-1.0, 1.0),
      m_size(1.0, 1.0)
{
    f32 new_x = static_cast<f32>((x - SCREEN_WIDTH / 2) * 2) / SCREEN_WIDTH;
    f32 new_y = static_cast<f32>(SCREEN_HEIGHT - y * 2) / SCREEN_HEIGHT;
    f32 new_w = static_cast<f32>(w * 2) / SCREEN_WIDTH;
    f32 new_h = static_cast<f32>(h * 2) / SCREEN_HEIGHT;
    m_originalSize = Vector2<f32>(new_w, new_h);
    m_transform = glm::mat4(1.0);
    m_position = Vector2<f32>(new_x, new_y);
    rotation = 0.0;

    applyTransform();

    glGenVertexArrays(1, &m_VAO);
    bind();
    color = glm::vec4(1.0);

    if (textured) {
        f32 vertices[] = {
                0.0,  0.0, 0.0f, 0.0, 0.0,
                0.0, -new_h, 0.0f, 0.0, 1.0,
                new_w, -new_h, 0.0f, 1.0, 1.0,
                new_w,  0.0, 0.0f, 1.0, 0.0
         };

        GLuint indices[] = {
            0, 1, 2,
            0, 2, 3
        };


        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (GLvoid*)vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), (GLvoid*)indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (GLvoid*)(3 * sizeof(f32)));
        glEnableVertexAttribArray(1);

        unbind();
    } else {
        color = glm::vec4(1.0);
        f32 vertices[] = {
                0.0,  0.0, 0.0f,
                0.0, -new_h, 0.0f,
                new_w, -new_h, 0.0f,
                new_w,  0.0, 0.0f
         };

        GLuint indices[] = {
            0, 1, 2,
            0, 2, 3
        };

       // GLuint VBO, EBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (GLvoid*)vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), (GLvoid*)indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), 0);
        glEnableVertexAttribArray(0);

        unbind();
    }
}

void Quad::bind()
{
    glBindVertexArray(m_VAO);
}

void Quad::unbind()
{
    glBindVertexArray(0);
}


void Quad::applyTransform()
{
    m_transform = glm::mat4(1.0f);
    auto center = getCenter();

    m_transform = glm::translate(m_transform, glm::vec3(m_position.x, m_position.y, 0.0));
    m_transform = glm::translate(m_transform, glm::vec3(center.x, center.y, 0.0));
    m_transform = glm::rotate(m_transform, rotation, glm::vec3(0.0, 0.0, 1.0));

    m_transform = glm::translate(m_transform, glm::vec3(-center.x, -center.y, 0.0));
    m_transform = glm::scale(m_transform, glm::vec3(m_size.x, m_size.y, 1.0));
}

void Quad::applyTransformTopLeft()
{
    m_transform = glm::mat4(1.0f);

    m_transform = glm::scale(m_transform, glm::vec3(m_size.x, m_size.y, 1.0));
    m_transform = glm::translate(m_transform, glm::vec3(m_position.x, m_position.y, 0.0));

    m_transform = glm::rotate(m_transform, rotation, glm::vec3(0.0, 0.0, 1.0));
}

Vector2<f32> Quad::getCenter() const
{
    return Vector2<f32>(m_size.x * m_originalSize.x / 2, -m_originalSize.y * m_size.y / 2);
}

void Quad::setColor(f32 r, f32 g, f32 b, f32 a)
{
    color = glm::vec4(r, g, b, a);
}
