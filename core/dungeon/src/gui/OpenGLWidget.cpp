#include <GL/glew.h>
#include <GL/GL.h>

#include <gui/OpenGLWidget.hpp>
#include <gui/MainWindow.hpp>

#include <asset/Asset.hpp>
#include <engine/Util.hpp>

#include <QMouseEvent>

#include <gui/Scene001.hpp>

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

    m_timer.setInterval(8);
    m_timer.start();

    m_elapsed_timer.start();
}

void OpenGLWidget::initializeGL ()
{
    using namespace engine;
    using namespace component;

    m_render.init();
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

    auto &player_dynamic = engine::Game::get_component<engine::component::DynamicCollisionCircle>(m_player);
    auto &player_position = engine::Game::get_component<engine::component::PositionComponent>(m_player);

    auto camera_position = glm::vec3{0.0f, 0.0f, gui::camera_distance};
    camera_position = glm::rotateX(camera_position, glm::radians(gui::CAMERA_ROTATION_X));
    camera_position = glm::rotateY(camera_position, glm::radians(gui::camera_rotation_y));

    auto velocity_forward = engine::toCoordinate(-camera_position);
    auto velocity_right = glm::vec2(velocity_forward.y, -velocity_forward.x);

    glm::vec2 v{};
    v += gui::key_states[gui::KEY_A] ? -velocity_right : glm::vec2{};
    v += gui::key_states[gui::KEY_S] ? -velocity_forward : glm::vec2{};
    v += gui::key_states[gui::KEY_W] || (gui::mouse_keys[gui::MOUSE_LEFT] && gui::mouse_keys[gui::MOUSE_RIGHT]) ? velocity_forward : glm::vec2{};
    v += gui::key_states[gui::KEY_D] ? velocity_right : glm::vec2{};
    player_dynamic.direction(v);
    player_dynamic.speed = gui::camera_distance;

    m_collision.update(m_registry, delta);

    const float fovy = glm::radians(90.0f);
    const float aspect = m_width / m_height;
    const float zNear = 0.001f;
    const float zFar = 1000.0f;
    const auto projection_matrix = glm::perspective(fovy, aspect, zNear, zFar);

    const auto camera_up = glm::vec3{0.0f, 1.0f, 0.0f};

    camera_position += engine::fromCoordinate(player_position);
    const auto camera_center = engine::fromCoordinate(player_position);

    glm::mat4 camera_matrix = glm::lookAt(camera_position, camera_center, camera_up);

    m_shadow_map.update(m_registry);

    makeCurrent();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_width, m_height);

    m_animator.update(m_registry, delta);
    m_render.update(m_registry, projection_matrix, camera_matrix, camera_position, m_width, m_height);

    glUseProgram(asset::program::trivial);
}

OpenGLWidget::~OpenGLWidget () = default;
