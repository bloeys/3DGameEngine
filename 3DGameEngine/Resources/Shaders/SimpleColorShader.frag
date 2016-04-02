#version 130

in vec4 color;
//in vec2 uv;

out vec4 finalColor;

uniform float time;
//uniform sampler2D tex;

void main()
{
	finalColor = vec4(color.r * (sin(time) + 1) * 0.5f, color.g * (cos(time) + 1) * 0.5f, color.b * (cos(time) + 1) * 0.5f, 1);
	//finalColor = color;
	//finalColor = texture(tex, uv);
}