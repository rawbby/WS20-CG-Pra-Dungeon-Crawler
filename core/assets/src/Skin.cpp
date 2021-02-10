#include <GL/glew.h>
#include <GL/GL.h>

#include <asset/Asset.hpp>

#include <gltf/GLTFLoader.hpp>

namespace asset::internal
{
    void init_skins ()
    {
        auto data = gltf::load_gltf("res/gltf/scorpi.gltf");

        gltf::internal::SkinExtra skin_extra{};
        asset::skin::skin = gltf::load_single_skin(data.get(), skin_extra);
        asset::skin::mesh = gltf::load_single_mesh(data.get(), skin_extra);

        gltf::internal::AnimationsExtra anims_extra{};
        asset::skin::anims = gltf::load_animations(data.get(), skin_extra, anims_extra);

        asset::skin::glmesh = model::GlSkinnedMesh::fromSkinnedMesh(asset::skin::mesh);
        asset::skin::glmesh.program = asset::program::skinned;
        asset::skin::glmesh.mvm = glm::mat4{1.0f};
        //asset::skin::glmesh.mvm = glm::rotate(asset::skin::glmesh.mvm, glm::radians(90.0f), glm::vec3{0.0f, 0.0f, -1.0f});
        asset::skin::glmesh.mvm = glm::rotate(asset::skin::glmesh.mvm, glm::radians(270.0f), glm::vec3{0.0f, 1.0f, 0.0f});
        asset::skin::glmesh.mvm = glm::scale(asset::skin::glmesh.mvm, glm::vec3{0.02f});

        asset::skin::ator = model::create_skin_transition_animator(&asset::skin::skin, asset::skin::anims.data(), anims_extra.animation_count);
    }
}
