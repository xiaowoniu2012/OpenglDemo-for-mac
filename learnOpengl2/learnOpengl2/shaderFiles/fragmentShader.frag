//  Created by zelong zou on 16/7/26.
//  Copyright © 2016年 Smart. All rights reserved.
#version 330 core
in vec4 fragmentColor;
in vec2 TexCoord;
out vec4 color;

uniform sampler2D ourTexture;
void main()
{
    color = texture(ourTexture,TexCoord);
    //*fragmentColor
}