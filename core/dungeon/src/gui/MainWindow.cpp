#include <gui/MainWindow.hpp>
#include <ui_mainwindow.h>

#include <QKeyEvent>

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

MainWindow::MainWindow (QWidget *parent)
        : QMainWindow(parent)
        , m_ui(std::make_unique<Ui::MainWindow>())
{
    m_ui->setupUi(this);
}

MainWindow::~MainWindow () = default;

[[maybe_unused]] void MainWindow::mousePressEvent (QMouseEvent *event)
{
    m_mouse_pressed = true;
    m_mouse_position = event->pos();
}

[[maybe_unused]] void MainWindow::mouseReleaseEvent (QMouseEvent *event)
{
    Q_UNUSED(event);
    m_mouse_pressed = false;
}

[[maybe_unused]] void MainWindow::mouseMoveEvent (QMouseEvent *event)
{
    if (m_mouse_pressed)
    {
        auto delta = event->pos() - m_mouse_position;
        m_mouse_position = event->pos();

        const auto dx = -static_cast<float> (delta.x());
        gui::camera_rotation_y = mod360(gui::camera_rotation_y + dx);
    }
}

[[maybe_unused]] void MainWindow::wheelEvent (QWheelEvent *event)
{
    const auto delta = static_cast<float> (-event->angleDelta().y()) / 512.0f;
    gui::camera_distance = clamp(gui::camera_distance + delta, gui::MIN_DISTANCE, gui::MAX_DISTANCE);
}

[[maybe_unused]] void MainWindow::keyPressEvent (QKeyEvent *event)
{
    switch (event->key())
    {   //@formatter:off
        case Qt::Key_A: gui::key_states[0] = true; break;
        case Qt::Key_S: gui::key_states[1] = true; break;
        case Qt::Key_W: gui::key_states[2] = true; break;
        case Qt::Key_D: gui::key_states[3] = true; break;
    }   //@formatter:on
}

[[maybe_unused]] void MainWindow::keyReleaseEvent (QKeyEvent *event)
{
    switch (event->key())
    {   //@formatter:off
        case Qt::Key_A: gui::key_states[0] = false; break;
        case Qt::Key_S: gui::key_states[1] = false; break;
        case Qt::Key_W: gui::key_states[2] = false; break;
        case Qt::Key_D: gui::key_states[3] = false; break;
    }   //@formatter:on
}
