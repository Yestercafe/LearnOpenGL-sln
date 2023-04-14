#include "shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    std::string vertexShaderCode, fragmentShaderCode;
    std::ifstream vShaderFile, fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(vertexShaderPath);
        fShaderFile.open(fragmentShaderPath);

        std::stringstream vStringStream, fStringStream;
        vStringStream << vShaderFile.rdbuf();
        fStringStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexShaderCode = vStringStream.str();
        fragmentShaderCode = fStringStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* vShaderCode = vertexShaderCode.c_str();
    const char* fShaderCode = fragmentShaderCode.c_str();

    unsigned int vertex, fragment;
    int succ;
    char info[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &succ);
    if (!succ) {
        glGetShaderInfoLog(vertex, 512, nullptr, info);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &succ);
    if (!succ) {
        glGetShaderInfoLog(fragment, 512, nullptr, info);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info << std::endl;
    }

    this->id = glCreateProgram();
    glAttachShader(this->id, vertex);
    glAttachShader(this->id, fragment);
    glLinkProgram(this->id);
    glGetProgramiv(this->id, GL_COMPILE_STATUS, &succ);
    if (!succ) {
        glGetProgramInfoLog(this->id, 512, nullptr, info);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(this->id);
}

void Shader::use() {
    glUseProgram(this->id);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int) value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
}
