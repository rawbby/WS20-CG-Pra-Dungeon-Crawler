#version 450

uniform sampler2D u_basecolor;
uniform sampler2D u_mrao;
uniform sampler2D u_normal;

uniform vec3 u_lights[16];   // TODO
uniform uint u_lights_count; // TODO

layout(location = 0) in vec3 f_position;
layout(location = 1) in vec3 f_normal;
layout(location = 2) in vec2 f_tex_coords;

out vec4 o_color;

void main()
{
    vec4 basecolor = texture(u_basecolor, f_tex_coords);
    vec3 mrao      = texture(u_mrao, f_tex_coords).xyz;
    vec3 normal    = texture(u_normal, f_tex_coords).xyz;

    o_color = basecolor;
}
