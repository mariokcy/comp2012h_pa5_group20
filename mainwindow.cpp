#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GameWindow* game = new GameWindow();
    game->show();
    this->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
