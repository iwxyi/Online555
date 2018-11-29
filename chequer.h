#ifndef CHEQUER_H
#define CHEQUER_H

const int BOARD_SIZE         = 16; // 棋盘大小
const int BOARD_SIZE_MAXN    = 50; // 棋盘大小上限
const int PIECE_NONE         = 0; // 没有棋子
const int PIECE_BLACK        = 1; // 黑棋子（玩家一）
const int PIECE_WHITE        = 2; // 白棋子（玩家二）

#include <QWidget>
#include <QString>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QMessageBox>
#include "globals.h"

class Chequer
{
public:
    Chequer();

	void init(); // 初始化棋盘
	void start(); // 开始游戏，玩家一先开始
	void setBoardLength(int x); // 设置格子边长
	void movesBoard(int mouseX, int mouseY); // 落子
    void movesGrid(int x, int y); // 落子到棋盘格子（protected提权）
    int getBoardSize();

protected:
	void paint(QPainter &painter);
    virtual void movesGridEvent(int, int){ } // 用来覆盖的函数
    virtual void gameOverEvent(int, int) { } // 游戏结束事件
	void nextTurn();

    bool isTurn(int t);
	bool isGameOver(int x, int y); // 检测是否结束
	void gameOver(int player); // 胜利者

private:
	int board[BOARD_SIZE_MAXN][BOARD_SIZE_MAXN];
	bool board_static[BOARD_SIZE_MAXN][BOARD_SIZE_MAXN];
	int board_length, grid_length, piece_radius;
	int turn;
};


#endif // CHEQUER_H
