#version 330 core

in vec4 VS_OUTPUT_color;


void main()
{
	gl_Color = VS_OUTPUT_color;
}