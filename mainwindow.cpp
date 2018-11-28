#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamecontrol.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GameControl* game = new GameControl();
    this->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
