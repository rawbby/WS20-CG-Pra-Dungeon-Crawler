#pragma once

#include <QTimer>
#include <QPoint>
#include <QWidget>
#include <QOpenGLWidget>
#include <vector>

#include <asset/Drawable.hpp>
#include <geometries/Geometries.hpp>

class [[maybe_unused]] OpenGLWidget
        : public QOpenGLWidget
{
private:

    float m_width  = 0;
    float m_height = 0;

private:

    const float M_MIN_DISTANCE      = 1.0f;
    const float M_MAX_DISTANCE      = 6.0f;
    const float M_CAMERA_ROTATION_X = 65.0f;

    float m_camera_rotation_y = 0.0f;
    float m_camera_distance   = M_MIN_DISTANCE;

    QTimer m_timer;
    QPoint m_mouse_position   = {};
    bool   m_mouse_pressed    = false;

private:

    std::vector<asset::MaterialDrawable> m_materialDrawable;

public:

    [[maybe_unused]] explicit OpenGLWidget (QWidget *parent = nullptr);
    ~OpenGLWidget () override;

protected:

    void initializeGL () override;
    void resizeGL (int width, int height) override;
    void paintGL () override;

protected:

    void mousePressEvent (QMouseEvent *event) override;
    void mouseReleaseEvent (QMouseEvent *event) override;
    void mouseMoveEvent (QMouseEvent *event) override;
    void wheelEvent (QWheelEvent *event) override;
};
