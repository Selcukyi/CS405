#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
using namespace std;

class ShaderProgram
{
public:
    unsigned int id = NULL;

    ShaderProgram(const string& vertexPath, const string& fragmentPath);
    void use();

private:
    string parseShader(const string& shaderDirectory);
    int createProgram(const string& vertexPath, const string& fragmentPath);
    unsigned int compileShader(unsigned int type, const char* source);
    unsigned int compileProgram(const char* vertexShader, const char* fragmentShad);
};

ShaderProgram::ShaderProgram(const string& vertexPath, const string& fragmentPath) {
    id = createProgram(vertexPath, fragmentPath);
}

void ShaderProgram::use() {
    glUseProgram(id);
}

int ShaderProgram::createProgram(const string& vertexPath, const string& fragmentPath) {

    string vertexSource = parseShader(vertexPath);
    string fragmentSource = parseShader(fragmentPath);

    const char* vertexSourcePtr = &vertexSource[0];
    const char* fragmentSourcePtr = &fragmentSource[0];

    unsigned int program = glCreateProgram();
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSourcePtr);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSourcePtr);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Error check
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        cout << "Error: Program linking failed" << endl;

        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];

        glGetProgramInfoLog(program, length, &length, message);
        cout << message << endl;

        delete[]message;
        return NULL;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

unsigned int ShaderProgram::compileShader(unsigned int type, const char* source)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    // Error check
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        cout << "Error: Shader Compilation failed" << endl;
        cout << "Shader type: " << (type == GL_FRAGMENT_SHADER ? "fragment shader" : "vertex shader") << endl;

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];

        glGetShaderInfoLog(id, length, &length, message);
        cout << message << endl;

        delete[]message;
        glDeleteShader(id);

        return NULL;
    }

    return id;
}

string ShaderProgram::parseShader(const string& shaderPath) {

    ifstream shaderFile(shaderPath);
    string shaderSource = "";
    string line;

    if (shaderFile.fail()) {
        cout << "Failed to open file: \"" << shaderPath << "\"" << endl;
        return "";
    };

    while (getline(shaderFile, line)) {
        shaderSource += line + '\n';
    }

    return shaderSource;
}

#endif