#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class GameControl;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameControl* game = nullptr;

public slots:
    void game_started();
    void game_closed();
};

#endif // MAINWINDOW_H
