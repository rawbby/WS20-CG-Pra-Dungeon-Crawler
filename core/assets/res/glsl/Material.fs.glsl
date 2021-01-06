#version 450 core

uniform sampler2D u_basecolor;
uniform sampler2D u_mrao;
uniform samplerCube u_shadow_map;

uniform vec3 u_light_positions[16];
uniform vec3 u_light_colors[16];
uniform int u_lights_count;
uniform float u_far_plane;

in vec3 f_position;
in vec3 f_normal;
in vec2 f_tex_coords;

out vec4 o_color;

float ShadowCalculation(vec3 fragPos)
{
    vec3 fragToLight = fragPos - u_light_positions[0];
    float closestDepth = texture(u_shadow_map, fragToLight).r;
    closestDepth *= u_far_plane;
    float currentDepth = length(fragToLight);

    float bias = 0.05;

    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    return shadow;
}

void main()
{
    vec3 basecolor = texture(u_basecolor, f_tex_coords).xyz;
    vec3 mrao      = texture(u_mrao, f_tex_coords).xyz;

    vec3 n = normalize(f_normal);
    vec3 v = normalize(-f_position);

    vec3 intensity = vec3(0.0, 0.0, 0.0);

    //for (int i = 0; i < u_lights_count; ++i)
    //{
    //    vec3 light_position  = u_light_positions[i];
    //    vec3 light_color     = u_light_colors[i];

    //    vec3 l = normalize(light_position - f_position);

    //    vec3 r = reflect(-l, n);

    //    vec3 Ia =                                                 vec3(0.0) * light_color;
    //    vec3 Id =     max(dot(n, l), 0.0)                       * vec3(0.95) * light_color;
    //    vec3 Is = pow(max(dot(v, r), 0.0), 1.0 + mrao[1] * 8.0) * vec3(0.25) * light_color;

    //    intensity += Ia + Id + Is;
    //}

    vec3 light_position  = u_light_positions[0];
    vec3 light_color     = u_light_colors[0];
    vec3 l = normalize(light_position - f_position);
    vec3 r = reflect(-l, n);
    vec3 Ia =                                                 vec3(0.1) * light_color;
    vec3 Id =     max(dot(n, l), 0.0)                       * vec3(0.95) * light_color;
    vec3 Is = pow(max(dot(v, r), 0.0), 1.0 + mrao[1] * 8.0) * vec3(0.25) * light_color;

    //float shadow = ShadowCalculation(f_position);
    //intensity += Ia + (1.0 - shadow) * (Id + Is);

    //o_color = vec4(basecolor * intensity, 1.0);
    o_color = vec4(basecolor, 1.0);
}
