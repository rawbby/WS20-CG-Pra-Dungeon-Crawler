#include <GL/glew.h>
#include <GL/GL.h>

#include <gui/OpenGLWidget.hpp>
#include <gui/MainWindow.hpp>

#include <asset/Asset.hpp>

#include <QMouseEvent>

#include <engine/component/GlPointLightComponent.hpp>

#include <gui/Scene001.hpp>

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

    m_elapsed_timer.start();
}

void OpenGLWidget::initializeGL ()
{
    using namespace engine;
    using namespace component;

    Game::init();
    asset::init_assets();

    makeCurrent();

    scene001::create_scene(*this, m_player);
}

void OpenGLWidget::resizeGL (int width, int height)
{
    glViewport(0, 0, width, height);
    m_width = static_cast<float> (width);
    m_height = static_cast<float> (height);
}

void OpenGLWidget::paintGL ()
{
    const auto delta = static_cast<float> (m_elapsed_timer.elapsed()) / 1000.0f;
    m_elapsed_timer.restart();

    auto camera_position = glm::vec3{0.0f, 0.0f, gui::camera_distance};
    camera_position = glm::rotateX(camera_position, glm::radians(gui::CAMERA_ROTATION_X));
    camera_position = glm::rotateY(camera_position, glm::radians(gui::camera_rotation_y));

    auto &player_dynamic = engine::Game::get_component<engine::component::DynamicCollisionCircle>(m_player);
    auto &player_position = engine::Game::get_component<engine::component::PositionComponent>(m_player);

    auto velocity_sideway = glm::vec2(-camera_position.z, camera_position.x);
    auto velocity_forward = glm::vec2(velocity_sideway.y, -velocity_sideway.x);

    glm::vec2 v{};
    v += gui::key_states[gui::KEY_A] ? velocity_sideway : glm::vec2{};
    v += gui::key_states[gui::KEY_S] ? velocity_forward : glm::vec2{};
    v += gui::key_states[gui::KEY_W] ? -velocity_forward : glm::vec2{};
    v += gui::key_states[gui::KEY_D] ? -velocity_sideway : glm::vec2{};
    player_dynamic.direction(v);
    player_dynamic.speed = gui::camera_distance;

    m_collision.update(m_registry, delta);

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
