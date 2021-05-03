#version 300 es

precision highp float;

uniform sampler2D texture_0;

in vec4 v_color;
in vec2 v_uv;

out vec4 color;

void main() {
 	float gamma = 2.2;
	color = texture2D(texture_0, v_uv);
 	color *= v_color;
	//color.rgb = pow(color.rgb, vec3(1.0/gamma));
}