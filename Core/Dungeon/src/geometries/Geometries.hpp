#pragma once

#include <vector>
#include <spdlog/spdlog.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace geometries
{
    template <size_t DIVISIONS>
    std::vector<glm::vec3> generate_plane_bottom_points () // , (DIVISIONS + 2) * (DIVISIONS + 2)
    {
        std::vector<glm::vec3> points{};

        for (size_t z = 0; z < DIVISIONS + 2; ++z)
        {
            for (size_t x = 0; x < DIVISIONS + 2; ++x)
            {
                const auto x_val = -0.5f + (static_cast<float> (x) / (DIVISIONS + 1));
                const auto z_val = 0.5f - (static_cast<float> (z) / (DIVISIONS + 1));
                points.emplace_back(x_val, -0.5f, z_val);
            }
        }

        return points;
    }

    template <size_t DIVISIONS>
    std::vector<uint32_t> generate_plane_bottom_indices () // , (DIVISIONS + 1) * (DIVISIONS + 1) * 2 * 3
    {
        std::vector<uint32_t> indices{};

        for (size_t y = 0; y < DIVISIONS + 1; ++y)
        {
            for (size_t x = 0; x < DIVISIONS + 1; ++x)
            {
                indices.push_back((x + y + y * (DIVISIONS + 1)) + 0);
                indices.push_back((x + y + y * (DIVISIONS + 1)) + DIVISIONS + 2);
                indices.push_back((x + y + y * (DIVISIONS + 1)) + 1);

                indices.push_back((x + y + y * (DIVISIONS + 1)) + DIVISIONS + 2 + 1);
                indices.push_back((x + y + y * (DIVISIONS + 1)) + 1);
                indices.push_back((x + y + y * (DIVISIONS + 1)) + DIVISIONS + 2);
            }
        }

        return indices;
    }

    template <size_t DIVISIONS>
    std::vector<glm::vec3> generate_plane_bottom_normals ()
    {
        std::vector<glm::vec3> normals{};

        for (size_t i = 0; i < (DIVISIONS + 2) * (DIVISIONS + 2); ++i)
        {
            normals.emplace_back(0.0f, 1.0f, 0.0f);
        }

        return normals;
    }

    template <size_t DIVISIONS>
    std::vector<glm::vec2> generate_plane_bottom_tex_coords ()
    {
        std::vector<glm::vec2> tex_coords{};

        for (size_t y = 0; y < DIVISIONS + 2; ++y)
        {
            for (size_t x = 0; x < DIVISIONS + 2; ++x)
            {
                const auto x_val = (static_cast<float> (x) / (DIVISIONS + 1));
                const auto y_val = (static_cast<float> (y) / (DIVISIONS + 1));
                tex_coords.emplace_back(x_val, y_val);
            }
        }

        return tex_coords;
    }
}
