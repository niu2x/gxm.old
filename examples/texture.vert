#version 300 es

precision highp float;

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 uv;

out vec4 v_color;
out vec2 v_uv;

void main() {
	v_color = color;
	v_uv = uv;
	
	gl_Position = vec4(position, 1.0);
}