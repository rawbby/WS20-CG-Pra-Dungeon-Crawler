#include <GL/glew.h>
#include <GL/GL.h>

#include <engine/service/RenderService.hpp>

namespace engine::service
{
    void Render::init ()
    {
        glewExperimental = GL_TRUE;
        glewInit();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_TEXTURE_2D);
    }

    void Render::update (entt::registry &reg, glm::mat4 projection_matrix, glm::mat4 camera_matrix)
    {
        using namespace component;

        {
            auto render_group = reg.group<PositionComponent, GlMaterialComponent>();

            for (const auto entity: render_group)
            {
                auto[position, data] = render_group.get<PositionComponent, GlMaterialComponent>(entity);

                const auto x = position[0];
                const auto z = position[1];
                const auto model_view_matrix = camera_matrix * glm::translate(glm::mat4{1.0f}, glm::vec3{x, 0.0f, z}) * data.model_view_matrix;

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

                glUniform1i(glGetUniformLocation(data.program, "u_basecolor"), 0);
                glUniform1i(glGetUniformLocation(data.program, "u_height"), 1);
                glUniform1i(glGetUniformLocation(data.program, "u_mrao"), 2);
                glUniform1i(glGetUniformLocation(data.program, "u_normal"), 3);

                glUniformMatrix4fv(glGetUniformLocation(data.program, "u_projection_matrix"), 1, GL_FALSE, glm::value_ptr(projection_matrix));
                glUniformMatrix4fv(glGetUniformLocation(data.program, "u_model_view_matrix"), 1, GL_FALSE, glm::value_ptr(model_view_matrix));

                glDrawElements(GL_TRIANGLES, data.count, GL_UNSIGNED_INT, nullptr);
            }
        }
    }
}
