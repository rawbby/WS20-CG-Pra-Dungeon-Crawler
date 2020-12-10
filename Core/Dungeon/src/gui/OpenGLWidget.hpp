#pragma once

#include <QTimer>
#include <QWidget>
#include <QOpenGLWidget>
#include <vector>

#include <gui/Drawable.hpp>
#include <geometries/Geometries.hpp>

class [[maybe_unused]] OpenGLWidget
        : public QOpenGLWidget
{
    //Q_OBJECT

private:

    float m_width = 0;
    float m_height = 0;

private:

    QTimer m_timer;

private:

    std::vector<TrivialDrawable> m_trivialDrawable;
    std::vector<SingleTextureDrawable> m_singleTextureDrawable;

public:

    [[maybe_unused]] explicit OpenGLWidget (QWidget *parent = nullptr);
    ~OpenGLWidget () override;

protected:

    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
};
