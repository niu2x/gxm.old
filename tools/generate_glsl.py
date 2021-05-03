# -*- coding: utf-8 -*-
import os

from jinja2 import Template

files = os.listdir('../res/glsl/')


glsl = []
for v in files:
	name, shader_type = v.split('.')
	fp = open('../res/glsl/' + v, 'r')
	glsl.append({
		'name': name,
		'shader_type': shader_type,
		'src': fp.read(),

	})
	fp.close()


glsl_h = Template("""
#ifndef GXM_GLSL_H
#define GXM_GLSL_H
namespace gxm {
struct glsl{
{% for v in glsl %}
static const char * {{  v.name }}_{{v.shader_type}};
{% endfor %}
};
}
#endif
""")

glsl_cpp = Template("""
#include "glsl.h"
namespace gxm {
{% for v in glsl %}
const char * glsl::{{  v.name }}_{{v.shader_type}} = R"GLSL(
{{v.src}}
)GLSL";
{% endfor %}
}
""")

fp = open('../src/gxm/glsl.h', 'w')
fp.write(glsl_h.render(glsl=glsl))
fp.close()

fp = open('../src/gxm/glsl.cpp', 'w')
fp.write(glsl_cpp.render(glsl=glsl))
fp.close()
