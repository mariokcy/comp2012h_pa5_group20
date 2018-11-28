#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

//Control Game Window Display
namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private:
    Ui::GameWindow *ui;
};

#endif // GAMEWINDOW_H
