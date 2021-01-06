#version 450 core

uniform sampler2D u_basecolor;
uniform sampler2D u_normal;
uniform sampler2D u_mrao;

uniform samplerCubeArray u_shadow_maps;

uniform vec3 u_light_positions[16];
uniform vec3 u_light_colors[16];
uniform int  u_lights_count;

uniform float u_far_plane;

uniform vec3 u_camera_position;

in    vec3  f_position;
in    vec3  f_normal;
in    vec2  f_tex_coords;

in    vec4  f_pos_light_space;
out   vec4  o_color;
const float pi = 3.14159265359;

float calculate_shadow(vec3 frag_position, int light_index)
{
    vec3 frag_to_light = frag_position - u_light_positions[light_index];

    float closest_depth = texture(u_shadow_maps, vec4(frag_to_light, light_index)).r;
    closest_depth *= u_far_plane;
    float current_depth = length(frag_to_light);

    //float bias = 0.0234375;
    float bias = 0.03;

    float shadow = current_depth - bias > closest_depth ? 1.0 : 0.0;

    return shadow;
}

vec3 get_normal_from_map()
{
    vec3 tangent_normal = texture(u_normal, f_tex_coords).xyz * 2.0 - 1.0;

    vec3 q1  = dFdx(f_position);
    vec3 q2  = dFdy(f_position);
    vec2 st1 = dFdx(f_tex_coords);
    vec2 st2 = dFdy(f_tex_coords);

    vec3 n   = normalize(f_normal);
    vec3 t   = normalize(q1*st2.t - q2*st1.t);
    vec3 b   = -normalize(cross(n, t));
    mat3 tbn = mat3(t, b, n);

    return normalize(tbn * tangent_normal);
}

float distribution_ggx(vec3 n, vec3 h, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(n, h), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = NdotH2 * (a2 - 1.0) + 1.0;
    denom = pi * denom * denom;

    return nom / denom;
}

float geometry_schlick_ggx(float n_dot_v, float roughness)
{
    float r     = roughness + 1.0;
    float k     = (r*r) / 8.0;

    float nom   = n_dot_v;
    float denom = n_dot_v * (1.0 - k) + k;

    return nom / denom;
}

float geometry_smith(vec3 n, vec3 v, vec3 l, float roughness)
{
    float n_dot_v = max(dot(n, v), 0.0);
    float n_dot_l = max(dot(n, l), 0.0);

    float ggx2    = geometry_schlick_ggx(n_dot_v, roughness);
    float ggx1    = geometry_schlick_ggx(n_dot_l, roughness);

    return ggx1 * ggx2;
}

vec3 fresnel_schlick(float cos_theta, vec3 f0)
{
    return f0 + (1.0 - f0) * pow(max(1.0 - cos_theta, 0.0), 5.0);
}

void main()
{
    vec3  basecolor = pow(texture(u_basecolor, f_tex_coords).rgb, vec3(2.2));
    vec3  mrao      = texture(u_mrao, f_tex_coords).rgb;
    float metallic  = mrao.r;
    float roughness = mrao.g;
    float ao        = mrao.g;

    vec3  n         = get_normal_from_map();
    vec3  v         = normalize(u_camera_position - f_position);

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)
    vec3 f0 = vec3(0.04);
    f0 = mix(f0, basecolor, metallic);

    // reflectance equation
    vec3 lo = vec3(0.0);

    for (int i = 0; i < u_lights_count; ++i)
    {
        if (calculate_shadow(f_position, i) == 1.0)
        {
            continue;
        }

        // calculate per-light radiance
        vec3  l           = normalize(u_light_positions[i] - f_position);
        vec3  h           = normalize(v + l);
        float distance    = length(u_light_positions[i] - f_position);
        float attenuation = 1.0 / (distance * distance);
        vec3  radiance    = u_light_colors[i] * attenuation;

        // Cook-Torrance BRDF
        float ndf = distribution_ggx(n, h, roughness);
        float g   = geometry_smith(n, v, l, roughness);
        vec3  f   = fresnel_schlick(max(dot(h, v), 0.0), f0);

        vec3  nominator   = ndf * g * f;
        float denominator = 4 * max(dot(n, v), 0.0) * max(dot(n, l), 0.0) + 0.001;// 0.001 to prevent divide by zero.
        vec3  specular    = nominator / denominator;

        // ks is equal to Fresnel
        vec3 ks = f;

        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kd = vec3(1.0) - ks;

        // multiply kD by the inverse metalness such that only non-metals
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kd *= 1.0 - metallic;

        // scale light by NdotL
        float n_dot_l = max(dot(n, l), 0.0);

        // add to outgoing radiance Lo
        // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
        lo += (kd * basecolor / pi + specular) * radiance * n_dot_l;
    }

    // ambient lighting (note that the next IBL tutorial will replace
    // this ambient lighting with environment lighting).
    vec3 ambient = vec3(0.03) * basecolor * ao;

    vec3 color = ambient + lo;

    color = color / (color + vec3(1.0));// HDR tonemapping
    color = pow(color, vec3(1.0/2.2));// gamma correct

    o_color = vec4(color, 1.0);
}
