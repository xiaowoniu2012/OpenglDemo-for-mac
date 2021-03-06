
//  Created by zelong zou on 16/7/26.
//  Copyright © 2016年 Smart. All rights reserved.
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
out vec4 fragmentColor;
out vec2 TexCoord;
//uniform mat4 transform;

uniform mat4 modeMatrix;
uniform mat4 viewMatrix;
uniform mat4 perspectiveMatrix;

void main() {
//    gl_Position = transform*vec4(position, 1.0f);
    gl_Position = perspectiveMatrix * viewMatrix * modeMatrix *vec4(position,1.0f);
    fragmentColor = vec4(1.0,1.0,1.0,1.0f);
    TexCoord = vec2(texCoord.x,1.0-texCoord.y);
}



