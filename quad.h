#ifndef QUAD_H
#define QUAD_H

#include "libs.h"
#include "engine_maths.h"

class Quad
{
public:
    Quad(i32 x, i32 y, i32 w, i32 h, bool textured);
    void bind();
    void unbind();
    void applyTransform();
    void applyTransformTopLeft();
    Vector2<f32> getCenter() const;
    void setColor(f32 r, f32 g, f32 b, f32 a);

    glm::mat4 m_transform;

    Vector2<f32> m_position;
    Vector2<f32> m_originalSize;
    f32 rotation;
    Vector2<f32> m_size;
    glm::vec4 color;
private:
    GLuint m_VAO, VBO, EBO;
};

#endif // QUAD_H
