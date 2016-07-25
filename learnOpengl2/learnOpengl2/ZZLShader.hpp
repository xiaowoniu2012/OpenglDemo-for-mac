//
//  ZZLShader.hpp
//  learnOpengl2
//
//  Created by zelong zou on 16/7/26.
//  Copyright © 2016年 Smart. All rights reserved.
//

#ifndef ZZLShader_hpp
#define ZZLShader_hpp
#include <OpenGL/gl3.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class ZZLShader {
public:

    // 构造器读取并构建着色器
    ZZLShader(const GLchar *vertexShaderFile,const GLchar *fragmentShaderFile);
    // 使用程序
    void UseShader();
    
private:
    // program id
    GLuint programId;
};


#endif /* ZZLShader_hpp */
