#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QKeyEvent>
#include "wall.h"
#include "road.h"
#include "accel.h"
#include "terminate.h"
#include <QDebug>

GameWindow::GameWindow(GameControl* _game, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow),
    game(_game)
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
    qDebug()<<"player:"<< game->player->getRow() <<','<< game->player->getCol() <<endl;

    for (std::vector<std::vector<int>>::iterator row = game->map.begin(); row != game->map.end(); ++row) {
        qDebug()<<"loop";
        std::vector<int> col_list = *row;
        std::vector<Block*> _board = {};
        for (std::vector<int>::iterator block = col_list.begin(); block != col_list.end(); ++block) {
            Block* tile;
            qDebug()<<row-game->map.begin()<<','<<block-col_list.begin()<<endl;

            switch (*block) {
            case GameControl::R : // Normal road
                //tile = new Road(row-game->map.begin(), block-col_list.begin(), this);
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
                tile = new Accel(row-game->map.begin(),block-col_list.begin(), static_cast<DIRECTION>(*block - GameControl::A), this);
                qDebug() << dynamic_cast<Accel*>(tile)->getDir();
                break;
            default:
                tile = new Road(row-game->map.begin(), block-col_list.begin(), this);
                qDebug() << "called by default";
                break;
            }
            qDebug() << *block;

            tile->set_image(*(game->player));
            _board.push_back(tile);
        }
        qDebug() << '\n';
        game->board.push_back(_board);
    }
}

void GameWindow::paint_player() {
    // not implemented; return when called
    return;
}

//void GameWindow::rotate() {
//    for (int i = 0; i< game->map.size(); ++i) {
//        for (int j = 0; j<game->map.size(); ++j) {
//            int old_r = game->board[i][j]->getRow();
//            int old_c = game->board[i][j]->getCol();
//            game->board[i][j]->setRow(game->map.size()-old_c);
//            game->board[i][j]->setCol(old_r);

//        }
//    }
//}

void GameWindow::update_map(){
    for ( int r = 0; r < game->board.size(); ++r) {
        for (int c = 0; c < (game->board[0]).size(); ++c) {
            ((game->board)[r][c])->set_image(*(game->player));
        }
    }
}

void GameWindow::closeEvent(QCloseEvent *event) {
    emit gameWindow_closed();
}
