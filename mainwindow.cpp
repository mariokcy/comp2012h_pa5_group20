#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamecontrol.h"
#include "gamewindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::game_started);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::game_started() {
    if (game==nullptr) game = new GameControl();
    connect(game->game_window, &GameWindow::gameWindow_closed, this, &MainWindow::game_closed);
    this->hide();
}

void MainWindow::game_closed() {
    this->show();
}
