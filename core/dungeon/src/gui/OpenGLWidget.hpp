#pragma once

#include <QTimer>
#include <QPoint>
#include <QWidget>
#include <QOpenGLWidget>
#include <vector>

#include <entt/entt.hpp>

#include <engine/Game.hpp>

class [[maybe_unused]] OpenGLWidget
        : public QOpenGLWidget
                , public engine::Game
{
private:

    engine::Entity m_player{};

private:

    float m_width = 0;
    float m_height = 0;

private:

    QTimer m_timer;

public:

    [[maybe_unused]] explicit OpenGLWidget (QWidget *parent = nullptr);
    ~OpenGLWidget () override;

protected:

    void initializeGL () override;
    void resizeGL (int width, int height) override;
    void paintGL () override;
};
