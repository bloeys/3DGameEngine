#version 130

in vec3 vertPos;
in vec4 vertColor;

out vec4 color;
//out vec2 uv;

uniform mat4 transformation;

void main()
{
	color = vertColor*vec4(vertPos.xyz,1);
	//uv = vertPos.xy;
	gl_Position = transformation * vec4(vertPos, 1);
}