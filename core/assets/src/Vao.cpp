#include <GL/glew.h>
#include <GL/GL.h>

#include <asset/Asset.hpp>

#include <geometries/Plane.hpp>
#include <geometries/Sphere.hpp>

#include <span>

namespace
{
    GLuint generate_vao (std::span<glm::vec3> points, std::span<uint32_t> indices, std::span<glm::vec3> normals, std::span<glm::vec2> tex_coords)
    {
        GLuint vao;
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);

        GLuint pointsBuffer;
        glGenBuffers(1, &pointsBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer);
        glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        GLuint normalsBuffer;
        glGenBuffers(1, &normalsBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(1);

        GLuint texCoordsBuffer;
        glGenBuffers(1, &texCoordsBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, texCoordsBuffer);
        glBufferData(GL_ARRAY_BUFFER, tex_coords.size() * sizeof(glm::vec2), tex_coords.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(2);

        GLuint indicesBuffer;
        glGenBuffers(1, &indicesBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(GL_NONE);
        //glDeleteBuffers(1, &pointsBuffer);
        //glDeleteBuffers(1, &texCoordsBuffer);
        //glDeleteBuffers(1, &indicesBuffer);
        //glDeleteBuffers(1, &normalsBuffer);

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
    void init_vaos ()
    {
        // initialize base plane
        {
            constexpr size_t divisions = 120;

            auto plane_points = geometries::generate_plane_back_points(divisions);
            auto plane_indices = geometries::generate_plane_indices(divisions);
            auto plane_normals = geometries::generate_plane_back_normals(divisions);
            auto plane_tex_coords = geometries::generate_plane_tex_coords(divisions);

            vao::plane = generate_vao(plane_points, plane_indices, plane_normals, plane_tex_coords);
            vao::plane_count = static_cast<GLsizei> (plane_indices.size());
        }

        // initialize base sphere
        {
            constexpr size_t slices = 32;
            constexpr size_t stacks = 32;

            auto sphere_points = geometries::generate_sphere_points(slices, stacks);
            auto sphere_indices = geometries::generate_sphere_indices(slices, stacks);
            auto sphere_normals = geometries::generate_sphere_normals(slices, stacks);
            auto sphere_tex_coords = geometries::generate_sphere_tex_coords(slices, stacks);

            vao::sphere = generate_vao(sphere_points, sphere_indices, sphere_normals, sphere_tex_coords);
            vao::sphere_count = static_cast<GLsizei> (sphere_indices.size());
        }
    }
}
