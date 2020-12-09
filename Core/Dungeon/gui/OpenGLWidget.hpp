#pragma once

#include <QWidget>
#include <QOpenGLWidget>

class [[maybe_unused]] OpenGLWidget
        : public QOpenGLWidget
{
public:

    explicit OpenGLWidget (QWidget *parent = nullptr);
    ~OpenGLWidget () override;

protected:

    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
};
