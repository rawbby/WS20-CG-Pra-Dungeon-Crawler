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
    {update();});

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
    glewExperimental = GL_TRUE;
    glewInit();

    asset::init_assets();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_TEXTURE_2D);

    m_materialDrawable.push_back(asset::drawable::create_floor());
    m_materialDrawable.push_back(asset::drawable::create_wall_back());
    m_materialDrawable.push_back(asset::drawable::create_wall_right());
    // m_materialDrawable.push_back(asset::drawable::create_wall_front());
    // m_materialDrawable.push_back(asset::drawable::create_wall_left());
    // m_materialDrawable.push_back(asset::drawable::create_wall_top());
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

    for (const auto &drawable : m_materialDrawable)
    {
        glUseProgram(drawable.program);
        glBindVertexArray(drawable.vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, drawable.tex_basecolor);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, drawable.tex_height);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, drawable.tex_mrao);

        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, drawable.tex_normal);

        glUniform1i(glGetUniformLocation(drawable.program, "u_basecolor"), 0);
        glUniform1i(glGetUniformLocation(drawable.program, "u_height"), 1);
        glUniform1i(glGetUniformLocation(drawable.program, "u_mrao"), 2);
        glUniform1i(glGetUniformLocation(drawable.program, "u_normal"), 3);

        glUniformMatrix4fv(glGetUniformLocation(drawable.program, "u_projection_matrix"), 1, GL_FALSE, glm::value_ptr(projection_matrix));
        glUniformMatrix4fv(glGetUniformLocation(drawable.program, "u_model_view_matrix"), 1, GL_FALSE, glm::value_ptr(camera_matrix * drawable.model_view_matrix));

        glDrawElements(GL_TRIANGLES, drawable.count, GL_UNSIGNED_INT, nullptr);
    }
}

OpenGLWidget::~OpenGLWidget () = default;
