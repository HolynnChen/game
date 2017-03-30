#pragma once
#include <iostream>
#include <memory>
#include <array>
#include <vector>
#include <random>
#include <ctime>
#include <conio.h>
#include <string>
using namespace std;

class mygame {
public:
	mygame();//无参构造函数
	void game_start(int n, int once=1);//有参构造函数,生成n*n大小矩阵
	bool game_randomadd(int n);//根据最后一次方向键记录随机加入n个1或2（不可小于0，不可大于矩阵大小n）若空位不足则默认填满该列，若矩阵叠加后无空位则游戏失败
	void game_printgame();//打印游戏
	void game_getch();//循环监听，esc键退出，过滤其他键，仅监听方向键
private:
	vector<vector<int> > game;//储存游戏矩阵
	int game_max=0;//储存游戏最大值
	int game_onceoccur = 1;//储存一次性出现的变量个数
	void game_turnway(int way);//改变矩阵方向阅读方向，与进入方向说明相同
	void game_downadd();//向下叠加
	void game_sort();//整理
	int game_getnumber(vector<vector<int> > &gamearray,int x, int y);//默认左上角为0点，向下x，向右y
	void game_setnumber(vector<vector<int> > &gamearray, int x, int y, int number);//默认左上角为0点，向下x，向右y
	int way=0;//进入方向，默认为0，下，左，上，右分别为1,2,3,4
	/*目前用不到的高级功能*/
	void game_srsp(int ar_s_xy_i, int ar_s_xy_j, int ar_s_i_i, int ar_s_i_j, int ar_s_j_i, int ar_s_j_j);//设置矩阵阅读起始点与基向量
	int ar_i[2] = {1,0}, ar_j[2] = { 0,1 };//储存基向量i,j
	int ar_s[2] = {0,0};//储存初始阅读点
	int game_continue = true;//保持进行
	int game_score = 1;//分数
};

mygame::mygame() {
	srand((unsigned)time(NULL));
	system("cls");
	game_continue = true;
	game_turnway(1);
	cout << "游戏:2048"<<endl<<"按空格键开始游戏" << endl;
	while(_getch()!=32){}
	//可以用于初始化，自动清空上次的矩阵
	return;
}

void mygame::game_start(int n, int once) {
	game_onceoccur = once;
	vector<vector<int> > array(n);
	for (int i = 0; i < n; i++)
	{
		array[i].resize(n);
	}
	game = array;
	game_max = n;
	game_printgame();
	return;
}

int mygame::game_getnumber(vector<vector<int> > &gamearray, int x, int y) {
	if (game_max<1||ar_s[0] + ar_i[0]*x + ar_j[0] * y > game_max - 1 || ar_s[0] + ar_i[0]*x + ar_j[0] * y<0 || ar_s[1] + ar_i[1] * x + ar_j[1]*y>game_max - 1 || ar_s[1] + ar_i[1] * x + ar_j[1]*y < 0) {
		return -1;
	}else {
		//cout << "读取了" << x << "!" << y << "位,内容为" << gamearray[ar_s[0] + ar_i[0] * x + ar_j[0] * y][ar_s[1] + ar_i[1] * x + ar_j[1] * y] << endl;
		return gamearray[ar_s[0] + ar_i[0]*x+ar_j[0]*y][ar_s[1] + ar_i[1]*x+ar_j[1]*y];
	}
}

void mygame::game_setnumber(vector<vector<int> > &gamearray, int x, int y, int number) {
	if (game_max<1 || ar_s[0] + ar_i[0] * x + ar_j[0] * y > game_max - 1 || ar_s[0] + ar_i[0] * x + ar_j[0] * y<0 || ar_s[1] + ar_i[1] * x + ar_j[1] * y>game_max - 1 || ar_s[1] + ar_i[1] * x + ar_j[1] * y < 0) {
		return;
	}
	else {
		//cout << "写入了" << x << "!" << y << "位,内容为" << number << endl;
		gamearray[ar_s[0] + ar_i[0] * x + ar_j[0] * y][ar_s[1] + ar_i[1] * x + ar_j[1] * y]=number;
		return;
	}
}

void mygame::game_turnway(int way) {
	switch (way)
	{
	case 1:
		game_srsp(0,0,1,0,0,1);
		break;
	case 2:
		game_srsp(game_max-1, 0, 0, 1, -1, 0);
		break;
	case 3:
		game_srsp(game_max-1,game_max-1,-1,0,0,-1);
		break;
	case 4:
		game_srsp(0, game_max - 1, 0, -1, 1, 0);
		break;
	default:
		break;
	}
}

