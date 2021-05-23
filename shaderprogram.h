#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "libs.h"
#include <string>

class ShaderProgram
{
public:
    ShaderProgram(const std::string& vertex_shader, const std::string& fragment_shader);

    GLuint getVertexShaderID() const { return m_vertexShader; }
    GLuint getFragmentShaderID() const { return m_fragmentShader; }
    GLuint getProgramID() const { return m_program; }

    void applyUniformMat4(const std::string& position, const glm::mat4& value) {
        GLint location = glGetUniformLocation(m_program, position.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void applyUniform1i(const std::string& position, i32 value) {
        GLint location = glGetUniformLocation(m_program, position.c_str());
        glUniform1i(location, value);
    }

    void applyUniform4f(const std::string& position, const glm::vec4& value) {
        GLint location = glGetUniformLocation(m_program, position.c_str());
        glUniform4fv(location, 1, glm::value_ptr(value));
    }

    void bind();
    void unbind();

private:
    bool checkForShaderSuccess(GLuint shader, const std::string& shader_type);
    bool checkForProgramSuccess();

    GLuint m_vertexShader;
    GLuint m_fragmentShader;
    GLuint m_program;


};

#endif // SHADERPROGRAM_H
