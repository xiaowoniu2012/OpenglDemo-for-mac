//
//  main.cpp
//  learnOpengl2
//
//  Created by zelong zou on 16/7/25.
//  Copyright © 2016年 Smart. All rights reserved.
//

#include <iostream>
#include "glfw3.h"
#include <math.h>
#include <OpenGL/gl3.h>
#include "ZZLShader.hpp"
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec4 fragmentColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0f);\n"
"fragmentColor = vec4(color,1.0f);\n"
"}\0";

//const GLchar* fragmentShaderSource = "#version 330 core\n"
////"in vec4 fragmentColor;\n"
//"uniform vec4 changeColor;\n"
//"out vec4 color;\n"
//"void main()\n"
//"{\n"
//"color = changeColor;\n"
//"}\n\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"in vec4 fragmentColor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = fragmentColor;\n"
"}\n\0";

GLuint shaderProgram;
GLuint VAO[2];
GLuint VBO[2];
GLfloat vertices1[] = {
    //first
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // Left
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// Right
    0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,// Top
    
    //second

};

GLfloat vertices2[] = {
    
    0.5f,-0.5f,0.0f, 1.0f, 0.0f, 0.0f,//left
    1.0f,-0.5f,0.0f, 0.0f, 1.0f, 0.0f,//right
    0.75f,0.5f,0.0f, 0.0f, 0.0f, 1.0f,//top
};

void compileShaders(void) {
    //创建顶点着色器对象 vertexShader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //下一步我们把这个着色器源码附加到着色器对象上，然后编译它：
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    // 检测在调用glCompileShader后编译是否成功了
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("vertexshader compile error log : %s",infoLog);
    }
    
    //创建片段着色器对旬 fragmentShader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    
    // 检测在调用glCompileShader后编译是否成功了
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("fragmentShader compile error log : %s",infoLog);
    }
    
    // 链接shader
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    
    // 检测在调用glLinkProgram 后链接是否成功了
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("shaderProgram link error log : %s",infoLog);
    }
    
    //使用着色器对象程序
    glUseProgram(shaderProgram);
    //删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
}


void process() {
    
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    
    // location
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    
    
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    //color  间隔 6*sizeof(GLfloat) 大小  ，存储位置：(GLvoid*)(3*sizeof(GLfloat)) 偏移3个(float)位置
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    

}



int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    
 
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    printf("%s \n\n",glGetString(GL_VERSION)) ;
    
    
    //下面两种方式二选一：
    
    //1.使用c++类加载shader资源文件
    ZZLShader myshader("/Users/xiaowoniu/Documents/OpenglProgramming/learnOpengl/learnOpengl2/learnOpengl2/shaderFiles/vertexShader.vs", "/Users/xiaowoniu/Documents/OpenglProgramming/learnOpengl/learnOpengl2/learnOpengl2/shaderFiles/fragmentShader.frag");
    
    //2.使用全局的字符串加载shader
    //compileShaders();
    
    
    process();
    
    while (!glfwWindowShouldClose(window))
    {
        
        glClearColor(0.2, 0.2, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        /*  use uniform global var..
         
        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = sin(timeValue)/2 + 0.5f;
        GLuint vertexColorLocation = glGetUniformLocation(shaderProgram, "changeColor");
        glUseProgram(shaderProgram);
        
        glUniform4f(vertexColorLocation, 0.5f, 0.5f, greenValue, 1.0f);
        
         */
        //1.使用全局的字符串加载着色器程序方式
        //glUseProgram(shaderProgram);
        
        //2.使用C++类加载加载着色器程序方式
        myshader.UseShader();
        
        
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        
 
        glfwPollEvents();
    }
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    
    glfwTerminate();
    return 0;
}



