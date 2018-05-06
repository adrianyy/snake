#version 450 core

uniform vec3 input_color;
out vec4	 color;

void main() 
{
	color = vec4(input_color, 1.0);
}