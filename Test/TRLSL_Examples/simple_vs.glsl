#version 330 core

in vec3 VS_INPUT_pos;
in vec4 VS_INPUT_color;

out vec4 VS_OUTPUT_color;

uniform mat4 UniformBlock_model;
uniform mat4 UniformBlock_view;
uniform mat4 UniformBlock_proj;
uniform vec4 UniformBlock_globalColor;


vec3 func(vec3 a)
{
	return a;
}


void main()
{
	gl_Position = VS_INPUT_pos;
	VS_OUTPUT_color = VS_INPUT_color;

	func(VS_INPUT_pos);

	vec3 res = func(VS_INPUT_pos);
}