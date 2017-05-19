// 2048.cpp : 定义控制台应用程序的入口点。
//2048游戏
#include "mygame.h"
int main()
{
    mygame a;
	a.game_start(9,3);//说明：创建一个n*n大小的矩阵，默认一次出现一个新的数
	a.game_getch();//说明：开始监听键盘，Esc键终止当前游戏或退出程序。
}

