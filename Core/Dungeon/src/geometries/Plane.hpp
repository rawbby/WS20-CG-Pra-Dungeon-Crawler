#pragma once

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

#include <vector>

namespace geometries
{
    inline std::vector<glm::vec3> generate_plane_back_points (uint32_t divisions)
    {
        std::vector<glm::vec3> points{};
        points.reserve((divisions + 2) * (divisions + 2));

        for (uint32_t y = 0; y < divisions + 2; ++y)
        {
            for (uint32_t x = 0; x < divisions + 2; ++x)
            {
                const auto x_val = -0.5f + (static_cast<float> (x) / static_cast<float> (divisions + 1));
                const auto y_val = -0.5f + (static_cast<float> (y) / static_cast<float> (divisions + 1));
                points.emplace_back(x_val, y_val, -0.5f);
            }
        }

        return points;
    }

    inline std::vector<glm::vec3> generate_plane_back_normals (uint32_t divisions)
    {
        std::vector<glm::vec3> normals{};
        normals.reserve((divisions + 2) * (divisions + 2));

        for (uint32_t i = 0; i < (divisions + 2) * (divisions + 2); ++i)
        {
            normals.emplace_back(0.0f, 0.0f, 1.0f);
        }

        return normals;
    }

    inline std::vector<uint32_t> generate_plane_indices (uint32_t divisions)
    {
        std::vector<uint32_t> indices{};
        indices.reserve((divisions + 1) * (divisions + 1) * 2 * 3);

        for (uint32_t y = 0; y < divisions + 1; ++y)
        {
            for (uint32_t x = 0; x < divisions + 1; ++x)
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

    inline std::vector<glm::vec2> generate_plane_tex_coords (uint32_t divisions)
    {
        std::vector<glm::vec2> tex_coords{};
        tex_coords.reserve((divisions + 2) * (divisions + 2));

        for (uint32_t y = 0; y < divisions + 2; ++y)
        {
            for (uint32_t x = 0; x < divisions + 2; ++x)
            {
                const auto x_val = static_cast<float> (x) / static_cast<float> (divisions + 1);
                const auto y_val = static_cast<float> (y) / static_cast<float> (divisions + 1);
                tex_coords.emplace_back(x_val, y_val);
            }
        }

        return tex_coords;
    }
}
