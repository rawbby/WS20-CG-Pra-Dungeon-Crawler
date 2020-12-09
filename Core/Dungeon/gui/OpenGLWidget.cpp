#include <OpenGLWidget.hpp>

OpenGLWidget::OpenGLWidget (QWidget *parent)
        : QOpenGLWidget(parent)
{
}
void OpenGLWidget::initializeGL ()
{
    QOpenGLWidget::initializeGL();
}
void OpenGLWidget::resizeGL (int width, int height)
{
    QOpenGLWidget::resizeGL(width, height);
}
void OpenGLWidget::paintGL ()
{
    QOpenGLWidget::paintGL();
}

OpenGLWidget::~OpenGLWidget () = default;
