#version 450

uniform sampler2D u_height;

uniform mat4 u_model_view_matrix;
uniform float u_height_mult;

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_tex_coords;

void main()
{
    float height = texture(u_height, v_tex_coords).x * u_height_mult;
    gl_Position = u_model_view_matrix * vec4(v_position + height * v_normal, 1.0);
    // gl_Position = u_model_view_matrix * vec4(v_position, 1.0);
}
