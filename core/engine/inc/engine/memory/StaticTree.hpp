#pragma once

#include <cstdint>
#include <cstdlib>
#include <span>

namespace engine::memory
{
    template <typename T>
    struct StaticTree
    {
        uint8_t *parents = nullptr;
        T *data = nullptr;

        StaticTree (std::span<T> elements, std::span<uint8_t> layers) noexcept
        {
            // allocate memory
            data = new T[elements.size()];
            parents = new uint8_t[elements.size()];

            // fill element array
            memcpy(data, elements, sizeof(T) * elements.size());

            // fill parent array
            uint8_t &size = *parents;
            size = 1;

            uint8_t parent = 0;

            for (auto layer: layers)
            {
                for (; layer; --layer)
                {
                    parents[size] = parent;
                    ++size;
                }
                ++parent;
            }
        }

        ~StaticTree () noexcept
        {
            delete[]data;
            delete[]parents;
        };

        [[nodiscard]] uint8_t size () const
        {
            return *parents;
        }
    };
}
