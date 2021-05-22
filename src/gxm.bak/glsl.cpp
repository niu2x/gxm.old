
#include "glsl.h"
namespace gxm {

const char *glsl::framebuffer_frag = R"GLSL(
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
)GLSL";

const char *glsl::gaussian_filter_frag = R"GLSL(
#version 300 es

precision highp float;
precision highp sampler2D;

uniform sampler2D texture_0;

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
)GLSL";

const char *glsl::default_vert = R"GLSL(
#version 300 es

precision highp float;

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 v_color;

void main() {
	v_color = color;
	gl_Position = vec4(position, 1.0);
}
)GLSL";

const char *glsl::default_frag = R"GLSL(
#version 300 es

precision highp float;

in vec4 v_color;
out vec4 color;

void main() {
	color = v_color;
}
)GLSL";

const char *glsl::framebuffer_vert = R"GLSL(
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
)GLSL";

} // namespace gxm