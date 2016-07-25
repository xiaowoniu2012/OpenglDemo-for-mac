//
//  ZZLShader.cpp
//  learnOpengl2
//
//  Created by zelong zou on 16/7/26.
//  Copyright © 2016年 Smart. All rights reserved.
//

#include "ZZLShader.hpp"
using namespace std;

ZZLShader::ZZLShader(const GLchar *vertexPath,const GLchar *fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vshaderFile;
    std::ifstream fshaderFile;
    
    try {
        vshaderFile.open(vertexPath);
        fshaderFile.open(fragmentPath);
        
        std::stringstream vshaderStream,fshaderStream;
        
        vshaderStream << vshaderFile.rdbuf();
        fshaderStream << fshaderFile.rdbuf();
        
        //close file
        
        vshaderFile.close();
        fshaderFile.close();
        
        //convert stream to string
        vertexCode = vshaderStream.str();
        fragmentCode = fshaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    
    const GLchar *vertexShaderSource = vertexCode.c_str();
    const GLchar *fragmentShaderSource = fragmentCode.c_str();
    
    std::cout<<"vertexShader Source :"<<std::endl<<vertexShaderSource<<endl;
    std::cout<<"fragmentShaderSource Source :"<<std::endl<<fragmentShaderSource<<endl;
    //compile shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    
    glCompileShader(vertexShader);
    
    GLint success;
    GLchar infoLog[512];
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout<<"vertexShader compile error: "<<infoLog<<std::endl;
        
    }
    
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout<<"fragmentShader compile error: "<<infoLog<<std::endl;
    }
    
    //create shader program
    this->programId = glCreateProgram();
    glAttachShader(this->programId, vertexShader);
    glAttachShader(this->programId, fragmentShader);
    glLinkProgram(this->programId);
    
    //log of shader program
    
    glGetProgramiv(this->programId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->programId, 512, NULL, infoLog);
        std::cout<<"program link error: "<<infoLog<<std::endl;
        
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void ZZLShader::UseShader() {
    glUseProgram(this->programId);
}




