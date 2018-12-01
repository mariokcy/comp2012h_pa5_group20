#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QKeyEvent>
#include "wall.h"
#include "road.h"
#include "accel.h"
#include "terminate.h"
#include "block.h"
#include <QDebug>

GameWindow::GameWindow(GameControl* _game, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow),
    game(_game),
    paint(new QPainter(this))
{
    ui->setupUi(this);
    show();
    connect(this, &GameWindow::KeyPress, this->game, &GameControl::move);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key()==Qt::Key_W || event->key()==Qt::Key_S || event->key()==Qt::Key_D || event->key()==Qt::Key_A || event->key()==Qt::Key_R) {
        emit KeyPress(event->key());
    }
}


void GameWindow::load_map() {
    qDebug() << "hi";
    for (std::vector<std::vector<int>>::iterator row = game->map.begin(); row != game->map.end(); ++row) {
        qDebug()<<"loop";
        std::vector<int> col_list = *row;
        std::vector<Block*> _board = {};
        for (std::vector<int>::iterator block = col_list.begin(); block != col_list.end(); ++block) {
            Block* tile;
            switch (*block) {
            case GameControl::R : // Normal road
                tile = new Road(row-game->map.begin(), block-col_list.begin(), this);
                qDebug() << "R";
                break;
            case GameControl::W : // Wall
                tile = new Wall(row-game->map.begin(),block-col_list.begin(), this);
                qDebug() << "W";
                break;
            case GameControl::T : // Terminate
                tile = new Terminate(row-game->map.begin(),block-col_list.begin(), this);
                qDebug() << "T";
                break;
            case GameControl::A :
            case GameControl::B :
            case GameControl::C :
            case GameControl::D :
                tile = new Accel(row-game->map.begin(),block-col_list.begin(), static_cast<Accel::DIRECTION>(*block - GameControl::A), this);
                qDebug() << dynamic_cast<Accel*>(tile)->getDir();
                break;
            default:
                tile = new Road(row-game->map.begin(), block-col_list.begin(), this);
                qDebug() << "called by default";
                break;
            }
            qDebug() << *block;
            tile->set_image();
            _board.push_back(tile);
        }
        qDebug() << '\n';
        game->board.push_back(_board);
    }
    rotate(0);
    paint_player();
}

void GameWindow::paint_player() {
    paint->drawImage(QRect(game->player->getCol()*Block::BLOCK_SIZE,game->player->getRow()*Block::BLOCK_SIZE,Block::BLOCK_SIZE,Block::BLOCK_SIZE),
                     QImage("/resources/player.png"));
}

void GameWindow::rotate(int dir) {
    for (int i = 0; i< game->map.size(); ++i) {
        for (int j = 0; j<game->map.size(); ++j) {
            int old_r = game->board[i][j]->getRow();
            int old_c = game->board[i][j]->getCol();
            game->board[i][j]->setRow(game->map.size()-old_c);
            game->board[i][j]->setCol(old_r);

        }
    }
}

void GameWindow::update_map(){
    load_map();
    Block* target_block = game->board[game->player->getCol()][game->player->getRow()];
    paint_player();
}
