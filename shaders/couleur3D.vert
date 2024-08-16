#version 150

in vec3 inPosition;
in vec3 inColor;

out vec3 fragColor;

uniform mat4 modelview;
uniform mat4 projection;

void main()
{
    gl_Position = projection * modelview * vec4(inPosition, 1.0);
    fragColor = inColor;
}
