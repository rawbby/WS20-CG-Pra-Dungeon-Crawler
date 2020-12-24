#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <spdlog/spdlog.h>

#include <vector>

namespace geometries
{
    inline std::vector<glm::vec3> generate_plane_bottom_points (size_t divisions)
    {
        auto points = std::vector<glm::vec3>((divisions + 2) * (divisions + 2));

        for (size_t z = 0; z < divisions + 2; ++z)
        {
            for (size_t x = 0; x < divisions + 2; ++x)
            {
                const auto x_val = -0.5f + (static_cast<float> (x) / static_cast<float> (divisions + 1));
                const auto z_val = +0.5f - (static_cast<float> (z) / static_cast<float> (divisions + 1));
                points.emplace_back(x_val, -0.5f, z_val);
            }
        }

        return points;
    }

    inline std::vector<uint32_t> generate_plane_bottom_indices (size_t divisions)
    {
        auto indices = std::vector<uint32_t>((divisions + 1) * (divisions + 1) * 2 * 3);

        for (size_t y = 0; y < divisions + 1; ++y)
        {
            for (size_t x = 0; x < divisions + 1; ++x)
            {
                indices.push_back((x + y + y * (divisions + 1)) + 0);
                indices.push_back((x + y + y * (divisions + 1)) + divisions + 2);
                indices.push_back((x + y + y * (divisions + 1)) + 1);

                indices.push_back((x + y + y * (divisions + 1)) + divisions + 2 + 1);
                indices.push_back((x + y + y * (divisions + 1)) + 1);
                indices.push_back((x + y + y * (divisions + 1)) + divisions + 2);
            }
        }

        return indices;
    }

    inline std::vector<glm::vec3> generate_plane_bottom_normals (size_t divisions)
    {
        auto normals = std::vector<glm::vec3>((divisions + 2) * (divisions + 2));

        for (size_t i = 0; i < (divisions + 2) * (divisions + 2); ++i)
        {
            normals.emplace_back(0.0f, 1.0f, 0.0f);
        }

        return normals;
    }

    inline std::vector<glm::vec2> generate_plane_bottom_tex_coords (size_t divisions)
    {
        auto tex_coords = std::vector<glm::vec2>((divisions + 2) * (divisions + 2));

        for (size_t y = 0; y < divisions + 2; ++y)
        {
            for (size_t x = 0; x < divisions + 2; ++x)
            {
                const auto x_val = static_cast<float> (x) / static_cast<float> (divisions + 1);
                const auto y_val = static_cast<float> (y) / static_cast<float> (divisions + 1);
                tex_coords.emplace_back(x_val, y_val);
            }
        }

        return tex_coords;
    }
}
