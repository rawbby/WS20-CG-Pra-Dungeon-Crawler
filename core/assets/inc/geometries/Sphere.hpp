#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <vector>

namespace geometries
{
    inline std::vector<glm::vec3> generate_sphere_points (uint32_t slices, uint32_t stacks)
    {
        constexpr auto X_AXIS = glm::vec3{1.0f, 0.0f, 0.0f};
        constexpr auto Y_AXIS = glm::vec3{0.0f, 1.0f, 0.0f};
        constexpr auto PI = glm::radians(180.0f);
        constexpr auto TAU = glm::radians(360.0f);

        const auto part_x = PI / static_cast<float> (stacks - 1);
        const auto part_y = TAU / static_cast<float> (slices);

        std::vector<glm::vec3> points{};
        points.reserve(2 + (stacks - 2) * slices+1);

        const glm::vec3 point{0.0f, 0.5f, 0.0f};
        points.push_back(point);

        for (uint32_t i = 1; i < stacks - 1; ++i)
        {
            const auto rot_x = part_x * static_cast<float>(i);

            for (uint32_t j = 0; j < slices+1; ++j)
            {
                const auto rot_y = part_y * static_cast<float>(j);

                points.push_back(glm::rotate(glm::rotate(point, rot_x, X_AXIS), rot_y, Y_AXIS));
            }
        }

        points.emplace_back(0.0f, -0.5f, 0.0f);

        return points;
    }

    inline std::vector<glm::vec3> generate_sphere_normals (uint32_t slices, uint32_t stacks)
    {
        constexpr auto X_AXIS = glm::vec3{1.0f, 0.0f, 0.0f};
        constexpr auto Y_AXIS = glm::vec3{0.0f, 1.0f, 0.0f};
        constexpr auto PI = glm::radians(180.0f);
        constexpr auto TAU = glm::radians(360.0f);

        const auto part_x = PI / static_cast<float> (stacks - 1);
        const auto part_y = TAU / static_cast<float> (slices);

        std::vector<glm::vec3> normals{};
        normals.reserve(2 + (stacks - 2) * slices+1);

        const glm::vec3 normal{0.0f, 1.0f, 0.0f};
        normals.push_back(normal);

        for (uint32_t i = 1; i < stacks - 1; ++i)
        {
            const auto rot_x = part_x * static_cast<float>(i);

            for (uint32_t j = 0; j < slices+1; ++j)
            {
                const auto rot_y = part_y * static_cast<float>(j);

                normals.push_back(glm::rotate(glm::rotate(normal, rot_x, X_AXIS), rot_y, Y_AXIS));
            }
        }

        normals.emplace_back(0.0f, -1.0f, 0.0f);

        return normals;
    }

    inline std::vector<uint32_t> generate_sphere_indices (uint32_t slices, uint32_t stacks)
    {
        std::vector<uint32_t> indices{};

        for (uint32_t i = 1; i < slices+1; ++i)
        {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }

        for (uint32_t i = 1; i < stacks - 2; ++i)
        {
            const auto offset = (i - 1) * slices + 1;

            for (uint32_t j = 0; j < slices; ++j)
            {
                indices.push_back(offset + j);
                indices.push_back(offset + j + slices + 1);
                indices.push_back(offset + j + 1);

                indices.push_back(offset + j + slices + 2);
                indices.push_back(offset + j + 1);
                indices.push_back(offset + j + slices+1);
            }
        }

        const auto LAST = 1 + (stacks - 2) * (slices+1);

        for (uint32_t i = 1; i < slices+1; ++i)
        {
            indices.push_back(LAST);
            indices.push_back(LAST - i);
            indices.push_back(LAST - i - 1);
        }

        return indices;
    }

    inline std::vector<glm::vec2> generate_sphere_tex_coords (uint32_t slices, uint32_t stacks)
    {
        std::vector<glm::vec2> tex_coords{};
        tex_coords.reserve(2 + (stacks - 2) * slices+1);

        tex_coords.emplace_back(0.5f, 1.0f);

        for (uint32_t i = 1; i < stacks - 1; ++i)
        {
            for (uint32_t j = 0; j < slices+1; ++j)
            {
                // TODO optimize
                tex_coords.emplace_back(1.0 - (1.0f * j / slices), 1.0f - (1.0f * i / (stacks-1.0)));
            }
        }

        tex_coords.emplace_back(0.5f, 0.0f);

        return tex_coords;
    }
}
