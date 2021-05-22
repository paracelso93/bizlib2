#ifndef SPRITE_H
#define SPRITE_H

#include <optional>
#include <string>
#include <functional>
#include "quad.h"
#include "shaderprogram.h"

class Sprite
{
public:
    Sprite(i32 x, i32 y, i32 w, i32 h, const std::string& file_path) noexcept;
    void render();
    void rotate(float amount);
    void translate(const Vector2<f32>& amount);
    void translate(f32 x, f32 y);
    void scale(const Vector2<f32>& amount);
    void scale(f32 x, f32 y);
    Vector2<f32> getPosition() const { return Vector2<f32>((m_quad.m_position.x + 1.0) * SCREEN_WIDTH / 2, (1 - m_quad.m_position.y ) * SCREEN_HEIGHT / 2); }

    static ShaderProgram* shader_program;

private:
    Quad m_quad;
    GLuint m_texture;
};

#endif // SPRITE_H
