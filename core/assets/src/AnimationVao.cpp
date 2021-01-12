#include <GL/glew.h>
#include <GL/GL.h>

#include <asset/Asset.hpp>

#include <geometries/Plane.hpp>
#include <geometries/Sphere.hpp>

#include <span>
#include <AnimatedMesh.hpp>
#include <DaeLoader.hpp>

namespace
{
    GLuint generate_vao (const AnimatedMesh& mesh)
    {
        GLuint vao;
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);

        GLuint pointsBuffer;
        glGenBuffers(1, &pointsBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer);
        glBufferData(GL_ARRAY_BUFFER, mesh.vertex_count * sizeof(glm::vec3), mesh.vertices.get(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        GLuint normalsBuffer;
        glGenBuffers(1, &normalsBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
        glBufferData(GL_ARRAY_BUFFER, mesh.vertex_count * sizeof(glm::vec3), mesh.normals.get(), GL_STATIC_DRAW);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(1);

        GLuint texCoordsBuffer;
        glGenBuffers(1, &texCoordsBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, texCoordsBuffer);
        glBufferData(GL_ARRAY_BUFFER, mesh.vertex_count * sizeof(glm::vec2), mesh.tex_coords.get(), GL_STATIC_DRAW);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(2);

        GLuint jointIndicesBuffer;
        glGenBuffers(1, &jointIndicesBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, jointIndicesBuffer);
        glBufferData(GL_ARRAY_BUFFER, mesh.joint_count * sizeof(uint32_t) * 3,  mesh.joint_indices.get(), GL_STATIC_DRAW);

        glVertexAttribPointer(3, 3, GL_UNSIGNED_INT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(3);

        GLuint jointWeightsBuffer;
        glGenBuffers(1, &jointWeightsBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, jointWeightsBuffer);
        glBufferData(GL_ARRAY_BUFFER, mesh.joint_count * sizeof(glm::vec3), mesh.joint_weights.get(), GL_STATIC_DRAW);

        glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(4);

        GLuint indicesBuffer;
        glGenBuffers(1, &indicesBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices_count * sizeof(uint32_t), mesh.indices.get(), GL_STATIC_DRAW);

        glBindVertexArray(GL_NONE);
        glDeleteBuffers(1, &pointsBuffer);
        glDeleteBuffers(1, &normalsBuffer);
        glDeleteBuffers(1, &texCoordsBuffer);
        glDeleteBuffers(1, &jointIndicesBuffer);
        glDeleteBuffers(1, &jointWeightsBuffer);
        glDeleteBuffers(1, &indicesBuffer);

        const auto status = glGetError();
        if (GL_NO_ERROR != status)
        {
            spdlog::error("OPENGL ERROR! (FILE: \"{}\", LINE: \"{}\")\n{}", __FILE__, __LINE__, status);

            glDeleteVertexArrays(1, &vao);
            return GL_NONE;
        }

        return vao;
    }
}

namespace asset::internal
{
    void init_animation_vaos ()
    {
        vao::animation::player_mesh = dae_loader::load_animated_mesh("dae/bone0.dae");
        vao::animation::player_animation = dae_loader::load_animation("dae/bone0.dae");

        vao::animation::player_count = vao::animation::player_mesh.indices_count;
        vao::animation::player = generate_vao(vao::animation::player_mesh);
    }
}
