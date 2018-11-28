#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QKeyEvent>

GameWindow::GameWindow(GameControl* _game, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow),
    game(_game)
{
    ui->setupUi(this);
    connect(this, &GameWindow::KeyPress, this->game, &GameControl::move);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key()==Qt::Key_W || event->key()==Qt::Key_S || event->key()==Qt::Key_D || event->key()==Qt::Key_A) {
        emit KeyPress(event->key());
    }
}


void GameWindow::paint_map() {
    qDebug() << "hi";
    for (std::vector<std::vector<int>>::iterator row = game->map.begin(); row != game->map.end(); ++row) {
        std::vector<int> col_list = *row;
        for (std::vector<int>::iterator block = col_list.begin(); block != col_list.end(); ++block) {
            if (*block == 0) {
                // debug
                qDebug()<< "w ";
            } else {
                qDebug() << "r ";
            }
            Block* me = new Block(this, nullptr, row-game->map.begin(),block - col_list.begin(),*block, 0);
            game->map_block.push_back(me);

        }
        qDebug() << '\n';
    }
}
