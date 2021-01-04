#version 450

uniform vec3 u_light_pos;
uniform float u_far_plane;

in vec4 f_position;

void main()
{
    float ld = length(f_position.xyz - u_light_pos);
    ld = ld / u_far_plane;

    gl_FragDepth = ld;
}
