#pragma once

#include <cstdint>
#include <memory>
#include <spdlog/spdlog.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct Mesh
{
    std::unique_ptr<glm::vec3[]> vertices;
    std::unique_ptr<uint32_t[]>  indices;
    std::unique_ptr<glm::vec3[]> normals;
    std::unique_ptr<glm::vec2[]> tex_coords;

    uint32_t vertex_count;
    uint32_t indices_count;
};

struct AnimatedMesh
        : public Mesh
{
    std::unique_ptr<uint32_t[]> joint_indices;
    std::unique_ptr<glm::vec3[]> joint_weights;

    std::unique_ptr<glm::vec3[]> joints;
    std::unique_ptr<uint32_t[]> joint_parent_indices;

    uint32_t joint_count;
};

struct Animation
{
    struct JointTransformation
    {
        glm::quat rotation;
        glm::vec3 scale;
    };

    std::unique_ptr<JointTransformation[]> joint_transformations;
    std::unique_ptr<float[]> joint_timestamps;

    uint32_t joint_count;
    uint32_t key_frame_count;
};
