#version 450

uniform sampler2D u_height;
uniform mat4 u_model_view_matrix;
uniform mat4 u_projection_matrix;

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_tex_coords;

out vec3 f_position;
out vec3 f_normal;
out vec2 f_tex_coords;

void main()
{
    vec3 position = v_position + texture(u_height, v_tex_coords).x * v_normal * 0.075;

    f_position = position;
    f_normal = v_normal;
    f_tex_coords = v_tex_coords;

    gl_Position = u_projection_matrix * u_model_view_matrix * vec4(position, 1.0);
}
