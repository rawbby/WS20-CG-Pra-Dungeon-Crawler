#include <GL/glew.h>
#include <GL/GL.h>

#include "engine/service/RenderService.hpp"

#include <engine/component/GlRenderComponent.hpp>
#include <engine/component/GlMaterialComponent.hpp>
#include <engine/component/GlBlendMaterialComponent.hpp>
#include <engine/component/GlPointLightComponent.hpp>

#include <engine/component/PositionComponent.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <spdlog/spdlog.h>

namespace engine::service
{
    void Render::init ()
    {
        glewExperimental = GL_TRUE;
        glewInit();

        glEnable(GL_DEPTH_TEST);
    }

    void Render::update (entt::registry &reg, glm::mat4 projection_matrix, glm::mat4 camera_matrix, glm::vec3 camera_position, float width, float height)
    {
        using namespace component;

        std::vector<glm::vec3> light_positions;
        light_positions.reserve(16);

        std::vector<glm::vec3> light_colors;
        light_colors.reserve(16);

        std::vector<GLuint> light_tex_shadows;
        light_tex_shadows.reserve(16);

        // fetch point light sources
        {
            auto light_group = reg.group<GlPointLightComponent>(entt::get<PositionComponent>);

            for (const auto entity: light_group)
            {
                auto[position, data] = light_group.get<PositionComponent, GlPointLightComponent>(entity);

                light_positions.emplace_back(glm::vec3{position[0], data.height, position[1]});
                light_colors.push_back(data.color);
                light_tex_shadows.push_back(data.tex_shadow);

                if (light_positions.size() >= 16)
                {
                    break;
                }
            }
        }

        std::vector<GLint> shadow_map_indices{};
        shadow_map_indices.reserve(light_tex_shadows.size());

        for (size_t i = 0; i < light_tex_shadows.size(); ++i)
        {
            shadow_map_indices.emplace_back(4 + i);
        }

        // render material components
        {
            auto render_group = reg.group<GlMaterialComponent>(entt::get<PositionComponent>);

            float far_plane = 10.0f;

            for (const auto entity: render_group)
            {
                auto[position, data] = render_group.get<PositionComponent, GlMaterialComponent>(entity);

                const auto x = position[0];
                const auto z = position[1];
                const auto model_view_matrix = glm::translate(glm::mat4{1.0f}, glm::vec3{x, 0.0f, z}) * data.model_view_matrix;

                glUseProgram(data.program);
                glBindVertexArray(data.vao);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, data.material.tex_basecolor);

                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, data.material.tex_height);

                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, data.material.tex_mrao);

                glActiveTexture(GL_TEXTURE3);
                glBindTexture(GL_TEXTURE_2D, data.material.tex_normal);

                for (size_t i = 0; i < light_tex_shadows.size(); ++i)
                {
                    glActiveTexture(GL_TEXTURE4 + i);
                    glBindTexture(GL_TEXTURE_CUBE_MAP, light_tex_shadows[i]);
                }

                glUniform3fv(glGetUniformLocation(data.program, "u_light_positions"), static_cast<GLsizei> (light_positions.size()), glm::value_ptr(*light_positions.data()));
                glUniform3fv(glGetUniformLocation(data.program, "u_light_colors"), static_cast<GLsizei> (light_colors.size()), glm::value_ptr(*light_colors.data()));
                glUniform1i(glGetUniformLocation(data.program, "u_lights_count"), static_cast<GLsizei> (light_positions.size()));
                glUniform1f(glGetUniformLocation(data.program, "u_far_plane"), far_plane);

                glUniform3f(glGetUniformLocation(data.program, "u_camera_position"), camera_position.x, camera_position.y, camera_position.z);

                glUniform1i(glGetUniformLocation(data.program, "u_basecolor"), 0);
                glUniform1i(glGetUniformLocation(data.program, "u_height"), 1);
                glUniform1i(glGetUniformLocation(data.program, "u_mrao"), 2);
                glUniform1i(glGetUniformLocation(data.program, "u_normal"), 3);
                glUniform1iv(glGetUniformLocation(data.program, "u_shadow_maps"), static_cast<GLsizei> (shadow_map_indices.size()), shadow_map_indices.data());

                glUniformMatrix4fv(glGetUniformLocation(data.program, "u_projection_matrix"), 1, GL_FALSE, glm::value_ptr(projection_matrix * camera_matrix));
                glUniformMatrix4fv(glGetUniformLocation(data.program, "u_model_view_matrix"), 1, GL_FALSE, glm::value_ptr(model_view_matrix));

                glDrawElements(GL_TRIANGLES, data.count, GL_UNSIGNED_INT, nullptr);

                const auto status = glGetError();
                if (GL_NO_ERROR != status)
                {
                    spdlog::error(R"(OPENGL ERROR! (FILE: "{}", LINE: "{}", STATUS: "{}"))", __FILE__, __LINE__, status);
                }
            }

            for (const auto i : light_tex_shadows)
            {
                glDeleteTextures(1, &i);
            }
        }
    }
}
