#version 450 core

uniform sampler2D u_height;
uniform sampler2D u_normal;

uniform mat4 u_model_view_matrix;
uniform mat4 u_projection_matrix;

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_tex_coords;

out vec3 f_position;
out vec3 f_normal;
out vec2 f_tex_coords;

mat3 rotation_of(vec3 v1, vec3 v2)
{
    vec3 axis = cross(v1, v2);

    const float cosA = dot(v1, v2);
    const float k = 1.0f / (1.0f + cosA);

    return mat3(
    (axis.x * axis.x * k) + cosA,
    (axis.y * axis.x * k) - axis.z,
    (axis.z * axis.x * k) + axis.y,
    (axis.x * axis.y * k) + axis.z,
    (axis.y * axis.y * k) + cosA,
    (axis.z * axis.y * k) - axis.x,
    (axis.x * axis.z * k) - axis.y,
    (axis.y * axis.z * k) + axis.x,
    (axis.z * axis.z * k) + cosA
    );
}

void main()
{
    vec3 normal = texture(u_normal, v_tex_coords).xyz;
    mat3 rotation = rotation_of(vec3(0.0, 0.0, 1.0), normal);

    f_normal = rotation * vec3(u_model_view_matrix * vec4(v_normal, 1.0) - u_model_view_matrix[3]);

    f_tex_coords = v_tex_coords;

    float height = texture(u_height, v_tex_coords).x * 0.0625;

    vec4 position = u_model_view_matrix * vec4(v_position + height * v_normal, 1.0);
    f_position = position.xyz / position.w;
    gl_Position = u_projection_matrix * position;
}
