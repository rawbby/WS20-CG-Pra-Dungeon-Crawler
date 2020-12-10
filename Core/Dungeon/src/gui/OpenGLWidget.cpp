#include <GL/glew.h>
#include <GL/GL.h>

#include <gui/OpenGLWidget.hpp>
#include <geometries/Geometries.hpp>
#include <shader/Assets.hpp>
#include <shader/Program.hpp>

#include <spdlog/spdlog.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

[[maybe_unused]] OpenGLWidget::OpenGLWidget (QWidget *parent)
        : QOpenGLWidget(parent)
        , m_timer(parent)
{
    QWidget::connect(&m_timer, &QTimer::timeout, [this] (auto signal) {update();});

    m_timer.setInterval(10);
    m_timer.start();
}

void OpenGLWidget::initializeGL ()
{
    glewExperimental = GL_TRUE;
    glewInit();

    shader::load_assets();

    glEnable(GL_DEPTH_TEST);

    auto tri = geom_test_triangle();

    using namespace shader;
    tri.program = compile_program(vertex_shader::trivial, fragment_shader::trivial_red);

    m_trivialDrawable.push_back(tri);
}

void OpenGLWidget::resizeGL (int width, int height)
{
    glViewport(0, 0, width, height);
    m_width  = static_cast<float> (width);
    m_height = static_cast<float> (height);
}

void OpenGLWidget::paintGL ()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // const float fovy              = glm::radians(45.0f);
    // const float aspect            = m_width / m_height;
    // const float zNear             = 0.1f;
    // const float zFar              = 150.0f;
    // const auto  projection_matrix = glm::perspective(fovy, aspect, zNear, zFar);

    for (const auto &drawable : m_trivialDrawable)
    {
        if (drawable.program == GL_NONE)
        {
            spdlog::error("drawable has invalid program!");
            continue;
        }

        glUseProgram(drawable.program);
        glBindVertexArray(drawable.vbo);

        // glUniformMatrix4fv(glGetUniformLocation(drawable.program, "v_projection_matrix"), 1, GL_FALSE, glm::value_ptr(projection_matrix));
        // glUniformMatrix4fv(glGetUniformLocation(drawable.program, "v_model_view_matrix"), 1, GL_FALSE, glm::value_ptr(drawable.model_view_matrix));

        glDrawElements(GL_TRIANGLES, drawable.count, GL_UNSIGNED_INT, nullptr);
    }

//    for (const auto &drawable : m_singleTextureDrawable)
//    {
//        if (drawable.program == GL_NONE)
//        {
//            spdlog::error("drawable has invalid program!");
//            continue;
//        }
//
//        glUseProgram(drawable.program);
//        glBindVertexArray(drawable.vbo);
//
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, drawable.texture);
//
//        glUniformMatrix4fv(glGetUniformLocation(drawable.program, "v_projection_matrix"), 1, GL_FALSE, glm::value_ptr(projection_matrix));
//        glUniformMatrix4fv(glGetUniformLocation(drawable.program, "v_model_view_matrix"), 1, GL_FALSE, glm::value_ptr(drawable.model_view_matrix));
//
//        glDrawElements(GL_TRIANGLES, drawable.count, GL_UNSIGNED_INT, nullptr);
//    }
}

OpenGLWidget::~OpenGLWidget () = default;
