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
#include "SOIL.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec4 fragmentColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position, 1.0f);\n"
"fragmentColor = vec4(color,1.0f);\n"
"}\0";


const GLchar* fragmentShaderSource = "#version 330 core\n"
"in vec4 fragmentColor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = fragmentColor;\n"
"}\n\0";

GLuint shaderProgram;
GLuint VAO[3];
GLuint VBO[3];
GLuint texture1;

GLfloat field_of_view = 45.0f;

GLfloat vertices1[] = {
    //first               //color               //texture
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  1.0f,0.0f,
    0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,  0.5f,1.0f,
    
    //second

};

GLfloat vertices2[] = {
    
    0.5f,-0.5f,0.0f, 1.0f, 0.0f, 0.0f,0.0f,0.0f,
    1.0f,-0.5f,0.0f, 0.0f, 1.0f, 0.0f,0.5f,0.0f,
    0.75f,0.5f,0.0f, 0.0f, 0.0f, 1.0f,0.25f,1.0f,
};

GLfloat cubeVertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

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
    
    glGenVertexArrays(3, VAO);
    glGenBuffers(3, VBO);
    
    
    
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    
    // location
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    //texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat),(GLvoid *)(6*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    
    
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    //color  间隔 6*sizeof(GLfloat) 大小  ，存储位置：(GLvoid*)(3*sizeof(GLfloat)) 偏移3个(float)位置
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    //texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat),(GLvoid *)(6*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
     
    
    
    
    
    // cube
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0); // Unbind VAO
    
    

}

void textureProcess() {
    
    
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    GLint width,height;
   
//    unsigned char * image = SOIL_load_image("/Users/smart/Documents/learn/opengl/OpenglDemo-for-mac/learnOpengl2/learnOpengl2/wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    unsigned char * image = SOIL_load_image("wall.jpg",&width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    std::cout<<"resource image  width is : "<<width<<" height is : "<<height<<std::endl;
    
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    

}




int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    
 
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    

    
    // Define the viewport dimensions
    glViewport(0, 0, 640, 480);
    
    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);
    
    
    printf("%s \n\n",glGetString(GL_VERSION)) ;
    

    
    
    //下面两种方式二选一：
    //1.使用全局的字符串加载shader
//    compileShaders();
    
    //2.使用c++类加载shader资源文件
    
    

    
    
        ZZLShader myshader("./shaderFiles/vertexShader.vs", "./shaderFiles/fragmentShader.frag");
    //
   
    
    process();
    
    textureProcess();
    while (!glfwWindowShouldClose(window))
    {
        
        glClearColor(0.2, 0.2, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        /*  use uniform global var..
         
        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = sin(timeValue)/2 + 0.5f;
        GLuint vertexColorLocation = glGetUniformLocation(shaderProgram, "changeColor");
        glUseProgram(shaderProgram);
        
        glUniform4f(vertexColorLocation, 0.5f, 0.5f, greenValue, 1.0f);
        
         */
        //1.使用全局的字符串加载着色器程序方式
//        glUseProgram(shaderProgram);
        
        
        //2.使用C++类加载加载着色器程序方式
        myshader.UseShader();
        
        // transform
        /*
        glm::mat4 trans;
        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = sin(timeValue)/2 + 0.5f;
//
//        trans = glm::scale(trans, glm::vec3(greenValue,greenValue,0.0f));
        trans = glm::rotate(trans, (GLfloat)glfwGetTime() * 2.0f, glm::vec3(0.0,0.0,1.0f));
        trans = glm::translate(trans, glm::vec3(greenValue,greenValue,0.0f));
        GLuint transfromLoc = glGetUniformLocation(myshader.programId, "transform");
        glUniformMatrix4fv(transfromLoc, 1, GL_FALSE, glm::value_ptr(trans));
        
        */
        
        
        glm::mat4 modeMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 perspectiveMatrix;
        

//        viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0,0.0,-3.0));
        GLfloat camX = sinf(glfwGetTime())*10.0f;
        GLfloat camZ = cos(glfwGetTime())*10.0f;
        
        viewMatrix = glm::lookAt(glm::vec3(camX,0.0f,camZ), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
        perspectiveMatrix = glm::perspective(glm::radians(field_of_view), (GLfloat)(640.0/480.0), 0.1f, 100.0f);
        
        GLuint modelLocal = glGetUniformLocation(myshader.programId, "modeMatrix");
        GLuint viewLocal = glGetUniformLocation(myshader.programId, "viewMatrix");
        GLuint perspectiveLocal = glGetUniformLocation(myshader.programId, "perspectiveMatrix");
        
        
        glUniformMatrix4fv(viewLocal, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(perspectiveLocal, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
        
        
        
        glBindVertexArray(VAO[0]);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    

        glBindVertexArray(VAO[2]);
        for (GLuint i= 0; i<10; i++) {
            modeMatrix = glm::translate(modeMatrix, cubePositions[i]*0.3f);
//            modeMatrix = glm::rotate(modeMatrix, (GLfloat)glm::radians(glfwGetTime()*100), glm::vec3(0.5f,0.5,0.5));
            glUniformMatrix4fv(modelLocal, 1, GL_FALSE, glm::value_ptr(modeMatrix));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        
 
        glfwPollEvents();
    }
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(3, VAO);
    glDeleteBuffers(3, VBO);
    
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
        field_of_view+=3.0f;
    }else if (key == GLFW_KEY_UP && action == GLFW_REPEAT) {
        field_of_view-=3.0f;
    }
}

