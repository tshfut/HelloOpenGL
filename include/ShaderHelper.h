//
// Created by TSHFUT on 2023-01-14.
//

#ifndef HELLOOPENGL_SHADERHELPER_H
#define HELLOOPENGL_SHADERHELPER_H

#include <iostream>
#include <sstream>
#include <fstream>

#include <glad/glad.h>

enum SHADER_TYPE {
    VERTEX      = 0,
    FRAGMENT    = 1,
    GEOMETRY    = 2,
    PROGRAM     = 3,
};

class ShaderHelper {
public:
    GLuint ID;

public:
    ShaderHelper() {}

    ShaderHelper(const std::string vertexPath,
                 const std::string fragmentPath,
                 const std::string geometryPath = "") {
        GLuint vertexShader = 0;
        GLuint fragmentShader = 0;
        GLuint geometryShader = 0;
        CreateAndCompileShader(vertexPath, &vertexShader, SHADER_TYPE::VERTEX);
        CreateAndCompileShader(fragmentPath, &fragmentShader, SHADER_TYPE::FRAGMENT);
        if (!geometryPath.empty()) {
            CreateAndCompileShader(geometryPath, &geometryShader, SHADER_TYPE::GEOMETRY);
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        if (!geometryPath.empty()) {
            glAttachShader(ID, geometryShader);
        }
        glLinkProgram(ID);
        checkCompileErrors(ID, SHADER_TYPE::PROGRAM);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        if (!geometryPath.empty()) {
            glDeleteShader(vertexShader);
        }
    }

    void CreateAndCompileShader(std::string path, GLuint *id, SHADER_TYPE type) {
        std::string code;
        std::ifstream shaderFile;
        shaderFile.open(path);
        if (!shaderFile.is_open()) {
            std::cout << "Failed to open fragment shader(" << type << ") file:" << path << std::endl;
            return;
        }
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        code = shaderStream.str();
        switch (type) {
            case SHADER_TYPE::VERTEX:
                *id = glCreateShader(GL_VERTEX_SHADER);
                break;
            case SHADER_TYPE::FRAGMENT:
                *id = glCreateShader(GL_FRAGMENT_SHADER);
                break;
            case SHADER_TYPE::GEOMETRY:
                *id = glCreateShader(GL_GEOMETRY_SHADER);
                break;
            default:
                std::cout << "Ininvalidate shader type" << std::endl;
                return;
        }

        const char *shaderCode = code.c_str();
        glShaderSource(*id, 1, &shaderCode, nullptr);
        glCompileShader(*id);
        checkCompileErrors(*id, type);
    }

    void use() {
        glUseProgram(ID);
    }

    void checkCompileErrors(GLuint shader, SHADER_TYPE type) {
        GLint success;
        GLchar infoLog[1024];
        if (type != PROGRAM) {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
                          << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
                          << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};


#endif //HELLOOPENGL_SHADERHELPER_H
