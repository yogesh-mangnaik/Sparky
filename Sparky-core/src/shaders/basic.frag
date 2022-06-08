#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;

in DATA{
	vec4 position;
	vec4 color;
} fs_in;

void main()
{
	float intensity = 0.5 / (length(fs_in.position.xy - light_pos) + 0.5);
	color = fs_in.color * intensity;
}