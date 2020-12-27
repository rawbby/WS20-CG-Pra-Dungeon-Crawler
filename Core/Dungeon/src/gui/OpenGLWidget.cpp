#include <GL/glew.h>
#include <GL/GL.h>

#include <QMouseEvent>

#include <gui/OpenGLWidget.hpp>
#include <asset/Asset.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace
{
    /** normalize x to br between l (lower) and u (upper). */
    [[nodiscard]] constexpr float clamp (float x, float l, float u) noexcept
    {   //@formatter:off
        if (x > u) return u;
        if (x < l) return l;
        return x;
    }   //@formatter:on

    /**
     * brute force modulo 360.0f on x.
     * this is faster than the conventional mod operator
     * if x is between -1 and 2 times 360.0f.
     */
    [[nodiscard]] constexpr float mod360 (float x) noexcept
    {   //@formatter:off
        while (x >= 360.0f) x -= 360.0f;
        while (x < 0.0f)    x += 360.0f;
        return x;
    }   //@formatter:on
}

[[maybe_unused]] OpenGLWidget::OpenGLWidget (QWidget *parent)
        : QOpenGLWidget(parent)
        , m_timer(parent)
{
    QWidget::connect(&m_timer, &QTimer::timeout, [this] (auto signal)
    {Q_UNUSED(signal); QWidget::update();});

    m_timer.setInterval(10);
    m_timer.start();
}

void OpenGLWidget::mousePressEvent (QMouseEvent *event)
{
    m_mouse_pressed = true;
    m_mouse_position = event->pos();
}

void OpenGLWidget::mouseReleaseEvent (QMouseEvent *event)
{
    Q_UNUSED(event);
    m_mouse_pressed = false;
}

void OpenGLWidget::mouseMoveEvent (QMouseEvent *event)
{
    if (m_mouse_pressed)
    {
        auto delta = event->pos() - m_mouse_position;
        m_mouse_position = event->pos();

        const auto dx = -static_cast<float> (delta.x());
        m_camera_rotation_y = mod360(m_camera_rotation_y + dx); // TODO mod360
    }
}

void OpenGLWidget::wheelEvent (QWheelEvent *event)
{
    const auto delta = static_cast<float> (-event->angleDelta().y()) / 512.0f;
    m_camera_distance = clamp(m_camera_distance + delta, M_MIN_DISTANCE, M_MAX_DISTANCE);
}

void OpenGLWidget::initializeGL ()
{
    engine::Game::init();
    asset::init_assets();

    auto entity = engine::Game::add_entity();
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::drawable::create_wall_back());

    entity = engine::Game::add_entity();
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::drawable::create_wall_right());

    entity = engine::Game::add_entity();
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::drawable::create_floor());

    entity = engine::Game::add_entity({1.0f,1.0f});
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::drawable::create_wall_back());

    entity = engine::Game::add_entity({1.0f,1.0f});
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::drawable::create_wall_right());

    entity = engine::Game::add_entity({1.0f,1.0f});
    engine::Game::add_component<engine::component::GlMaterialComponent>(entity, asset::drawable::create_floor());
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

    const float fovy = glm::radians(60.0f);
    const float aspect = m_width / m_height;
    const float zNear = 0.1f;
    const float zFar = 150.0f;
    const auto projection_matrix = glm::perspective(fovy, aspect, zNear, zFar);

    glm::vec3 direction{0.0f, 0.0f, -1.0f};
    direction = glm::rotateX(direction, glm::radians(M_CAMERA_ROTATION_X));
    direction = glm::rotateY(direction, glm::radians(m_camera_rotation_y));

    const auto position = m_camera_distance * direction;
    const auto center = glm::vec3{0.0f, 0.0f, 0.0f};
    const auto up = glm::vec3{0.0f, 1.0f, 0.0f};
    glm::mat4 camera_matrix = glm::lookAt(position, center, up);

    // TODO replace delta by a more accurate value
    engine::Game::update(projection_matrix, camera_matrix, 0.01f);
}

OpenGLWidget::~OpenGLWidget () = default;
