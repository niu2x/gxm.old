#version 300 es

precision highp float;

in vec4 v_color;
in vec2 v_uv;

out vec4 color;

void main() {
 	float gamma = 2.2;

	color = v_color;

	if(v_uv.y >= 0.5)
    	color.rgb = pow(color.rgb, vec3(1.0/gamma));
}