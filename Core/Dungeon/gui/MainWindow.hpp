#pragma once

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow
        : public QMainWindow
{
Q_OBJECT

private:
    std::unique_ptr<Ui::MainWindow> m_ui;

public:
    explicit MainWindow (QWidget *parent = nullptr);
    ~MainWindow () override;
};
