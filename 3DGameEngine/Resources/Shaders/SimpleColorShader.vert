#version 130

in vec3 vertPos;
in vec4 vertColor;

out vec4 color;

uniform mat4 transformation;

void main()
{
	color = vec4(vertPos, 1);
	gl_Position = transformation * vec4(vertPos, 1);
}