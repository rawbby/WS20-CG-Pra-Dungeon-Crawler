#include <asset/Mvm.hpp>

#include <glm/ext/matrix_transform.hpp>

namespace asset::internal
{
    void init_mvms ()
    {
        using namespace asset::internal;

        mvm::id = glm::identity<glm::mat4>();

        mvm::rot_x270      = glm::rotate(mvm::id, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        mvm::rot_x270_z270 = glm::rotate(mvm::rot_x270, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        mvm::rot_x270_z180 = glm::rotate(mvm::rot_x270, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        mvm::rot_x270_z90  = glm::rotate(mvm::rot_x270, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        mvm::tra_y1        = glm::translate(mvm::id, glm::vec3(0.0f, 1.0f, 0.0f));

        const auto debug_rot_x270      = mvm::rot_x270;
        const auto debug_rot_x270_z270 = mvm::rot_x270_z270;
        const auto debug_rot_x270_z180 = mvm::rot_x270_z180;
        const auto debug_rot_x270_z90  = mvm::rot_x270_z90;
        const auto debug_tra_y1        = mvm::tra_y1;
    }
}
