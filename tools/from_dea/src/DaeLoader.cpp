#include <DaeLoader.hpp>

#include <cstdint>
#include <memory>
#include <spdlog/spdlog.h>

#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <map>
#include <vector>
#include <queue>

#include <AnimatedMesh.hpp>

namespace
{
    void get_vertices (AnimatedMesh &mesh, const aiMesh *ai_mesh, const aiScene *ai_scene)
    {
        mesh.vertices = std::make_unique<glm::vec3[]>(ai_mesh->mNumVertices);
        mesh.vertex_count = ai_mesh->mNumVertices;
        memcpy(mesh.vertices.get(), ai_mesh->mVertices, sizeof(glm::vec3) * mesh.vertex_count);
    }

    void get_indices (AnimatedMesh &mesh, const aiMesh *ai_mesh, const aiScene *ai_scene)
    {
        mesh.indices = std::make_unique<uint32_t[]>(ai_mesh->mNumFaces * 3);
        mesh.indices_count = ai_mesh->mNumFaces * 3;
        for (size_t j = 0; j < ai_mesh->mNumFaces; ++j)
        {
            memcpy(&(mesh.indices[j * 3]), ai_mesh->mFaces[j].mIndices, sizeof(uint32_t) * 3);
        }
    }

    void get_normals (AnimatedMesh &mesh, const aiMesh *ai_mesh, const aiScene *ai_scene)
    {
        mesh.normals = std::make_unique<glm::vec3[]>(mesh.vertex_count);
        memcpy(mesh.normals.get(), ai_mesh->mNormals, sizeof(glm::vec3) * mesh.vertex_count);
    }

    void get_tex_coords (AnimatedMesh &mesh, const aiMesh *ai_mesh, const aiScene *ai_scene)
    {
        mesh.tex_coords = std::make_unique<glm::vec2[]>(mesh.vertex_count);
        for (size_t j = 0; j < mesh.vertex_count; ++j)
        {
            memcpy(&(mesh.tex_coords[j]), &(ai_mesh->mTextureCoords[0][j]), sizeof(glm::vec2));
        }
    }

    std::map<std::string, size_t> get_joint_parents (AnimatedMesh &mesh, const aiMesh *ai_mesh, const aiScene *ai_scene)
    { // TODO tidy up
        auto get_root = [] (auto scene, auto mesh) -> aiNode *
        {

            std::vector<aiNode *> todo{};
            todo.push_back(scene->mRootNode);

            while (!todo.empty())
            {
                aiNode *node = todo.back();
                todo.pop_back();

                for (size_t j = 0; j < mesh->mNumBones; ++j)
                {
                    const auto bone = mesh->mBones[j];
                    if (bone->mName == node->mName)
                    {
                        return node;
                    }
                }

                for (size_t j = 0; j < node->mNumChildren; ++j)
                {
                    todo.push_back(node->mChildren[j]);
                }
            }

            return nullptr;
        };

        mesh.joint_parent_indices = std::make_unique<uint32_t[]>(ai_mesh->mNumBones);

        aiNode *root = get_root(ai_scene, ai_mesh);

        std::queue<aiNode *> todo{};
        std::map<std::string, size_t> bone_map{};

        mesh.joint_parent_indices[0] = 0;
        size_t joint_parent_end = 1;

        todo.push(root);
        size_t index = 0;

        while (!todo.empty())
        {
            aiNode *child = todo.front();
            todo.pop();

            bone_map[child->mName.data] = index;

            for (size_t j = 0; j < child->mNumChildren; ++j)
            {
                mesh.joint_parent_indices[joint_parent_end] = index;
                ++joint_parent_end;

                todo.push(child->mChildren[j]);
            }

            ++index;
        }

        return bone_map;
    }

    void get_joints (AnimatedMesh &mesh, const aiMesh *ai_mesh, const aiScene *ai_scene, const std::map<std::string, size_t> &bone_map)
    {
        mesh.joints = std::make_unique<glm::vec3[]>(ai_mesh->mNumBones);
        mesh.joint_count = ai_mesh->mNumBones;

        for (size_t j = 0; j < ai_mesh->mNumBones; ++j)
        {
            const auto bone = ai_mesh->mBones[j];

            const auto am = bone->mOffsetMatrix;
            // @formatter:off
            const auto gm = glm::mat4{am[0][1], am[0][2], am[0][3], am[0][4],
                    am[1][1], am[1][2], am[1][3], am[1][4],
                    am[2][1], am[2][2], am[2][3], am[2][4],
                    am[3][1], am[3][2], am[3][3], am[3][4]};
            // @formatter:on

            const auto joint = gm * glm::vec4{0.0f};

            mesh.joints[bone_map.at(bone->mName.data)] = glm::vec3(joint) / joint.w;
        }
    }

