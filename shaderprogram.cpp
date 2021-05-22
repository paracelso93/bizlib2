#include "shaderprogram.h"
#include <fstream>
#include <sstream>
#include <iostream>

ShaderProgram::ShaderProgram(const std::string& vertex_shader, const std::string& fragment_shader) {
    std::ifstream vertex_file(vertex_shader);

    std::stringstream file_buffer;
    file_buffer << vertex_file.rdbuf();
    std::string file_string = file_buffer.str();
    const char* file_c_string = file_string.c_str();

    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShader, 1, &file_c_string, nullptr);
    glCompileShader(m_vertexShader);
    checkForShaderSuccess(m_vertexShader, "vertex");
    vertex_file.close();

    std::ifstream fragment_file(fragment_shader);

    file_buffer.str("");
    file_buffer << fragment_file.rdbuf();
    file_string = file_buffer.str();

    const char* file_c_string_frag = file_string.c_str();
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShader, 1, &file_c_string_frag, nullptr);
    glCompileShader(m_fragmentShader);
    checkForShaderSuccess(m_fragmentShader, "fragment");
    fragment_file.close();

    m_program = glCreateProgram();
    bind();
    glAttachShader(m_program, m_vertexShader);
    glAttachShader(m_program, m_fragmentShader);
    glLinkProgram(m_program);
    checkForProgramSuccess();
    unbind();

    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
}

void ShaderProgram::bind() {
    glUseProgram(m_program);
}

void ShaderProgram::unbind() {
    glUseProgram(0);
}

bool ShaderProgram::checkForShaderSuccess(GLuint shader, const std::string &shader_type) {
    char infoLog[512];
    GLint success;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Error: can't compile " + shader_type + " shader!" << std::endl;
        std::cout << infoLog << std::endl;
    }

    return success;
}

bool ShaderProgram::checkForProgramSuccess() {
    char infoLog[512];
    GLint success;

    glGetProgramiv(m_program, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
        std::cout << "Error: can't compile program!" << std::endl;
        std::cout << infoLog << std::endl;
    }

    return success;
}
