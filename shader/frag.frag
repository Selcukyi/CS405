#version 330 core

in vec3 vertex_position;
out vec4 FragColor;

uniform int u_frame;

void main()
{
	FragColor = vec4(abs(vertex_position.x), abs(vertex_position.y), abs(vertex_position.z), 0.0f);
}
