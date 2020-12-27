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

    vec4 position4 = u_model_view_matrix * vec4(position, 1.0);
    f_position = position4.xyz / position4.w;

    f_normal = vec3(u_model_view_matrix * vec4(v_normal, 0.0));
    f_tex_coords = v_tex_coords;

    gl_Position = u_projection_matrix * position4;
}