void mygame::game_srsp(int ar_s_xy_i, int ar_s_xy_j, int ar_s_i_i, int ar_s_i_j, int ar_s_j_i, int ar_s_j_j)
{
	ar_s[0] = ar_s_xy_i;
	ar_s[1] = ar_s_xy_j;
	ar_i[0] = ar_s_i_i;
	ar_i[1] = ar_s_i_j;
	ar_j[0] = ar_s_j_i;
	ar_j[1] = ar_s_j_j;
	return;
}

void mygame::game_downadd() {
	int p1, p2,ps_1,ps_2;//p1p2位置一位置二的数字,ps_1为x轴阅读起点,ps_2为y轴阅读起点
	game_sort();
	vector<vector<int> > checkgame = game;
	for (int i = 0; i < game_max; i++)//y轴
	{
		ps_1 = game_max - 1;
		ps_2 = i;
		do {
			p1 = game_getnumber(checkgame, ps_1, ps_2);
			p2 = game_getnumber(checkgame, ps_1 - 1, ps_2);
			if (p1 == p2&&p1!=0) {
				game_setnumber(game, ps_1, ps_2, p1 + p2);
				game_setnumber(game, ps_1 - 1, ps_2, 0);
				ps_1 = ps_1 - 2;
				if (2 * p1 > game_score)game_score = 2 * p1;
			}
			else
			{
				ps_1--;
			}
		} while (ps_1>0);
	}
	game_sort();
}

void mygame::game_sort() {
	//这里开始推移
	for (int i = 0; i < game_max; i++) {//这里是y轴
		int last = 0;//最后搜寻位
		for (int j = 0; j < game_max-1; j++) {//这里是x轴
			if (game_getnumber(game, game_max - 1 - j, i) == 0) {
				if (j > last) last = j;
				while (last < game_max) {
					last++;
					if (last < game_max) {
						if (game_getnumber(game, game_max - 1 - last, i) != 0) {
							game_setnumber(game, game_max - 1 - j, i, game_getnumber(game, game_max - 1 - last, i));
							game_setnumber(game, game_max - 1 - last, i, 0);
							break;
						}
					}
					else { goto llo; }
				}
			}
		}
	llo:;
	}
}

bool mygame::game_randomadd(int n) {
	for (int k = 0; k < n; k++) {
	int allzero = 0, nnn, putin;
	vector<int> wei;
	for (int i = 0; i < game_max; i++)
	{
		if (game_getnumber(game, 0, i) == 0) {
			allzero++;
			wei.push_back(i);
		}
	}
	if (allzero != 0) {
		nnn = rand() % allzero;
		putin = rand() % 2 + 1;
		game_setnumber(game, 0, wei[nnn], putin);
	}
	else {
		system("cls");
		cout << "你输了，最大分数："<<game_score << endl;
		system("pause");
		system("cls");
		game_continue = false;
		return false;
	}
	}return true;
}

void mygame::game_printgame() {
	system("cls");
	int oi = 0,io=game_score,io2,io3,oi1=0;
	while (io != 0)
	{
		oi++;
		io = io / 10; 
	}
	for (int i = 0; i < game_max; i++)
	{
		for (int j = 0; j < game_max; j++){
			oi1 = 0;
			io2 = game_getnumber(game, i, j);
			io3 = io2;
			io2=io2+1;
			while (io2 != 0)
			{
				oi1++; 
				io2 = io2 / 10;
			}
			cout << io3;
			for (int i = 0; i < oi-oi1+1; i++)
			{
				cout << " ";
			}
			//if (oi - oi1 + 1 <1) { cout << "!!" << oi << "!" << oi1 << "!!"; system("pause"); };
		}
		cout << endl;
	}

}

void mygame::game_getch() {
	int ch;
	while (game_continue && (ch = _getch()) != 0x1B ) /* Press ESC to quit... */
	{
		switch (ch)
		{
		case 0xE0:
			switch (ch = _getch())
			{
			case 72:  game_turnway(3);break;
			case 80:  game_turnway(1);break;
			case 75:  game_turnway(4);break;
			case 77:  game_turnway(2);break;
			default:
				break;
			};
			game_downadd(); 
			if(game_randomadd(game_onceoccur)){
				game_turnway(1);
				game_printgame();
			}
			break;
		default:
			break;
		}
	}
	game_continue = false;
	cout << "按Q可进行下一局，按ESC可退出程序" << endl;
	while ((ch = _getch()) != 0x1B) /* Press ESC to quit... */
	{
		switch (ch)
		{
		case 113: goto hhto; break;
		default:
			break;
		}
	}
	return;
	//next
hhto: system("cls"); game_continue = true; game_start(game_max, game_onceoccur); game_getch();
}