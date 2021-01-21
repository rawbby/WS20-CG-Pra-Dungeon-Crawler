#include <GL/glew.h>
#include <GL/GL.h>

#include <gui/OpenGLWidget.hpp>
#include <gui/MainWindow.hpp>

#include <asset/Asset.hpp>

#include <QMouseEvent>

#include <engine/component/GlPointLightComponent.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

[[maybe_unused]] OpenGLWidget::OpenGLWidget (QWidget *parent)
        : QOpenGLWidget(parent)
        , m_timer(parent)
{
    setFocusPolicy(Qt::StrongFocus);

    QWidget::connect(&m_timer, &QTimer::timeout, [this] (auto signal)
    {
        Q_UNUSED(signal);
        QWidget::update();
    });

    m_timer.setInterval(10);
    m_timer.start();
}

void OpenGLWidget::initializeGL ()
{
    engine::Game::init();
    asset::init_assets();

    makeCurrent();

    auto entity = engine::Game::add_entity();
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::material::create_wall_back());

    entity = engine::Game::add_entity();
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::material::create_wall_right());

    entity = engine::Game::add_entity();
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::material::create_wall_left());

    entity = engine::Game::add_entity();
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::material::create_floor());

    entity = engine::Game::add_entity({0.0f, 1.0f});
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::material::create_floor());

    entity = engine::Game::add_entity({0.0f, 1.0f});
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::material::create_wall_left());

    entity = engine::Game::add_entity({0.0f, 1.0f});
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::material::create_wall_front());

    entity = engine::Game::add_entity({1.0f, 1.0f});
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::material::create_wall_back());

    entity = engine::Game::add_entity({1.0f, 1.0f});
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::material::create_wall_right());

    entity = engine::Game::add_entity({1.0f, 1.0f});
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::material::create_floor());

    entity = engine::Game::add_entity({1.0f, 1.0f});
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::material::create_wall_front());

    entity = engine::Game::add_entity({0.5, 1.0});
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::material::create_player());
    engine::Game::add_component<engine::component::DynamicCollisionComponent>(entity, 0.5f, glm::vec2{});
    engine::Game::add_component<engine::component::GlPointLightComponent>(entity, glm::vec3{0.8f, 0.8f, 0.8f}, 0.0f, asset::program::shadow);
    m_player = entity;

    entity = engine::Game::add_entity({0.0f, 1.0f});
    engine::Game::add_component<engine::component::GlPointLightComponent>(entity, glm::vec3{0.4f, 0.4f, 1.0f}, 0.75f, asset::program::shadow);
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::material::create_debug_light());

    entity = engine::Game::add_entity({0.0f, 0.0f});
    engine::Game::add_component<engine::component::GlPointLightComponent>(entity, glm::vec3{1.0f, 0.5f, 0.5f}, 0.0f, asset::program::shadow);
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::material::create_debug_light());
}

void OpenGLWidget::resizeGL (int width, int height)
{
    glViewport(0, 0, width, height);
    m_width = static_cast<float> (width);
    m_height = static_cast<float> (height);
}

void OpenGLWidget::paintGL ()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto camera_position = glm::vec3{0.0f, 0.0f, gui::camera_distance};
    camera_position = glm::rotateX(camera_position, glm::radians(gui::CAMERA_ROTATION_X));
    camera_position = glm::rotateY(camera_position, glm::radians(gui::camera_rotation_y));


    auto &player_dynamic = engine::Game::get_component<engine::component::DynamicCollisionComponent>(m_player);
    auto &player_position = engine::Game::get_component<engine::component::PositionComponent>(m_player);

    auto velocity_sideway = glm::normalize(glm::vec2(-camera_position.z, camera_position.x)) * 0.025f * gui::camera_distance;
    auto velocity_forward = glm::vec2(velocity_sideway.y, -velocity_sideway.x);

    player_dynamic.velocity = glm::vec2{};
    player_dynamic.velocity += gui::key_states[gui::KEY_A] ? velocity_sideway : glm::vec2{};
    player_dynamic.velocity += gui::key_states[gui::KEY_S] ? velocity_forward : glm::vec2{};
    player_dynamic.velocity += gui::key_states[gui::KEY_W] ? -velocity_forward : glm::vec2{};
    player_dynamic.velocity += gui::key_states[gui::KEY_D] ? -velocity_sideway : glm::vec2{};

    m_collision.update(m_registry, 0.01f);

    const float fovy = glm::radians(90.0f);
    const float aspect = m_width / m_height;
    const float zNear = 0.1f;
    const float zFar = 10.0f;
    const auto projection_matrix = glm::perspective(fovy, aspect, zNear, zFar);

    auto camera_center = glm::vec3{0.0f, 0.0f, 0.0f};
    const auto camera_up = glm::vec3{0.0f, 1.0f, 0.0f};

    camera_position += glm::vec3{player_position[0], 0.0f, player_position[1]};
    camera_center += glm::vec3{player_position[0], 0.0f, player_position[1]};

    glm::mat4 camera_matrix = glm::lookAt(camera_position, camera_center, camera_up);

    m_shadow_map.update(m_registry);

    makeCurrent();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_width, m_height);

    m_render.update(m_registry, projection_matrix, camera_matrix, camera_position, m_width, m_height);
}

OpenGLWidget::~OpenGLWidget () = default;
