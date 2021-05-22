#include "sprite.h"
#include <iostream>

ShaderProgram *Sprite::shader_program = nullptr;
Sprite::Sprite(i32 x, i32 y, i32 w, i32 h, const std::string& file_path) noexcept :
    m_quad(x, y, w, h, true) {

    m_quad.applyTransform();

    const char *file = file_path.c_str();
    Vector2<i32> size;
    auto image = SOIL_load_image(file, &size.x, &size.y, nullptr, SOIL_LOAD_RGBA);
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if (image) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Error unable to load image!" << std::endl;
    }

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
}

void Sprite::rotate(float amount) {
    m_quad.rotation += amount;
    m_quad.applyTransform();
}

void Sprite::translate(const Vector2<f32>& amount) {
    m_quad.m_position.x += amount.x / SCREEN_WIDTH;
    m_quad.m_position.y -= amount.y / SCREEN_HEIGHT;
    m_quad.applyTransform();
}

void Sprite::translate(float x, float y)
{
    m_quad.m_position.x += x / SCREEN_WIDTH;
    m_quad.m_position.y += y / SCREEN_HEIGHT;
    m_quad.applyTransform();
}

void Sprite::scale(const Vector2<f32>& amount) {
    m_quad.m_size.x = amount.x;
    m_quad.m_size.y = amount.y;
    m_quad.applyTransform();
}

void Sprite::scale(float x, float y)
{
    m_quad.m_size.x = x;
    m_quad.m_size.y = y;
    m_quad.applyTransform();
}

void Sprite::render() {
    shader_program->bind();
    m_quad.applyTransform();
    shader_program->applyUniformMat4("transform", m_quad.m_transform);
    shader_program->applyUniform1i("texture_sampler", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    m_quad.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    m_quad.unbind();

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    shader_program->unbind();
}
