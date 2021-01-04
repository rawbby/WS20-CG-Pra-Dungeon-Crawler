#include <GL/glew.h>
#include <GL/GL.h>

#include "engine/service/ShadowMapService.hpp"

#include <engine/component/GlPointLightComponent.hpp>
#include <engine/component/GlMaterialComponent.hpp>

#include <engine/component/PositionComponent.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <spdlog/spdlog.h>

namespace engine::service
{
    void ShadowMap::init ()
    {
    }

    void ShadowMap::update (entt::registry &reg)
    {
        using namespace component;

        int shadow_map_size = 256;

        for (const auto entity: reg.group<GlPointLightComponent>(entt::get<PositionComponent>))
        {
            auto &position = reg.get<PositionComponent>(entity);
            auto &data = reg.get<GlPointLightComponent>(entity);

            auto render_group = reg.group<GlMaterialComponent>(entt::get<PositionComponent>);

            // create shadow map
            glEnable(GL_DEPTH_TEST);
            glm::vec3 lightPos = glm::vec3{position[0], data.height, position[1]};

            GLuint shadow_map = 0;
            if (shadow_map == 0)
            {
                glGenTextures(1, &shadow_map);
            }
            glBindTexture(GL_TEXTURE_CUBE_MAP, shadow_map);
            for (unsigned int i = 0; i < 6; ++i)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, shadow_map_size, shadow_map_size, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
            }
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            GLuint shadow_fbo = 0;
            glGenFramebuffers(1, &shadow_fbo);
            glBindFramebuffer(GL_FRAMEBUFFER, shadow_fbo);
            glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadow_map, 0);

            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);

            float near_plane = 0.125f, far_plane = 10.0f;

            glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), 1.0f, near_plane, far_plane);
            std::vector<glm::mat4> shadowTransforms;
            shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
            shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
            shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)));
            shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)));
            shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
            shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));

            glViewport(0, 0, shadow_map_size, shadow_map_size);

            glClearColor(0.1f, 0.4f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUseProgram(data.program);
            glUniformMatrix4fv(glGetUniformLocation(data.program, "u_shadow_matrices"), 6, GL_FALSE, glm::value_ptr(*shadowTransforms.data()));
            glUniform1f(glGetUniformLocation(data.program, "u_far_plane"), far_plane);
            glUniform3f(glGetUniformLocation(data.program, "u_light_pos"), lightPos.x, lightPos.y, lightPos.z);

            for (const auto material_entry: render_group)
            {
                const auto[material_position, material] = render_group.get<PositionComponent, GlMaterialComponent>(material_entry);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, material.material.tex_height);

                glUniform1i(glGetUniformLocation(data.program, "u_height"), 0);

                const auto x = material_position[0];
                const auto z = material_position[1];
                const auto model_view_matrix = glm::translate(glm::mat4{1.0f}, glm::vec3{x, 0.0f, z}) * material.model_view_matrix;

                glBindVertexArray(material.vao);
                glUniformMatrix4fv(glGetUniformLocation(data.program, "u_model_view_matrix"), 1, GL_FALSE, glm::value_ptr(model_view_matrix));
                glDrawElements(GL_TRIANGLES, material.count, GL_UNSIGNED_INT, nullptr);
            }

            data.tex_shadow = shadow_map;
            glDeleteFramebuffers(1, &shadow_fbo);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
