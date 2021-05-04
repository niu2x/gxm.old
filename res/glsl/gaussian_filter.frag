#version 300 es

precision highp float;
precision highp sampler2D;

uniform sampler2D texture_0;
uniform float texture_0;

in vec4 v_color;
in vec2 v_uv;

out vec4 color;
void main()
{
	float dx = dFdx(v_uv).x;
	float dy = dFdy(v_uv).y;

	color = texture2D(texture_0, v_uv) * 0.2270270270;
	color += texture2D(texture_0, vec2(v_uv.x+dx, v_uv.y)) * 0.3162162162;
	color += texture2D(texture_0, vec2(v_uv.x-dx, v_uv.y)) * 0.3162162162;
	color += texture2D(texture_0, vec2(v_uv.x, v_uv.y+dy)) * 0.0702702703;
	color += texture2D(texture_0, vec2(v_uv.x, v_uv.y-dy)) * 0.0702702703;

}