    void get_joint_indices_and_weights (AnimatedMesh &mesh, const aiMesh *ai_mesh, const aiScene *ai_scene, const std::map<std::string, size_t> &bone_map)
    {
        mesh.joint_indices = std::make_unique<uint32_t[]>(ai_mesh->mNumVertices * 3);
        mesh.joint_weights = std::make_unique<glm::vec3[]>(ai_mesh->mNumVertices);

        for (size_t j = 0; j < ai_mesh->mNumBones; ++j)
        {
            const auto bone = ai_mesh->mBones[j];
            const auto res = bone_map.at(bone->mName.data);

            for (size_t k = 0; k < bone->mNumWeights; ++k)
            {
                auto index = &(mesh.joint_indices[bone->mWeights[k].mVertexId]);
                auto &weight = mesh.joint_weights[bone->mWeights[k].mVertexId];

                if (weight.x <= weight.y && weight.x <= weight.z)
                {
                    // x min
                    if (bone->mWeights[k].mWeight > weight.x)
                    {
                        index[0] = res;
                        weight.x = bone->mWeights[k].mWeight;
                    }
                }
                else if (weight.y <= weight.z)
                {
                    // y min
                    if (bone->mWeights[k].mWeight > weight.y)
                    {
                        index[1] = res;
                        weight.y = bone->mWeights[k].mWeight;
                    }
                }
                else
                {
                    // z min
                    if (bone->mWeights[k].mWeight > weight.z)
                    {
                        index[2] = res;
                        weight.z = bone->mWeights[k].mWeight;
                    }
                }
            }
        }
    }

    void get_animation_timestamps (Animation &anim, const aiAnimation *ai_anim)
    {
        anim.key_frame_count = ai_anim->mChannels[0]->mNumRotationKeys;
        anim.joint_timestamps = std::make_unique<float[]>(anim.key_frame_count);
        float delta = static_cast<float> (ai_anim->mDuration) / static_cast<float> (anim.key_frame_count);

        for (size_t i = 0; i < anim.key_frame_count; ++i)
        {
            anim.joint_timestamps[i] = delta * i;
        }
    }

    void get_animation_transformations (Animation &anim, const aiAnimation *ai_anim)
    {
        anim.joint_count = ai_anim->mNumChannels;
        anim.joint_transformations = std::make_unique<Animation::JointTransformation[]>(anim.key_frame_count * anim.joint_count);
        for (size_t i = 0; i < anim.key_frame_count; ++i)
        {
            for (size_t j = 0; j < anim.joint_count; ++j)
            {
                Animation::JointTransformation t{};
                const auto r = ai_anim->mChannels[j]->mRotationKeys[i].mValue;
                const auto s = ai_anim->mChannels[j]->mScalingKeys[i].mValue;

                t.rotation = {r.x, r.y, r.z, r.w};
                t.scale = {s.x, s.y, s.z};

                anim.joint_transformations[anim.joint_count * i + j] = t;
            }
        }
    }
}

namespace dae_loader
{
    Animation load_animation (std::string_view path)
    {
        Assimp::Importer importer{};

        const aiScene *ai_scene = importer.ReadFile(path.data(), aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

        if (!ai_scene)
        {
            spdlog::error("FAILED TO LOAD DAE FILE! Error: {}", importer.GetErrorString());
            return {};
        }

        const auto *ai_anim = ai_scene->mAnimations[0];
        Animation anim{};

        get_animation_timestamps(anim, ai_anim);
        get_animation_transformations(anim, ai_anim);

        return anim;
    }

    AnimatedMesh load_animated_mesh (std::string_view path)
    {
        Assimp::Importer importer{};

        const aiScene *ai_scene = importer.ReadFile(path.data(), aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

        if (!ai_scene)
        {
            spdlog::error("FAILED TO LOAD DAE FILE! Error: {}", importer.GetErrorString());
            return {};
        }

        const auto ai_mesh = ai_scene->mMeshes[0];
        AnimatedMesh mesh{};

        // fetch vertices
        get_vertices(mesh, ai_mesh, ai_scene);

        // fetch indices
        get_indices(mesh, ai_mesh, ai_scene);

        // fetch normals
        get_normals(mesh, ai_mesh, ai_scene);

        // fetch tex_coords
        get_tex_coords(mesh, ai_mesh, ai_scene);

        // fetch joint_parent_indices;
        const auto bone_map = get_joint_parents(mesh, ai_mesh, ai_scene);

        // fetch joints;
        get_joints(mesh, ai_mesh, ai_scene, bone_map);

        // fetch joint_indices;
        // fetch joint_weights;
        get_joint_indices_and_weights(mesh, ai_mesh, ai_scene, bone_map);

        return mesh;
    }
}
