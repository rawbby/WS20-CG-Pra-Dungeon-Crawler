#pragma once

#include <QMainWindow>
#include <cstdlib>
#include <array>

namespace gui
{
    constexpr float MIN_DISTANCE = 0.3f;
    constexpr float MAX_DISTANCE = 6.0f;
    constexpr float CAMERA_ROTATION_X = -25.0f;

    inline float camera_rotation_y = 0.0f;
    inline float camera_distance = MIN_DISTANCE;

    constexpr size_t KEY_A = 0;
    constexpr size_t KEY_S = 1;
    constexpr size_t KEY_W = 2;
    constexpr size_t KEY_D = 3;

    inline std::array<bool, 4> key_states;
}

namespace Ui
{
    class MainWindow;
}

class MainWindow
        : public QMainWindow
{
Q_OBJECT

private:

    QPoint m_mouse_position = {};
    bool m_mouse_pressed = false;

private:

    std::unique_ptr<Ui::MainWindow> m_ui;

public:

    explicit MainWindow (QWidget *parent = nullptr);
    ~MainWindow () override;

protected:

    [[maybe_unused]] void mousePressEvent (QMouseEvent *event) override;
    [[maybe_unused]] void mouseReleaseEvent (QMouseEvent *event) override;
    [[maybe_unused]] void mouseMoveEvent (QMouseEvent *event) override;
    [[maybe_unused]] void wheelEvent (QWheelEvent *event) override;

protected:

    [[maybe_unused]] void keyPressEvent (QKeyEvent *event) override;
    [[maybe_unused]] void keyReleaseEvent (QKeyEvent *event) override;
};
