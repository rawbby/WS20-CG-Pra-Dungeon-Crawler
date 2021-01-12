#version 450 core

uniform sampler2D u_height;

uniform mat4 u_projection_matrix;
uniform mat4 u_model_view_matrix;

uniform mat4 u_joint_transformations[64];

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec2 v_tex_coords;

layout (location = 3) in uint v_joint_indices[3];
layout (location = 4) in vec3 v_joint_weights;

out vec2 f_tex_coords;
out vec3 f_position;
out vec3 f_normal;

vec4 get_position_from_map()
{
    float height = texture(u_height, v_tex_coords).x * 0.046875;
    return u_model_view_matrix * vec4(v_position + (height * v_normal), 1.0);
}

void main()
{
    vec4 position = get_position_from_map();

    // mat4 bone_transformation = u_joint_transformations[v_joint_indices[0]] * v_joint_weights[0];
    // bone_transformation += u_joint_transformations[v_joint_indices[1]] * v_joint_weights[1];
    // bone_transformation += u_joint_transformations[v_joint_indices[2]] * v_joint_weights[2];
    // position = bone_transformation * position;

    f_tex_coords = v_tex_coords;
    f_position   = position.xyz / position.w;
    f_normal     = mat3(u_model_view_matrix) * v_normal;

    gl_Position  =  u_projection_matrix * position;
}
