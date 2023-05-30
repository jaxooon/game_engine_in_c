/* date = August 28th 2022 0:54 am */
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    public:
    unsigned int ID; //program ID
    
    Shader(const char* vertexPath, const char* fragmentPath) // shader constructor
    {
        std::string vertexCode;
        std::string fragmentCode;
        
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        
        vShaderFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit);
        
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            
            //read file buffer content into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            
            vShaderFile.close();
            fShaderFile.close();
            
            //convert stream to string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
            
        }
        catch(std::ifstream::failure e)
        {
            printf("ERROR::SHADER::FILE_NOT_SUCCESFULY_READ %s\n", e.what());
        }
        
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        
        //compile shaders
        unsigned int vertex, fragment;
        
        //vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompilationErrors(vertex, "VERTEX");
        
        //fragment
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompilationErrors(vertex, "FRAGMENT");
        
        //shader program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompilationErrors(ID, "PROGRAM");
        
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        
    }
    
    void use() // use / activate the shader
    {
        glUseProgram(ID);
    }
    
    void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    } 
    
    private:
    void checkCompilationErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if(type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                printf("ERROR::SHADER::COMPILATION::FAILED of type %s \n %s", type.c_str(), infoLog); 
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;; 
            }
        }
        
    }
    
};

#endif //SHADER_H
