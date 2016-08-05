//
//  lightDemo.cpp
//  learnOpengl2
//
//  Created by smart on 16/8/5.
//  Copyright © 2016年 Smart. All rights reserved.
//

#include "lightDemo.hpp"
#include <iostream>
#include "glfw3.h"
#include <math.h>
#include <OpenGL/gl3.h>
#include "ZZLShader.hpp"
#include "SOIL.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"
#include "Carmer.hpp"



GLuint lightShaderProgram;
GLuint lightVAO[3];
GLuint lightVBO[3];
GLuint lighttexture1;

GLfloat light_field_of_view = 45.0f;




GLfloat lightcubeVertices[] = {
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    
    -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
    
    -0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
};



// Function prototypes
void light_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);



void lightprocess() {
    
    glGenVertexArrays(1, lightVAO);
    glGenBuffers(1, lightVBO);
    
    // cube
    glBindVertexArray(lightVAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightcubeVertices), lightcubeVertices, GL_STATIC_DRAW);
    
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // TexCoord attribute
    
    glBindVertexArray(0); // Unbind VAO
    
    
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO[0]);
    // Set the vertex attributes (only position data for the lamp))
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    
    
}


/*
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

*/


int processLightDemo(void)
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

    glfwSetKeyCallback(window, light_key_callback);
    

    glViewport(0, 0, 640, 480);

    glEnable(GL_DEPTH_TEST);
    
    
    printf("%s \n\n",glGetString(GL_VERSION)) ;
    

    
    
    
    ZZLShader myshader("./shaderFiles/vertexShader.vs", "./shaderFiles/fragmentShader.frag");
    //
    
    
    lightprocess();
    
    while (!glfwWindowShouldClose(window))
    {
        
        glClearColor(0.2, 0.2, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        myshader.UseShader();

        glm::mat4 modeMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 perspectiveMatrix;
        
        
        //        viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0,0.0,-3.0));
        GLfloat camX = sinf(glfwGetTime())*10.0f;
        GLfloat camZ = cos(glfwGetTime())*10.0f;
        
        viewMatrix = glm::lookAt(glm::vec3(camX,0.0f,camZ), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
        perspectiveMatrix = glm::perspective(glm::radians(light_field_of_view), (GLfloat)(640.0/480.0), 0.1f, 100.0f);
        
        GLuint modelLocal = glGetUniformLocation(myshader.programId, "modeMatrix");
        GLuint viewLocal = glGetUniformLocation(myshader.programId, "viewMatrix");
        GLuint perspectiveLocal = glGetUniformLocation(myshader.programId, "perspectiveMatrix");
        
        
        glUniformMatrix4fv(viewLocal, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(perspectiveLocal, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
        
        
        
        glBindVertexArray(lightVAO[0]);
        glBindTexture(GL_TEXTURE_2D, lighttexture1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        
        glBindVertexArray(lightVAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        
        glBindVertexArray(lightVAO[2]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        
        
        glfwPollEvents();
    }
    glDeleteProgram(lightShaderProgram);
    glDeleteVertexArrays(3, lightVAO);
    glDeleteBuffers(3, lightVBO);
    
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void light_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
        light_field_of_view+=3.0f;
    }else if (key == GLFW_KEY_UP && action == GLFW_REPEAT) {
        light_field_of_view-=3.0f;
    }
}