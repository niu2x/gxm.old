#version 300 es

precision highp float;

uniform sampler2D texture_0;
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform sampler2D texture_3;

in vec4 v_color;
in vec2 v_uv;

out vec4 color;

void main() {
 	float gamma = 2.2;

 	color = vec4(0 ,0, 0, 1);
 	if(v_uv.x < 0.5){
 		if(v_uv.y < 0.5) {
			color.r =  texture2D(texture_0, v_uv).r;
 		}
 		else{
			color.g =  texture2D(texture_1, v_uv).g;
 		}
 	}
 	else{
 		if(v_uv.y < 0.5) {
			color.b =  texture2D(texture_2, v_uv).b;

 		}
 		else{
			color =  texture2D(texture_3, v_uv);
 		}
 	}
 	color *= v_color;
	color.rgb = pow(color.rgb, vec3(1.0/gamma));
}