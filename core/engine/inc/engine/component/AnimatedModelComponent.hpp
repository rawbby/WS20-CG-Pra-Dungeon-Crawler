#pragma once

#include <engine/Entity.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <entt/entt.hpp>

#include <engine/component/GlMaterialComponent.hpp>

#include <vector>
#include <span>

#include <AnimatedMesh.hpp>

namespace engine::component
{
    struct JointAnimatorComponent
            : public GlMaterialComponent
    {
        const AnimatedMesh *model;
        const Animation *animation;

        std::unique_ptr<glm::mat4[]> current_joint_transformations;
        float current_time;

        JointAnimatorComponent (const AnimatedMesh *skeleton, const Animation *animation)
                : model(skeleton)
                , animation(animation)
                , current_time(0.0f)
        {
            current_joint_transformations = std::make_unique<glm::mat4[]>(skeleton->joint_count);
            current_time = apply_for_time(current_joint_transformations.get(), current_time);
        }

        void update (float delta)
        {
            current_time += delta;
            current_time = apply_for_time(current_joint_transformations.get(), current_time);
        }

    private:

        float apply_for_time (glm::mat4 *joints, float timestamp) const // TODO tidy and check
        {
            uint8_t n = animation->key_frame_count;

            while (true)
            {
                if (timestamp < animation->joint_timestamps[0])
                { // use identity for zero

                    joints[0] = glm::translate(glm::identity<glm::mat4>(), model->joints[0]);

                    for (uint8_t j = 0; j < animation->joint_count; ++j)
                    {
                        const auto &parent = joints[model->joint_parent_indices[1 + j]];
                        joints[1 + j] = glm::translate(parent, model->joints[1 + j]);
                    };

                    return timestamp;
                }

                for (uint8_t i = 0; i < n; ++i)
                {
                    if (timestamp < animation->joint_timestamps[i])
                    {
                        const auto f0 = animation->joint_transformations[(i + 0) * animation->joint_count];
                        const auto f1 = animation->joint_transformations[(i + 1) * animation->joint_count];

                        joints[0] = glm::translate(glm::identity<glm::mat4>(), model->joints[0]);
                        joints[0] = glm::scale(joints[0], glm::mix(f0.scale, f1.scale, timestamp));
                        joints[0] = glm::toMat4(glm::mix(f0.rotation, f1.rotation, timestamp)) * joints[0];

                        for (uint8_t j = 0; j < animation->joint_count; ++j)
                        {
                            const auto &parent = joints[model->joint_parent_indices[1 + j]];

                            joints[1 + j] = glm::translate(parent, model->joints[1 + j]);
                            joints[1 + j] = glm::scale(joints[1 + j], glm::mix(f0.scale, f1.scale, timestamp));
                            joints[1 + j] = glm::toMat4(glm::mix(f0.rotation, f1.rotation, timestamp)) * joints[1 + j];
                        };

                        return timestamp;
                    }
                }

                timestamp -= animation->joint_timestamps[animation->key_frame_count - 1];
            }
        }
    };
}
