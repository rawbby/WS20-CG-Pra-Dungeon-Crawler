#version 450

uniform sampler2D u_basecolor;
uniform sampler2D u_mrao;
uniform sampler2D u_normal;

uniform vec3 u_light_positions[16];
uniform vec3 u_light_colors[16];
uniform int u_lights_count;

in vec3 f_position;
in vec3 f_normal;
in vec2 f_tex_coords;

out vec4 o_color;

void main()
{
    vec3 basecolor = texture(u_basecolor, f_tex_coords).xyz;
    vec3 mrao      = texture(u_mrao, f_tex_coords).xyz;
    vec3 normal    = texture(u_normal, f_tex_coords).xyz;

    vec3 n = normalize(f_normal);
    vec3 v = normalize(-f_position);

    vec3 intensity = vec3(0.0, 0.0, 0.0);

    for (int i = 0; i < u_lights_count; ++i)
    {
        vec3 light_position  = u_light_positions[i];
        vec3 light_color     = u_light_colors[i];

        vec3 l = normalize(light_position - f_position);

        vec3 r = reflect(-l, n);

        vec3 Ia =                               light_color;
        vec3 Id =     max(dot(n, l), 0.0)     * light_color;
        vec3 Is = pow(max(dot(v, r), 0.0), 4) * light_color;

        intensity += Ia + Id + Is;
    }

    o_color = vec4(basecolor * intensity, 1.0);
}
