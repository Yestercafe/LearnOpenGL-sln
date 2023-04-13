#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 outColor;
out vec2 TexCoord;
out vec3 outPos;

void main()
{
    gl_Position = vec4(aPos, 1);
    outColor = aColor;
    TexCoord = aTexCoord;
    outPos = aPos;
}
