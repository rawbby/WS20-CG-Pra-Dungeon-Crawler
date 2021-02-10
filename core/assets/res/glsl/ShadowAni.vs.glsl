#version 450

layout(location = 0) in vec3 v_vertex;
layout(location = 2) in vec4 v_joint_indices;
layout(location = 3) in vec4 v_joint_weights;

uniform mat4 u_model_view_matrix;
uniform mat4 u_joints[48];

void main()
{
    mat4 joint_transformation
    = v_joint_weights[0] * u_joints[int(v_joint_indices[0])]
    + v_joint_weights[1] * u_joints[int(v_joint_indices[1])]
    + v_joint_weights[2] * u_joints[int(v_joint_indices[2])]
    + v_joint_weights[3] * u_joints[int(v_joint_indices[3])];

    //gl_Position = u_model_view_matrix * vec4(v_vertex, 1.0);
    gl_Position = u_model_view_matrix * joint_transformation * vec4(v_vertex, 1.0f);
}
