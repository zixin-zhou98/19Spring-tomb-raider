//TombRaider1.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "TombRaider1.h"
#define MAX_LOADSTRING 100
//Items on the map
#define STONE 1
#define BOX 3
#define GRASS 2
#define HOUSE 4
#define GHOSTC 5
#define BOMBC 6
#define CHARACTER 7
#define TRAP 11
#define FOOD 12
#define FLW0 20
#define FLW1 21
#define FLW2 22
#define FLW3 23
//#define FLW4 24
#define TR0 30
#define STN0 40

//道具
#define BOOK 8
#define SHOE 9
#define BUBBLE 10
#define BIRTH -2
//按键ID
#define IDB_ONE 3301
#define IDB_ZERO 3300
#define IDB_TWO 3302
#define IDB_THREE 3303
#define IDB_FOUR 3304
#define IDD_ZERO 2200
#define IDB_DONE 3311
#define IDB_DTWO 3312

#define IDB_DTHREE 3313

#define inf 1000000000

#define MAX_X 577
#define MAX_Y 577
#define MAX_XA 19
#define MAX_YA 19
#define ghost_speed 0.1
#define meet 200
// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
MCI_OPEN_PARMS m_mciOpen;
MCI_PLAY_PARMS m_mciPlay;
struct pixel_map {
	int F;//和
	int G;//已走距离
	int H;//剩余距离估计量
	int preX;
	int preY;
	bool isInClose = false;
	bool isInOpen = false;
};
struct Box {
	int hp = 600;
	bool state = true;
	int x;
	int y;
};
int ghostcnt[27] = {};
int mapcopy[18][18]= {
{-2, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 2, -1, 2, -1, -1, 2, -1, 2, 2, 2, TRAP, 2, -1, 2, -1, 2, -1},
{2, 2, 2, 2, 2, -1, 2, -1, 2, -1, 2, 2, 2, 2, 2, -1, 2, -1},
{-1,2, FOOD, 2, -1, -1, 2, 2, 2, -1, 2, -1, TR0, TR0, -1, -1, 2, -1},
{-1, 2, 2, 2, 2, 2, 2, -1, 2, -1, 2, 2, 2, 2, 2, 2, -1,2 },
{FLW0, 2, 2, -1, 2, 2, 2, 2, -1, 2, 2, 2, FOOD, 2, 2, 2, -1, 2},
{-1, 2, -1, 2, -1, -1, 2, TRAP, -1, 2, 2, 2, 2, 2, -1,2, -1 , -1},
{-1, -1, 2, 2, -1, 2, 2, 2, -1, 2, -1, 2, -1, -1, 2, 2,  FLW0,2},
{-1, -1, FLW0, 2, FOOD, 2, -1, -1, -1, 2, -1, 2, 2, -1, -1, 2, FLW0 ,2},
{-1, 2, -1, 2, -1, 2, 2, 2, 2, 2, 2, -1, 2, -1, 2, -1,FLW0 ,2 },
{-1, 2, -1, 2, -1, -1, -1, TRAP,2, 2, -1, 2, 2, 2, 2,2 , -1, -1},
{-1, 2, -1, 2, -1, 2, 2, 2, 2, 2, -1, 2, 2, -1, 2, -1, 2, -1},
{-1, -1, 2, 2, 2, 2, -1, -1, 2, 2, -1, -1, 2, -1, 2, 2,-1, -1},
{-1, -1, 2,TRAP, -1, -1, TR0,2, -1, 2, 2, 2, 2, 2, 2, 2, -1, -1},
{-1, 2, 2, 2, 2, FLW0, 2, 2, -1, 2, -1, 2, -1, TRAP, 2, 2, 2, -1},
{TR0, -1, 2, -1, FLW0, -1, 2, 2, -1, FLW0, -1, 2, -1,  2, 2, BOX,2,  -1},
{-1, -1, 2, 2, 2, -1, 2, FLW0, 2, -1, 2,FOOD, 2, 2,  2, HOUSE,TR0,2 },
{-1, -1, -1, -1, TR0, TR0, -1, -1, -1, FLW0, -1, -1, -1, 2, 2,TR0, TR0,  2 }
};

int map[18][18] = {
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,-1},
{1,2,2,2,2,2,2,2,-1,-1,2,2,2,2,2,-1,2,-1},
{-1,2,-1,2,-1,2,2,2,FOOD,2,2,-1,-1,-1,2,-1,2,-1},
{1,2,-1,2,-1,2,2,2,-1,-1,2,-1,2,-1,2,2,2,-1},
{1,2,-1,2,FOOD,-1,2,2,2,-1,2,-1,2,-1,2,-1,-1,-1},
{TR0,2,-1,2,2,2,TRAP,FLW0,2,-1,2,-1,2,-1,2,2,2,-1},
{TR0,2,2,-1,-1,2,2,FLW0,2,2,2,2,2,2,-1,-1,2,-1},
{1,2,TR0,2,2,2,-1,BOX,2,BOX,BOX,2,2,FOOD,2,2,2,-1},
{1,2,TR0,-1,2,2,2,2,BOX,4,BOX,2,2,2,2,-1,-1,TR0},
{-1,2,TR0,2,2,2,-1,TRAP,2,BOX,BOX,-1,2,TRAP,-1,2,2,-1},
{-1,2,2,2,-1,2,-1,2,BOX,2,2,2,2,-1,2,2,2,-1},
{1,2,2,2,-1,2,2,2,FOOD,2,-1,2,2,-1,2,-1,-1,-1},
{1,2,-1,2,-1,-1,-1,2,2,2,-1,TRAP,2,2,2,TR0,2,-1},
{1,-1,-1,2,2,2,-1,2,2,2,-1,2,-1,2,-1,TR0,2,-1},
{FLW0,2,2,2,-1,TRAP,-1,-1,-1,2,-1,2,-1,2,-1,2,2,-1},
{FLW0,-1,-1,2,2,2,2,2,-1,2,-1,2,-1,2,-1,2,-1,-1},
{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,-1},
{-1,-1,-1,-1,-1,-1,-1,FLW0,FLW0,-1,-1,-1,-1,-1,TR0,TR0,-1,-1}
};
int col = 18;
int row = 18;
int num;
int num_box = 0;
int countatk = 0;
int maxBomb = 2;
int item[25] = {};
int bombplus = 0;
int countHurt = 0;
int countGhost = 0;
int cntMusic = 0;
int traptime[5][2] = {};
int countTrap = 0;
int countvic = 0;
bool sec = false;
bool dopaint = true;
int deg = 1;
bool haveGhost = false;
bool secvic = false;
HDC gvdc, gvdcbuf, gvbgdc,gvbgdcs;
HBITMAP dog[4], dogn[4],monster[4],monstern[4], monsters[4], monsterns[4];
HBITMAP gvbg,vicbg,vicbg2;
HBITMAP gv, gvn, gvmap;
HWND hBtn1,hBtn2,hBtn3,hBtnEtr,hBtnQuit,hBtnStop;
HWND resEtr,resExt;
HBITMAP btnetrbmp, btnextbmp,musicclsbmp,deg1,deg2,deg3;
HWND hwnd,swnd;
HWND startwd;
DWORD tPre, tNow; 
HDC sdc,mdc, hdc, bufdc, bufdc_walk,bufdc_n;
HDC mdcs, hdcs, bufdcs, bufdc_walks, bufdc_ns, ghostdcs, ghostdcns,bombdcs;
HDC ghostdc, ghostdcn;
HDC bombdc;
HDC bgbufdc,bgdc;

HBITMAP trap, trapn,food,foodn;
HBITMAP base, box, house, housen, fullmap, girl[4], girln[4], walk0, walk1, walk2,walk3, walkn0, walkn1, walkn2, walkn3;
HBITMAP ghost[4], ghostn[4],bomb,bombn,bombs;
HBITMAP bgmap,bgpic, hp1, hp2, hp3, hp4, hp5, hp6, hp7, hp8, hp9, hp10, hp1n, hp2n, hp3n, hp4n, hp5n, hp6n, hp7n, hp8n, hp9n, hp10n;

HBITMAP bookbmp, bubblebmp,bubblen, shoebmp,shoen;
HBITMAP lflower,lflowern,flower0, flower1, flower2, flower3, flower4, stone0, tree0;
People people(1000, 30, 30, 0, 10);
LList<Ghost> ghostlist, ghostlists;
LList<Bomb> bomblist, bomblists;
LList<Box> boxlist, boxlists;
// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//函数原型
void paintMap(HDC hdc,HDC mdc);
void paintWalk(HDC hdc, HDC mdc, HDC bufdc_n, HDC bufdc_walk);
void generateMap();
bool checkCollision(int x,int y,int targetdir,int speed);
void generateGhost(int freq);
void generateGhosts(int freq);
void paintGhost(HDC hdc, Ghost g, HDC mdc, HDC ghostdcn, HDC ghostdc);
void initPeople(People p);
void paintBomb(HDC hdc, HDC bombdc, HDC mdc, Bomb b);
bool canPutBomb(Bomb *b);
void doHurt(Bomb *b, LList<Ghost> ghostlist, LList<Box> boxlist, HDC hdc);
bool getPeople(People*& it);
void checkAlive(People *it);
void gameOver(HDC hdc);
void paintbg(HDC hdc);
void initBox();
void initBoxs();
void paintvic(HDC hdc);
void initItems();
void pickItem();
void gHurtP(Ghost *g,People *p);
void paintHP(int hp,int x,int y,HDC hdc);
double dis(int x1, int y1, int x2, int y2);
int returnHelp(int curX, int curY, People people);
void calculate(pixel_map **pmap, int curX, int curY, int preX, int preY, People people);
bool add(int curX, int curY, pixel_map **pmap, People people);
bool checkGCollision(int x, int y, int targetdir, int speed);
void initS();
bool checkTrap();
bool checkFood();

void initS()
{
	sdc = GetDC(swnd);

}
bool checkFood()
{

	switch (people.dir)
	{
	case 0:
		if (map[(people.x + 16) / 32][(people.y + 10) / 32] == FOOD)
		{
			map[(people.x + 16) / 32][(people.y + 10) / 32] = GRASS;
			return true;
		}
		break;
	case 1:
		if (map[(people.x + 16) / 32][(people.y + 32 - 10) / 32] == FOOD)
		{
			map[(people.x + 16) / 32][(people.y + 32 - 10) / 32] = GRASS;
			return true;
		}
		break;
	case 2:
		if (map[(people.x + 10) / 32][(people.y + 16) / 32] == FOOD)
		{
			map[(people.x + 10) / 32][(people.y + 16) / 32] = GRASS;
			return true;
		}
		break;
	case 3:
		if (map[(people.x + 32 - 10) / 32][(people.y + 16) / 32] == FOOD)
		{
			map[(people.x + 32 - 10) / 32][(people.y + 16) / 32] = GRASS;
			return true;
		}
		break;
	}
	return false;
}
//return true代表被trap到了，false代表没有
bool checkTrap()
{
	
	switch (people.dir)
	{
	case 0:
		if (map[(people.x + 16) / 32][(people.y + 10) / 32] == TRAP)
		{
			map[(people.x + 16) / 32][(people.y + 10) / 32] = GRASS;
			return true;
		}
		break;
	case 1:
		if (map[(people.x + 16) / 32][(people.y + 32 - 10) / 32] == TRAP)
		{
			map[(people.x + 16) / 32][(people.y + 32 - 10) / 32] = GRASS;
			return true;
		}
		break;
	case 2:
		if (map[(people.x + 10) / 32][(people.y + 16) / 32] == TRAP)
		{
			map[(people.x + 10) / 32][(people.y + 16) / 32] = GRASS;
			return true;
		}
		break;
	case 3:
		if (map[(people.x + 32 - 10) / 32][(people.y + 16) / 32] == TRAP)
		{
			map[(people.x + 32 - 10) / 32][(people.y + 16) / 32] = GRASS;
			return true;
		}
		break;
	}
	return false;
}
bool checkGCollision(int x, int y, int targetdir, int speed)
{
	int w, h;
	w = h = 32;
	//选择图片大小

	//(1)计算人所在的坐标上下左右的地块是否是stone，是则表明有collision，返回true
	switch (targetdir)
	{
	case 0:
		if (y - speed<0 ||map[(x+2) / 32][(y-2 ) / 32] != GRASS || map[(x + w-2 ) / 32][(y - 2) / 32] != GRASS)
		{
			return true;
		}
		else
			return false;
		break;
	case 1:
		if (y + speed >530||map[(x+2 ) / 32][(y +h+4) / 32] != GRASS || map[(x + w-2) / 32][(y + h+ 4) / 32] != GRASS || ((x) / 32 == people.x / 32) && ((y) / 32 == people.y / 32) || ( (x+2 )/ 32 == people.x/32) && ((y+h+speed)  / 32 == people.y/32))
		{
			return true;
		}
		else
			return false;
		break;
	case 2:
		if (x - speed < 0||map[(x - 2) / 32][(y ) / 32] != GRASS || map[(x - 2) / 32][(y + h - 2) / 32] != GRASS || ((x) / 32 == people.x / 32) && ((y) / 32 == people.y / 32) || ((x-speed-2) / 32 == people.x/32) && ((y +2) / 32 == people.y/32))
		{
			return true;
		}
		else
			return false;
		break;
	case 3:
		if (x + speed> 530 || map[(x + w +2) / 32][(y + 2) / 32] != GRASS || map[(x + w + 2) / 32][(y + h - 2) / 32] != GRASS || ((x) / 32 == people.x / 32) && ((y) / 32 == people.y / 32) || ((x+w+speed )/ 32 == people.x/32) && ((y+2) / 32 == people.y/32))
		{
			return true;
		}
		else
			return false;
		break;

	}
	//否则返回false
	return false;
}
int path_finding(Ghost ghost, People people) {
	if (dis(ghost.x, ghost.y, people.x, people.y) <= meet) {//已经在玩家附近
		int temp = returnHelp(ghost.x, ghost.y, people);
		return temp;
	}
	else {
		pixel_map **pmap = new pixel_map*[MAX_XA+1];
		for (int i = 0; i < MAX_XA+1; i++) {
			pmap[i] = new pixel_map[MAX_YA+1];
		}
		//把当前位置添加到close列表
		pmap[ghost.x/32][ghost.y/32 ].isInClose = true;
		pmap[ghost.x / 32][ghost.y/32 ].G = 0;
		//相邻可行位置且不在close列表的格子加入open列表,上下左右
		bool bingo = false;
		bingo = add(ghost.x / 32, ghost.y / 32, pmap, people);
		char m[20] = "";
		sprintf_s(m, "hp%d", pmap[ghost.x / 32][ghost.y / 32].preX);
		if (bingo) {
		//空间释放
			{
				for (int i = 0; i < MAX_XA+1; i++) {
					delete[] pmap[i];
				}
				delete[] pmap;
			}
			return 0;
		}
		//更新bingo，若终点不在close列表中，则继续循环
		int flagX = -1, flagY = -1;
		int flagF = inf;
		while (!bingo) {
			//找出open列表中F值最小的方块，加入close列表中，对于与S相邻的每一块可通行的方块T：
			for (int i = 0; i < MAX_XA; i++) {
				for (int j = 0; j < MAX_YA; j++) {
					if (pmap[i][j].isInOpen && pmap[i][j].isInClose == false && pmap[i][j].F <= flagF) {
						flagF = pmap[i][j].F;
						flagX = i;
						flagY = j;
					}
				}
			}
			
			if (flagX == -1 && flagY == -1) {
				//空间释放
				{
					for (int i = 0; i < MAX_XA+1; i++) {
						delete[] pmap[i];
					}
					delete[] pmap;
				}
				return 0;
			}
			pmap[flagX][flagY].isInClose = true;
			bingo = add(flagX, flagY, pmap, people);
			if (bingo) {
				while (1) {
					int tempX = pmap[flagX][flagY].preX, tempY = pmap[flagX][flagY].preY;
					if (tempX == ghost.x/32 && tempY == ghost.y/32) {
						break;
					}
					flagX = tempX, flagY = tempY;
				}
			}
			else {
				flagX = -1, flagY = -1;
				flagF = inf;
			}
		}
		int direction;//0,1,2,3 represent up,down,left, right
		if (flagX == ghost.x/32) {
			if (flagY > ghost.y/32) {
				direction = 0;
			}
			else {
				direction = 1;
			}
		}
		else {
			if (flagX > ghost.x/32) {
				direction = 3;
			}
			else {
				direction = 2;
			}
		}
		//空间释放
		{
			for (int i = 0; i < MAX_XA; i++) {
				delete[] pmap[i];
			}
			delete[] pmap;
		}
		return direction;
	}

}
// distance between enemy and player
double dis(int x1, int y1, int x2, int y2) {
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}
int returnHelp(int curX, int curY, People people) {
	if (abs(curX - people.x) > abs(curY - people.y)) {//左或右
		if (curX > people.x) {
			return 2;
		}
		else return 3;
	}
	else {
		if (curY > people.y) {
			return 0;
		}
		else return 1;
	}

}

void calculate(pixel_map **pmap, int curX, int curY, int preX, int preY, People people) {
	pmap[curX][curY].isInOpen = true;
	pmap[curX][curY].preX = preX;
	pmap[curX][curY].preY = preY;
	pmap[curX][curY].G = pmap[preX][preY].G + 1 * ghost_speed;
	pmap[curX][curY].H = abs(people.x/32 - curX) + abs(people.y/32 - curY);
	pmap[curX][curY].F = pmap[curX][curY].G + pmap[curX][curY].H;
}

bool add(int curX, int curY, pixel_map **pmap, People people) {

	bool passable = true;
	{
		//上
	//判断可行，待补充
		passable = !checkGCollision(curX, curY, 0, ghost_speed);
		//end
		if (curX >= 0 && curX < MAX_XA && (curY + ghost_speed) >= 0 && 
			(int)ceil(curY + ghost_speed) < MAX_YA && curY >= 0 && curY < MAX_YA)
		{
			if (pmap[curX][(int)ceil(curY + ghost_speed)].isInClose == true) {

			}
			else {
				if (passable && pmap[curX][(int)ceil(curY + ghost_speed)].isInOpen == false) {
					calculate(pmap, curX, curY + ghost_speed, curX, curY, people);
					if (dis(curX, curY + ghost_speed, people.x, people.y) <= meet) {//已经在玩家附近
						//cout << "(" << curX << ", " << curY + ghost_speed << ")靠近人！" << endl;
						return true;
					}
				}
				else if (passable && pmap[curX][(int)ceil(curY + ghost_speed)].isInOpen == true) {
					if (pmap[curX][curY].G + ghost_speed + pmap[curX][(int)ceil(curY + ghost_speed)].H < pmap[curX][(int)ceil(curY + ghost_speed)].F) {
						calculate(pmap, curX, curY + ghost_speed, curX, curY, people);
					}
				}
				else {

				}
			}
		}


		//下
		//判断可行，待补充
		passable = !checkGCollision(curX, curY, 1, ghost_speed);
		//end

		if (curX >= 0 && curX < MAX_XA && (curY - ghost_speed) >= 0 && (curY - ghost_speed) < MAX_YA && curY >= 0 && curY < MAX_YA) {
			if (pmap[curX][(int)ceil(curY + ghost_speed)].isInClose == true) {

			}
			else {
				if (passable && pmap[curX][(int)ceil(curY + ghost_speed)].isInOpen == false) {
					calculate(pmap, curX, curY - ghost_speed, curX, curY, people);
					if (dis(curX, curY - ghost_speed, people.x, people.y) <= meet) {//已经在玩家附近
						//cout << "(" << curX << ", " << curY - ghost_speed << ")靠近人！" << endl;
						return true;
					}
				}
				else if (passable && pmap[curX][(int)ceil(curY + ghost_speed)].isInOpen == true) {
					if (pmap[curX][curY].G + ghost_speed + pmap[curX][(int)ceil(curY + ghost_speed)].H < pmap[curX][(int)ceil(curY + ghost_speed)].F) {
						calculate(pmap, curX, curY - ghost_speed, curX, curY, people);
					}
				}
				else {

				}
			}
		}


		//左
		//判断可行，待补充
		passable = !checkGCollision(curX, curY, 2, ghost_speed);
		//end
		if (curX >= 0 && curX < MAX_XA && curY >= 0 && curY < MAX_YA && (curX - ghost_speed) >= 0 && (curX - ghost_speed) < MAX_XA) {
			if (pmap[(int)ceil(curX + ghost_speed)][curY].isInClose == true) {

			}
			else {
				if (passable && pmap[(int)ceil(curX + ghost_speed)][curY].isInOpen == false) {
					calculate(pmap, curX - ghost_speed, curY, curX, curY, people);
					if (dis(curX - ghost_speed, curY, people.x, people.y) <= meet) {//已经在玩家附近
						//cout << "(" << curX - ghost_speed << ", " << curY << ")靠近人！" << endl;
						return true;
					}
				}
				else if (passable && pmap[(int)ceil(curX + ghost_speed)][curY].isInOpen == true) {
					if (pmap[curX][curY].G + ghost_speed + pmap[(int)ceil(curX + ghost_speed)][curY].H < pmap[(int)ceil(curX + ghost_speed)][curY].F) {
						calculate(pmap, curX - ghost_speed, curY, curX, curY, people);
					}
				}
				else {
				}
			}
		}
		//右
		passable = !checkGCollision(curX, curY, 3, ghost_speed);
		//end
		if (curX >= 0 && curX < MAX_XA && curY >= 0 && curY < MAX_YA && (curX + ghost_speed) >= 0 && (curX + ghost_speed) < MAX_XA) {
			if (pmap[(int)ceil(curX + ghost_speed)][curY].isInClose == true) {

			}
			else {
				if (passable && pmap[(int)ceil(curX + ghost_speed)][curY].isInOpen == false) {
					calculate(pmap,(int)ceil(curX + ghost_speed), curY, curX, curY, people);
					if (dis(curX + ghost_speed, curY, people.x, people.y) <= meet) {//已经在玩家附近
						return true;
					}
				}
				else if (passable && pmap[(int)ceil(curX + ghost_speed)][curY].isInOpen == true) {
					if (pmap[curX][curY].G + ghost_speed + pmap[(int)ceil(curX + ghost_speed)][curY].H < pmap[(int)ceil(curX + ghost_speed)][curY].F) {
						calculate(pmap,(int)ceil(curX + ghost_speed), curY, curX, curY, people);
					}
				}
				else {

				}
			}
		}

	}
	return false;
}

void paintHP(int hp,int x, int y, HDC hdc)
{

	switch (hp / 100)
	{
	case 1:
		SelectObject(gvdcbuf, hp1n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp1);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 2:
		SelectObject(gvdcbuf, hp2n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp2);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 3:
		SelectObject(gvdcbuf, hp3n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp3);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 4:
		SelectObject(gvdcbuf, hp4n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp4);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 5:
		SelectObject(gvdcbuf, hp5n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp5);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
	case 6:
		SelectObject(gvdcbuf, hp6n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp6);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 7:
		SelectObject(gvdcbuf, hp7n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp7);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 8:
		SelectObject(gvdcbuf, hp8n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp8);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 9:
		SelectObject(gvdcbuf, hp9n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp9);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	case 10:
		SelectObject(gvdcbuf, hp10n);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCAND);
		SelectObject(gvdcbuf, hp10);
		BitBlt(hdc, x - 10, y - 15, 50,10, gvdcbuf, 0, 0, SRCPAINT);
		break;
	}

}
void gHurtP(Ghost *g,People *p)
{
	switch (g->dir)
	{
	case 0:
		if ((g->x+12) / 32 == people.x / 32 && (g->y-10) / 32 == people.y / 32||(g->x/32==people.x/32)&& (g->y / 32 == people.y / 32))
		{
			countHurt++;
		}
		break;
	case 1:
		if ((g->x+12) / 32 == people.x / 32 && (g->y+32+1) / 32 == people.y / 32 || (g->x / 32 == people.x / 32) && (g->y / 32 == people.y / 32))
		{
			countHurt++;
		}
		break;
	case 2:
		if ((g->x-6) / 32 == people.x / 32 && (g->y+5) / 32 == people.y / 32 || (g->x / 32 == people.x / 32) && (g->y / 32 == people.y / 32))
		{
			countHurt++;
		}
		break;
	case 3:
		if ((g->x+32-4) / 32 == people.x / 32 && (g->y) / 32 == people.y / 32 || (g->x / 32 == people.x / 32) && (g->y / 32 == people.y / 32))
		{
			
			countHurt++;
		}
		break;
	}
	if(countHurt>=18)
	{
		p->hp -= g->atk;
		countHurt = 0;
	}
	
}
void pickItem()
{
	int ix = 0;
	int iy = 0;
	switch (people.dir)
	{
	case 0:
		ix = (people.x + 3) / 32;
		iy = (people.y+5) / 32-1;
		break;
	case 1:
		ix = (people.x+10) / 32;
		iy = (people.y+5) / 32+1;
		break;
	case 2:
		ix = (people.x+6) / 32-1;
		iy = (people.y+5) / 32;
		break;
	case 3:
		ix = (people.x) / 32+1;
		iy = (people.y+5 ) / 32;
		break;
	}

	if (map[ix][iy] == BOOK)
	{
		bombplus++;

		map[ix][iy] = GRASS;
	}
	if (map[ix][iy] == BUBBLE)
	{
		maxBomb += 1;
		map[ix][iy] = GRASS;
	}
	if (map[ix][iy] == SHOE)
	{
		People *ptemp = new People;
		getPeople(ptemp);
		ptemp->speed += 2;
		map[ix][iy] = GRASS;
	}

}
void initItems()
{
	for (int i = 0; i < num_box; i++)
	{
		item[i] = 0;
	}
	int countit = 0;
	while(countit<10)
	{

		srand((unsigned)time(NULL));
		int book = rand() % num_box;
		if (item[book] == 0)
		{
			item[book] = BOOK;
			countit++;
		}
		int bubble = rand() % num_box;

		if (item[bubble] == 0)
		{
			item[bubble] = BUBBLE;
			countit++;
		}

		int shoe = rand() % num_box;

		if (item[shoe] == 0)
		{
			item[shoe] = SHOE;
			countit++;
		}
	}
	
}

void paintvic(HDC hdc)
{
	if (sec)
	{
		SelectObject(gvbgdc, vicbg2);
		BitBlt(hdc, 0, 0, 592, 602, gvbgdc, 0, 0, SRCCOPY);
	}
	else {
		SelectObject(gvbgdc, vicbg);
		BitBlt(hdc, 0, 0, 592, 602, gvbgdc, 0, 0, SRCCOPY);
	}

}
void initBox()
{
	boxlist.init();
	for(int i=0;i<18;i++)
		for (int j = 0; j < 18; j++)
		{
			if (map[i][j] == BOX)
			{
				Box b0;
				b0.x = i;
				b0.y = j;
				boxlist.append(b0);
			}
		}
}
void initBoxs()
{
	boxlists.init();
	for (int i = 0; i < 18; i++)
		for (int j = 0; j < 18; j++)
		{
			if (map[i][j] == BOX)
			{
				Box b0;
				b0.x = i;
				b0.y = j;
				boxlists.append(b0);
			}
		}
}
void paintbg(HDC hdc)
{
	if (sec)
	{
		SelectObject(gvbgdcs, gvbg);
		BitBlt(hdc, 0, 0, 592, 602, gvbgdcs, 0, 0, SRCCOPY);
	}
	else
	{
		SelectObject(gvbgdc, gvbg);
		BitBlt(hdc, 0, 0, 592, 602, gvbgdc, 0, 0, SRCCOPY);
	}

}
void gameOver(HDC hdc)
{
	int x = 30;
	int y = 50;
	SelectObject(gvdcbuf, gvn);
	BitBlt(hdc, x, y, 500, 339, gvdcbuf, 0, 0, SRCAND);
	SelectObject(gvdcbuf, gv);
	BitBlt(hdc, x, y, 500, 339, gvdcbuf, 0, 0, SRCPAINT);
}

void checkAlive(People *it)
{
	if (it->hp <= 0)
		it->isAlive = false;
}

bool getPeople(People*& it)
{
	*&it = &people;
	return true;
}
void doHurt(Bomb *b, LList<Ghost> ghostlist, LList<Box> boxlist,HDC hdc)
{
	for (int i = b->x_axis - 1; i <= b->x_axis + 1; i++)
		for (int j = b->y_axis - 1; j <= b->y_axis + 1; j++)
		{
			Ghost *gtemp = new Ghost;
			while (ghostlist.fence->next != ghostlist.tail)
			{
				ghostlist.getValue(gtemp);
				if (gtemp->x / 32 == i && gtemp->y / 32 == j)
				{
					gtemp->hp -= b->atk;
					paintHP(gtemp->hp*1.67, gtemp->x, gtemp->y, hdc);
					if (gtemp->hp <= 0)
					{
						Ghost *deltemp = new Ghost;
						map[i][j] = GRASS;
						ghostlist.remove(*deltemp);
						//delete deltemp;
					}
					break;
				}
				else
					ghostlist.next();
			}
			ghostlist.setStart();
		}
	for(int i= b->x_axis-1;i<= b->x_axis + 1;i++)
		for (int j = b->y_axis - 1; j <= b->y_axis + 1; j++)
		{
			if (!(i == b->x_axis&j == b->y_axis)&&!(i == b->x_axis-1&&j == b->y_axis-1) && !(i == b->x_axis + 1 && j == b->y_axis + 1)
				&& !(i == b->x_axis - 1 && j == b->y_axis + 1) && !(i == b->x_axis + 1 && j == b->y_axis - 1))
			{
				
				if (people.x/32 == i&&people.y/32==j)
				{
					People *p = new People;
					getPeople(p);
					p->hp -= b->atk;
					//p->hp -= 100;

				}
					
				else if (map[i][j] == BOX)
				{
					//写box struct
					Box *box = new Box;
					int cntbox = 0;
					while (boxlist.fence->next != boxlist.tail)
					{

						boxlist.getValue(box);
						for (int i = b->x_axis - 1; i <= b->x_axis + 1; i++)
						{
							for (int j = b->y_axis - 1; j <= b->y_axis + 1; j++)
							{
								if (!(i == b->x_axis&&i == b->y_axis))
								{
									if (box->x == i && box->y == j)
									{
										box->hp -= b->atk;
										paintHP(box->hp*1.67, box->x * 32, box->y * 32, hdc);
										if (box->hp <= 0)
										{
											Box *del = new Box;
											map[i][j] = GRASS;
											boxlist.remove(*del);
											if (item[cntbox] == BOOK)
												map[i][j] = BOOK;
											else if (item[cntbox] == SHOE)
												map[i][j] = SHOE;
											else if (item[cntbox] == BUBBLE)
												map[i][j] = BUBBLE;
										}
										break;
									}
								}

							}
						}
						boxlist.next();
						cntbox++;
					}
					boxlist.setStart();
				}
			}
			
		}
	
}
void doHurts(Bomb *b, HDC hdc)
{
	for (int i = b->x_axis - 1; i <= b->x_axis + 1; i++)
		for (int j = b->y_axis - 1; j <= b->y_axis + 1; j++)
		{
			Ghost *gtemp = new Ghost;
			while (ghostlists.fence->next != ghostlists.tail)
			{
				ghostlists.getValue(gtemp);
				if (gtemp->x / 32 == i && gtemp->y / 32 == j)
				{
					gtemp->hp -= b->atk;
					paintHP(gtemp->hp*1.67, gtemp->x, gtemp->y, hdc);
					if (gtemp->hp <= 0)
					{
						Ghost *deltemp = new Ghost;
						map[i][j] = GRASS;
						ghostlists.remove(*deltemp);
						//delete deltemp;
					}
					break;
				}
				else
					ghostlists.next();
			}
			ghostlists.setStart();
		}
	for (int i = b->x_axis - 1; i <= b->x_axis + 1; i++)
		for (int j = b->y_axis - 1; j <= b->y_axis + 1; j++)
		{
			if (!(i == b->x_axis&j == b->y_axis) && !(i == b->x_axis - 1 && j == b->y_axis - 1) && !(i == b->x_axis + 1 && j == b->y_axis + 1)
				&& !(i == b->x_axis - 1 && j == b->y_axis + 1) && !(i == b->x_axis + 1 && j == b->y_axis - 1))
			{

				if (people.x / 32 == i && people.y / 32 == j)
				{
					People *p = new People;
					getPeople(p);
					p->hp -= b->atk;

				}

				else if (map[i][j] == BOX)
				{
					//写box struct
					Box *box = new Box;
					int cntbox = 0;
					while (boxlists.fence->next != boxlists.tail)
					{

						boxlists.getValue(box);
						for (int i = b->x_axis - 1; i <= b->x_axis + 1; i++)
						{
							for (int j = b->y_axis - 1; j <= b->y_axis + 1; j++)
							{
								if (!(i == b->x_axis&&i == b->y_axis))
								{
									if (box->x == i && box->y == j)
									{
										box->hp -= b->atk;
										paintHP(box->hp*1.67, box->x * 32, box->y * 32, hdc);
										if (box->hp <= 0)
										{
											Box *del = new Box;
											map[i][j] = GRASS;
											boxlists.remove(*del);
											if (item[cntbox] == BOOK)
												map[i][j] = BOOK;
											else if (item[cntbox] == SHOE)
												map[i][j] = SHOE;
											else if (item[cntbox] == BUBBLE)
												map[i][j] = BUBBLE;
										}
										break;
									}
								}

							}
						}
						boxlists.next();
						cntbox++;
					}
					boxlists.setStart();
				}
			}

		}

}
void changeValue(Bomb *&b)
{
	b->loop += 1;
}

//这里用了引用传递对象，所以数据成员的值可以被修改
bool canPutBomb(Bomb *b)
{
	int x, y;
	//检测是否能放置炸弹
	//不能的情况：不是草
	if ((bomblist.leftcnt + bomblist.rightcnt) == maxBomb)
		return false;
	switch (people.dir)
	{
		//人向上，炸弹放在人的上方,暂时不考虑为石头的情形和边界情形，稍后再做检测
	case 0:
		x = ((people.x+5) / 32);
		y = ((people.y+15) / 32) - 1;
		break;
		//人向下
	case 1:
		x = ((people.x + 5) / 32);
		y = ((people.y - 8) / 32) + 1;
		break;
		//人向左
	case 2:
		x = ((people.x+20) / 32) - 1;
		y = ((people.y +4) / 32);
		break;
		//人向右
	case 3:
		x = ((people.x ) / 32) + 1;
		y = ((people.y + 4) / 32);
		break;
	}
	if (map[x][y] != GRASS)
		return false;
	else
	{
		b->x_axis = x;
		b->y_axis = y;
		b->x = x * 32;
		b->y = y * 32;
		return true;
	}
	
}

void paintBomb(HDC hdc, HDC bombdc,HDC mdc, Bomb b)
{
	int w, h;
	w = h = 23;
	//分阶段绘制
	int src_start_x =0;
	int src_start_y=0;
	//阶段1
	b.tN = GetTickCount();
	//if ((b.tN-b.tP) < 200)
	if (b.loop < 16)
	{
		if ((b.loop) < 5)
		{
			src_start_x = src_start_y = 0;
		}
		//阶段2

		//else if ((b.tN - b.tP) > 200 && (b.tN - b.tP) < 400)
		else if (b.loop >= 5 && b.loop < 10)
		{
			src_start_x = 24;
			src_start_y = 0;
		}
		//阶段3
		else if (b.loop >= 10 && b.loop < 15)
		{
			src_start_x = 48;
			src_start_y = 0;
		}
		//阶段4
		else if (b.loop >= 15 && b.loop < 20)
		{
			src_start_x = 72;
			src_start_y = 0;
		}
		if (sec)
		{
			SelectObject(bombdcs, bombn);
			BitBlt(mdcs, b.x, b.y, w, h, bombdcs, src_start_x, src_start_y, SRCAND);
			SelectObject(bombdcs, bombs);
			BitBlt(mdcs, b.x, b.y, w, h, bombdcs, src_start_x, src_start_y, SRCPAINT);
		}
		else {
			SelectObject(bombdc, bombn);
			BitBlt(mdc, b.x, b.y, w, h, bombdc, src_start_x, src_start_y, SRCAND);
			SelectObject(bombdc, bomb);
			BitBlt(mdc, b.x, b.y, w, h, bombdc, src_start_x, src_start_y, SRCPAINT);
		}

		BitBlt(hdc, b.x, b.y, w, h, mdc, b.x, b.y, SRCCOPY);
	}

}
//这样做不能改变people的x和y值
void initPeople(People p)
{
	srand((unsigned)time(NULL));
	while (true)
	{
		int x = (rand() % 500) / 32;
		int y = (rand() % 500) / 32;
		if (map[x][y] == GRASS)
		{
			p.setx(x*32);
			p.sety(y*32);
			break;
		}
	}
}

void paintGhost(HDC hdc,Ghost g,HDC mdc,HDC ghostdcn, HDC ghostdc)
{
	int w, h;
	w = h = 32;
	switch (g.type)
	{
		//蜘蛛
	case 0:
		//把人物图按现在的坐标贴到mdc上，同时消除背景
		SelectObject(ghostdcn, ghostn[g.dir]);
		BitBlt(mdc, g.x, g.y, w, h, ghostdcn, ghostcnt[g.sec]*w, 0, SRCAND);
		SelectObject(ghostdc, ghost[g.dir]);
		BitBlt(mdc, g.x, g.y, w, h, ghostdc, ghostcnt[g.sec]*w, 0, SRCPAINT);
		//把mdc上的人粘贴到hdc上
		BitBlt(hdc, g.x, g.y, w, h, mdc, g.x, g.y, SRCCOPY);
		ghostcnt[g.sec]++;
		//判断是否已经完成一轮动作，若完成，则从头开始动
		if (ghostcnt[g.sec] == 4)
		{
			ghostcnt[g.sec] = 0;

		}
		break;
		//狗
	case 1:
		SelectObject(ghostdcn, dogn[g.dir]);
		BitBlt(mdc, g.x, g.y, w, h, ghostdcn, ghostcnt[g.sec]*w, 0, SRCAND);
		SelectObject(ghostdc, dog[g.dir]);
		BitBlt(mdc, g.x, g.y, w, h, ghostdc, ghostcnt[g.sec]*w, 0, SRCPAINT);
		//把mdc上的人粘贴到hdc上
		BitBlt(hdc, g.x, g.y, w, h, mdc, g.x, g.y, SRCCOPY);
		ghostcnt[g.sec]++;
		//判断是否已经完成一轮动作，若完成，则从头开始动
		if (ghostcnt[g.sec] == 4)
		{
			ghostcnt[g.sec] = 0;

		}
		break;
		//狼
	case 2:
		if (sec)
		{
			SelectObject(ghostdcn, monsterns[g.dir]);
			BitBlt(mdc, g.x, g.y, w, h, ghostdcn, ghostcnt[g.sec] * w, 0, SRCAND);
			SelectObject(ghostdc, monsters[g.dir]);
			BitBlt(mdc, g.x, g.y, w, h, ghostdc, ghostcnt[g.sec] * w, 0, SRCPAINT);
		}
		else
		{
			SelectObject(ghostdcn, monstern[g.dir]);
			BitBlt(mdc, g.x, g.y, w, h, ghostdcn, ghostcnt[g.sec] * w, 0, SRCAND);
			SelectObject(ghostdc, monster[g.dir]);
			BitBlt(mdc, g.x, g.y, w, h, ghostdc, ghostcnt[g.sec] * w, 0, SRCPAINT);
		}
		
		//把mdc上的人粘贴到hdc上
		BitBlt(hdc, g.x, g.y, w, h, mdc, g.x, g.y, SRCCOPY);
		ghostcnt[g.sec]++;
		//判断是否已经完成一轮动作，若完成，则从头开始动
		if (ghostcnt[g.sec] == 4)
		{
			ghostcnt[g.sec] = 0;

		}
		break;
	}
	


}
//freq参数指生成ghost的频率，现在暂时没有用，设成0
void generateGhost(int freq)
{
	int count = 0;
	int gnum=deg*3;
	//int gnum = deg ;
	srand((unsigned)time(NULL));
	while(count< gnum)
	{
		int x = (rand() % 500)/32;
		int y= (rand() % 500) /32;
		if (map[x][y] == GRASS)
		{
			Ghost ghost(600, x * 32, y * 32, 100, 0, ghost_speed,0,count);
			ghost.x_axis = x;
			ghost.y_axis = y;
			map[x][y] = GHOSTC;
			ghostlist.append(ghost);
			
			paintGhost(hdc, ghost, mdc,ghostdcn, ghostdc);
			count++;
		}
		
	}
	count = 0;
	while (count < gnum)
	{
		int x = (rand() % 500) / 32;
		int y = (rand() % 500) / 32;
		if (map[x][y] == GRASS)
		{
			Ghost ghost(200, x * 32, y * 32, 60, 0, ghost_speed,1,gnum+count);
			ghost.x_axis = x;
			ghost.y_axis = y;
			map[x][y] = GHOSTC;
			ghostlist.append(ghost);

			paintGhost(hdc, ghost, mdc, ghostdcn, ghostdc);
			count++;
		}

	}
	count = 0;
	while (count < gnum+1)
	{
		int x = (rand() % 500) / 32;
		int y = (rand() % 500) / 32;
		if (map[x][y] == GRASS)
		{
			Ghost ghost(400, x * 32, y * 32, 80, 0, ghost_speed, 2, gnum*2 + count);
			ghost.x_axis = x;
			ghost.y_axis = y;
			map[x][y] = GHOSTC;
			ghostlist.append(ghost);

			paintGhost(hdc, ghost, mdc, ghostdcn, ghostdc);
			count++;
		}

	}
}
void generateGhosts(int freq)
{
	int count = 0;
	int gnum = deg * 3;
	srand((unsigned)time(NULL));
	while (count < gnum)
	{
		int x = (rand() % 500) / 32;
		int y = (rand() % 500) / 32;
		if (map[x][y] == GRASS)
		{
			Ghost ghost(600, x * 32, y * 32, 100, 0, ghost_speed, 0, count);
			ghost.x_axis = x;
			ghost.y_axis = y;
			map[x][y] = GHOSTC;
			ghostlists.append(ghost);

			paintGhost(sdc, ghost, mdcs, ghostdcns, ghostdcs);
			count++;
		}

	}
	count = 0;
	while (count < gnum)
	{
		int x = (rand() % 500) / 32;
		int y = (rand() % 500) / 32;
		if (map[x][y] == GRASS)
		{
			Ghost ghost(200, x * 32, y * 32, 60, 0, ghost_speed, 1, gnum + count);
			ghost.x_axis = x;
			ghost.y_axis = y;
			map[x][y] = GHOSTC;
			ghostlists.append(ghost);

			paintGhost(sdc, ghost, mdcs, ghostdcns, ghostdcs);
			count++;
		}

	}
	count = 0;
	while (count < gnum)
	{
		int x = (rand() % 500) / 32;
		int y = (rand() % 500) / 32;
		if (map[x][y] == GRASS)
		{
			Ghost ghost(400, x * 32, y * 32, 80, 0, ghost_speed, 2, gnum * 2 + count);
			ghost.x_axis = x;
			ghost.y_axis = y;
			map[x][y] = GHOSTC;
			ghostlists.append(ghost);

			paintGhost(sdc, ghost, mdcs, ghostdcns, ghostdcs);
			count++;
		}

	}
}
bool checkCollision(int x, int y, int targetdir,int speed)
{
	//碰撞检测
	//当人走到地图上map[i][j]==STONE时，不能继续走，返回原位置
	//每次检测遍历人周围的所有石头？
	int w, h;
	w = h = 32;
	//选择图片大小

	//(1)计算人所在的坐标上下左右的地块是否是stone，是则表明有collision，返回true
	switch (targetdir)
	{
	case 0:
		if ((map[(x + 6) / 32][(y + 5) / 32] != GRASS&& map[(x + 6) / 32][(y + 5) / 32] != TRAP 
			&& map[(x + 6) / 32][(y + 5) / 32] !=FOOD && map[(x + 6) / 32][(y + 5) / 32] != GHOSTC)
			|| (map[(x + w - 6) / 32][(y + 5) / 32] != GRASS&&map[(x + w - 6) / 32][(y + 5) / 32] !=TRAP
				&& map[(x + w - 6) / 32][(y + 5) / 32] != FOOD && map[(x +w- 6) / 32][(y + 5) / 32] != GHOSTC))
		{
			//return false;
			return true;
		}
		else
			return false;
		break;
	case 1:
		if ((map[(x + 6) / 32][(y + h -4) / 32] != GRASS && map[(x + 6) / 32][(y + h -4) / 32] != TRAP
			&&map[(x +  6) / 32][(y +h-4) / 32] != FOOD && map[(x + 6) / 32][(y +h-4) / 32] != GHOSTC)
			|| (map[(x + w - 6) / 32][(y + h -4) / 32] != GRASS&& map[(x + w - 6) / 32][(y + h -4) / 32] != TRAP
				&& map[(x +w- 6) / 32][(y + h -4) / 32] != FOOD && map[(x + w-6) / 32][(y +h-4) / 32] != GHOSTC))
		{
			//return false;
			return true;
		}
		else
			return false;
		break;
	case 2:
		if ((map[(x + 4) / 32][(y + 7) / 32] != GRASS&& map[(x + 3) / 32][(y + 7) / 32] != TRAP
			&& map[(x + 4) / 32][(y + 7) / 32] != FOOD && map[(x + 3) / 32][(y + 7) / 32] != GHOSTC)
			|| (map[(x + 4) / 32][(y + h - 7) / 32] != GRASS&& map[(x + 3) / 32][(y + h - 7) / 32] != TRAP
				&& map[(x + 4) / 32][(y + h - 7) / 32] != FOOD && map[(x + 3) / 32][(y +h- 7) / 32] != GHOSTC))
		{
			//return false;
			return true;
		}
		else
			return false;
		break;
	case 3:
		if ((map[(x + w - 5) / 32][(y + 7) / 32] != GRASS&& map[(x + w - 5) / 32][(y + 7) / 32] !=TRAP
			&& map[(x + w-5) / 32][(y + 7) / 32] != FOOD&&map[(x + w - 5) / 32][(y + 7) / 32] !=GHOSTC )
			|| (map[(x + w - 5) / 32][(y + h - 7) / 32] != GRASS&& map[(x + w - 5) / 32][(y + h - 7) / 32] !=TRAP 
				&& map[(x + w-5) / 32][(y +h- 7) / 32] != FOOD&& map[(x + w - 5) / 32][(y +h- 7) / 32] !=GHOSTC))
		{
			//return false;
			return true;
		}
		else
			return false;
		break;

}
	//否则返回false
		return false;
}

void paintMap(HDC hdc,HDC mdc)
{
	//重绘地图
	for (int i = 0; i<row; i++)
		for (int j = 0; j< col; j++)
		{

			if (map[i][j] == BOX)
			{
				SelectObject(bufdc, box);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc,  192,64, SRCCOPY);
			}
			else if (map[i][j] == BIRTH ||map[i][j] == STONE || map[i][j] == GRASS|| map[i][j] == HOUSE
				|| map[i][j] == GHOSTC|| map[i][j] == BOMBC || map[i][j] == BOOK
				|| map[i][j] == BUBBLE || map[i][j] == SHOE || map[i][j] == TRAP || map[i][j] == FOOD)
			{
				
				SelectObject(bufdc, base);
				if (map[i][j] == HOUSE || map[i][j] == GHOSTC || map[i][j] == BOMBC || map[i][j] == BOOK
					|| map[i][j] == BUBBLE || map[i][j] == SHOE || map[i][j] == TRAP || map[i][j] == FOOD || map[i][j] == BIRTH)
				{
					BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, GRASS * 32, 0, SRCCOPY);

				}
				else {

					BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, (map[i][j]) * 32, 0, SRCCOPY);
				}
					
			}
			if (map[i][j] == TRAP)
			{

				SelectObject(bufdc, trapn);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 32, 0, SRCAND);
				SelectObject(bufdc, trap);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 32, 0, SRCPAINT);

			}
			if (map[i][j] == FOOD)
			{

				SelectObject(bufdc, foodn);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCAND);
				SelectObject(bufdc, food);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCPAINT);

			}
			if (map[i][j] == HOUSE)
			{
				if (sec)
				{
					SelectObject(bufdc, housen);
					BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCAND);
					SelectObject(bufdc, house);
					BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCPAINT);
				}
				else
				{
					SelectObject(bufdc, lflowern);
					BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCAND);
					SelectObject(bufdc, lflower);
					BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCPAINT);
				}

			}
			if (map[i][j] == BOOK)
			{
				//paintbook
				SelectObject(bufdc, bookbmp);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCCOPY);

			}
			if (map[i][j] == BUBBLE)
			{
				//paint bubble
				
				SelectObject(bufdc, bubblen);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCAND);
				SelectObject(bufdc, bubblebmp);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCPAINT);

			}
			if (map[i][j] == SHOE)
			{
				
				SelectObject(bufdc, shoen);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCAND);
				SelectObject(bufdc, shoebmp);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCPAINT);

			}

			if (map[i][j] == TR0)
			{
				SelectObject(bufdc, tree0);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCCOPY);
			}
			if (map[i][j] == FLW0)
			{
				SelectObject(bufdc, flower0);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCCOPY);
			}
			if (map[i][j] == FLW1)
			{
				SelectObject(bufdc, flower1);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCCOPY);
			}
			if (map[i][j] == FLW2)
			{
				SelectObject(bufdc, flower2);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCCOPY);
			}
			if (map[i][j] == FLW3)
			{
				SelectObject(bufdc, flower3);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCCOPY);
			}
			if (map[i][j] == STN0)
			{
				SelectObject(bufdc, stone0);
				BitBlt(mdc, 32 * i, 32 * j, 32, 32, bufdc, 0, 0, SRCCOPY);
			}
		}

	//将fullmap存到mdc中
	SelectObject(mdc, fullmap);

	BitBlt(hdc, 0, 0, 592, 602, mdc, 0, 0, SRCCOPY);
	
}
//人物走动
void paintWalk(HDC hdc,HDC mdc,HDC bufdc_n,HDC bufdc_walk)
{//把人物走动的图片保存到bufdc_walk dc上
	
	int w, h;
	w = h = 32;
	//把人物图按现在的坐标贴到mdc上，同时消除背景
	//（这种方法只有背景为白色才能用，transparentblt也可以实现）
	SelectObject(bufdc_n, girln[people.dir]);
	BitBlt(mdc, people.x, people.y, w, h, bufdc_n, num*w, 0, SRCAND);
	SelectObject(bufdc_walk, girl[people.dir]);
	BitBlt(mdc, people.x, people.y, w, h, bufdc_walk, num*w, 0, SRCPAINT);
	//把mdc上的人粘贴到hdc上
	BitBlt(hdc, people.x, people.y, w, h, mdc, people.x, people.y, SRCCOPY);
	tPre = GetTickCount();
	num++;
	//判断是否已经完成一轮动作，若完成，则从头开始动
	if (num == 3)
		num = 0;
	
}
void paintWalks()
{//把人物走动的图片保存到bufdc_walk dc上

	int w, h;
	w = h = 32;
	if(people.dir == 0)
	{
		
			SelectObject(bufdc_ns,walkn0);
			BitBlt(mdcs, people.x, people.y, w, h, bufdc_ns, num*w, 0, SRCAND);
			SelectObject(bufdc_walks, walk0);
			BitBlt(mdcs, people.x, people.y, w, h, bufdc_walks, num*w, 0, SRCPAINT);
			//把mdc上的人粘贴到hdc上
			BitBlt(sdc, people.x, people.y, w, h, mdcs, people.x, people.y, SRCCOPY);
		
	}
	else if (people.dir == 1)
	{
		SelectObject(bufdc_ns, walkn1);
		BitBlt(mdcs, people.x, people.y, w, h, bufdc_ns, num*w, 0, SRCAND);
		SelectObject(bufdc_walks, walk1);
		BitBlt(mdcs, people.x, people.y, w, h, bufdc_walks, num*w, 0, SRCPAINT);
		//把mdc上的人粘贴到hdc上
		BitBlt(sdc, people.x, people.y, w, h, mdcs, people.x, people.y, SRCCOPY);
	}
	else if (people.dir == 2)
	{
		SelectObject(bufdc_ns, walkn2);
		BitBlt(mdcs, people.x, people.y, w, h, bufdc_ns, num*w, 0, SRCAND);
		SelectObject(bufdc_walks, walk2);
		BitBlt(mdcs, people.x, people.y, w, h, bufdc_walks, num*w, 0, SRCPAINT);
		//把mdc上的人粘贴到hdc上
		BitBlt(sdc, people.x, people.y, w, h, mdcs, people.x, people.y, SRCCOPY);
	}
	else if(people.dir == 3)
	{
		SelectObject(bufdc_ns, walkn3);
		BitBlt(mdcs, people.x, people.y, w, h, bufdc_ns, num*w, 0, SRCAND);
		SelectObject(bufdc_walks, walk3);
		BitBlt(mdcs, people.x, people.y, w, h, bufdc_walks, num*w, 0, SRCPAINT);
		//把mdc上的人粘贴到hdc上
		BitBlt(sdc, people.x, people.y, w, h, mdcs, people.x, people.y, SRCCOPY);
	}
	tPre = GetTickCount();
	num++;
	//判断是否已经完成一轮动作，若完成，则从头开始动
	if (num == 3)
		num = 0;

}
void generateMap()
{
	//生成随机地图
	//为地图数组赋值
	int cnttr0 = 0;
	int cntflw0 = 0;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			if (map[i][j] == -1)
			{
				
				int temp = rand() % 6;
				if (temp == 0&&cnttr0<10)
				{
					map[i][j] = TR0;
					cnttr0++;
				}
				else if (temp == 1 && cntflw0 < 10)
				{
					map[i][j] = FLW0;
					cntflw0++;
				}
				else if (temp == 4 && num_box < 8)
				{
					map[i][j] =BOX;
					num_box++;
				}
				else
					map[i][j] = STONE;
			}
		}
	}
	srand((unsigned)time(NULL));
	for (int i = 9; i < 18; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			if (map[i][j] == -1)
			{

				int temp = rand() % 6;
				if (temp == 0 && cnttr0 < 10)
				{
					map[i][j] = TR0;
					cnttr0++;
				}
				else if (temp == 1 && cntflw0 < 10)
				{
					map[i][j] = FLW0;
					cntflw0++;
				}
				else if (temp == 4 && num_box < 17)
				{
					map[i][j] = BOX;
					num_box++;
				}
				else
					map[i][j] = STONE;
			}
		}
	}
	num_box += 8;
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TOMBRAIDER1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TOMBRAIDER1));

    MSG msg;

    // 主消息循环: 
	ZeroMemory(&msg, sizeof(msg));   //这句特别重要，因为需要将msg初始化后才不会引起编译异常、运行异常 
	
	
		

		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			//每60ms刷新一次，进行重绘
			{
			tNow = GetTickCount();

			if (tNow - tPre >= 60)
			{
				//调试需要：直接胜利第一关
				bool vic = false;
				
				//bool vic = true;
				if ((((people.x+23) / 32 == 8 - 1 && (people.y+12) / 32 == 9) ||
					((people.x+20 ) / 32 == 8 + 1 && (people.y+10) / 32 == 9) ||
					((people.x +10) / 32 == 8 && (people.y + 10) / 32 == 9-1) ||
					((people.x +10) / 32 == 8  && (people.y + 22) / 32 == 9+ 1)
					))
				{
					countvic++;
					paintvic(hdc);
					dopaint = false;
					if (countvic == 3000)
					{
						vic = true;
					}
				}
				if (sec)
				{
					if ((((people.x + 4) / 32 == 16 - 1 && (people.y + 4) / 32 == 15) ||
						((people.x + 4) / 32 == 16 + 1 && (people.y + 4) / 32 == 15) ||
						((people.x - 2) / 32 == 16 && (people.y + 4) / 32 == 15 - 1) ||
						((people.x - 2) / 32 == 16 && (people.y + 4) / 32 == 15 + 1)
						))
					{
						//胜利
						
						paintvic(sdc);
						secvic = true;
					}
					if (people.hp <= 0&&!secvic)
					{
						paintbg(sdc);
					}
					else if(!secvic) {
						if (checkTrap())
						{
							traptime[countTrap][0] = 1;
							People *ttemp = new People;
							getPeople(ttemp);
							if (ttemp->speed - 6 > 0)
								ttemp->speed -= 6;
							//若碰到trap，trap将开始计时
							countTrap += 1;

						}
						if (checkFood())
						{
							People *p = new People;
							getPeople(p);
							p->hp += 200;
							if (p->hp > 1000)
								p->hp = 1000;
						}
						for (int i = 0; i <= countTrap; i++)
						{
							if (traptime[i][0] == 1)
							{
								traptime[i][1]++;
								if (traptime[i][1] == 120)
								{
									People *spdtemp = new People;
									getPeople(spdtemp);
									spdtemp->speed += 6;
								}
							}
						}
						paintMap(sdc, mdcs);
						paintWalks();
						Ghost *it = new Ghost;
						People *htemp = new People;
						getPeople(htemp);
						while (ghostlists.fence->next != ghostlists.tail)
						{

							ghostlists.getValue(it);
							gHurtP(it, htemp);
							//delete it;
							Ghost *it = new Ghost;
							ghostlists.getValue(it);
							bool decision = false;
							int dis = sqrt((it->x - people.x)*(it->x - people.x) + (it->y - people.y)*(it->y - people.y));
							int cntBomb = 0;
							bool haveP = false;
							if (dis >= 200)
							{
								if (it->countDecision == 0)
								{
									srand((unsigned)time(NULL));
									it->tempDir = (rand() + countGhost * 10) % 4;
									it->dir = it->tempDir;
								}

								if (it->countDecision < 20)
								{
									it->countDecision++;
									if (map[it->x / 32][it->y / 32] == GHOSTC)
										map[it->x / 32][it->y / 32] = GRASS;
									switch (it->tempDir)
									{
									case 0:
										if (it->y > 10 && !checkGCollision(it->x, it->y, 0, 32 * ghost_speed))
										{
											it->y = (int)((double)it->y - 32 * ghost_speed);


										}
										break;
									case 1:
										if (it->y < 592 && !checkGCollision(it->x, it->y, 1, 32 * ghost_speed))
										{
											it->y = (int)((double)it->y + 32 * ghost_speed);
										}
										break;
									case 2:
										if (it->x > 10 && !checkGCollision(it->x, it->y, 2, 32 * ghost_speed))
										{
											it->x = (int)((double)it->x - 32 * ghost_speed);
										}
										break;
									case 3:
										if (it->x < 602 && !checkGCollision(it->x, it->y, 3, 32 * ghost_speed))
										{
											it->x = (int)((double)it->x + 32 * ghost_speed);
										}
										break;
									}
									if (map[it->x / 32][it->y / 32] == GRASS)
										map[((it->x) / 32)][((it->y) / 32)] = GHOSTC;
								}
								else if (it->countDecision == 20)
								{
									it->countDecision = 0;

								}

							}
							else
							{
								double value = 0;

								for (int i = (it->x / 32) - 1; i <= (it->x / 32) + 1; i++)
									for (int j = (it->y / 32) - 1; j <= (it->y / 32) + 1; j++)
									{
										if (i >= 0 && i < 18 && j >= 0 && j < 18)
										{
											if (map[i][j] == BOMBC)
											{
												cntBomb++;
											}
											if ((people.x / 32 == i) && (people.y / 32 == j))
											{
												haveP = true;
											}
										}
									}

								value = -100 * cntBomb*0.5 + it->atk * 10 * 1.2;
								//伤害他人更多，a*
								if (value > 0)
									decision = true;
								//逃跑
								else
								{
									if (it->countDecision == 0)
									{
										srand((unsigned)time(NULL));
										it->tempDir = (rand() + countGhost * 10) % 4;
										it->dir = it->tempDir;
									}
									if (it->countDecision < 60)
									{
										if (map[it->x / 32][it->y / 32] == GHOSTC)
											map[it->x / 32][it->y / 32] = GRASS;
										switch (it->tempDir)
										{
										case 0:
											if (it->y > 10 && !checkGCollision(it->x, it->y, 0, 32 * ghost_speed))
											{
												it->y -= 32 * ghost_speed;
											}
											break;
										case 1:
											if (it->y < 592 && !checkGCollision(it->x, it->y, 1, 32 * ghost_speed))
											{
												it->y += 32 * ghost_speed;
											}
											break;
										case 2:
											if (it->x > 10 && !checkGCollision(it->x, it->y, 2, 32 * ghost_speed))
											{
												it->x -= 32 * ghost_speed;
											}
											break;
										case 3:
											if (it->x < 602 && !checkGCollision(it->x, it->y, 3, 32 * ghost_speed))
											{
												it->x += 32 * ghost_speed;

											}
											break;
										}
										if (map[it->x / 32][it->y / 32] == GRASS)
											map[((it->x) / 32)][((it->y) / 32)] = GHOSTC;
										it->countDecision++;
									}
									else if (it->countDecision == 60)
									{

										it->countDecision = 0;

									}
									false;
								}

							}
							if (decision)
							{
								
								if (map[it->x / 32][it->y / 32] == GHOSTC)
									map[it->x / 32][it->y / 32] = GRASS;

								switch (path_finding(*it, people))
								{
								case 0:
									if (it->y > 10 && !checkGCollision(it->x, it->y, 0, 32 * ghost_speed))
									{
										it->dir = 0;
										it->y = int((double)it->y - 32 * ghost_speed);

									}
									break;
								case 1:
									if (it->y < 562 && !checkGCollision(it->x, it->y, 1, 32 * ghost_speed))
									{
										it->dir = 1;
										it->y = int((double)it->y + 32 * ghost_speed);
									}
									break;
								case 2:
									if (it->x > 10 && !checkGCollision(it->x, it->y, 2, 32 * ghost_speed))
									{
										it->dir = 2;
										it->x = int((double)it->x - 32 * ghost_speed);
									}
									break;
								case 3:
									if (it->x < 592 && !checkGCollision(it->x, it->y, 3, 32 * ghost_speed))
									{
										it->dir = 3;
										it->x = int((double)it->x + 32 * ghost_speed);

									}
									break;
								}
								if (map[it->x / 32][it->y / 32] == GRASS)
									map[((it->x) / 32)][((it->y) / 32)] = GHOSTC;
							}/**/
							countGhost++;
							paintGhost(sdc, *it, mdcs, ghostdcns, ghostdcs);
							ghostlists.next();
						}
						ghostlists.setStart();
						countGhost = 0;

						//绘制炸弹
						Bomb *items = new Bomb;
						bomblists.setStart();

						if ((bomblists.leftcnt + bomblists.rightcnt) > 0) {
							while (bomblists.fence != bomblists.tail)
							{
								bool flag = false;
								bomblists.getValue(items);
								items->tN = GetTickCount();
								changeValue(items);

								if (items->loop < 20)
								{

									paintBomb(sdc,bombdcs,mdcs, *items);
								}
								else
								{
									doHurts(items,sdc);
									flag = true;
									countatk++;
									map[items->x_axis][items->y_axis] = GRASS;
									Bomb *btemp = new Bomb;
									bomblists.remove(*btemp);
								}

								bomblists.next();
							}


						}paintHP(people.hp, people.x, people.y, sdc);
					}

				}
				if (vic)
				{
					//重置
					//重新生成dc
					sec = true;
					
					ghostlists.init();
					bomblists.init();
					countGhost = 0;
					countatk = 0;
					countHurt = 0;
					countTrap = 0;
					num = 0;
					num_box = 0;
					swnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
					sdc = GetDC(swnd);
					mdcs = CreateCompatibleDC(sdc);
					bufdcs = CreateCompatibleDC(sdc);
					bufdc_walks = CreateCompatibleDC(sdc);
					bufdc_ns = CreateCompatibleDC(sdc);
					ghostdcs = CreateCompatibleDC(sdc);
					ghostdcns = CreateCompatibleDC(sdc);
					bombdcs = CreateCompatibleDC(sdc);
					gvbgdcs= CreateCompatibleDC(sdc);
					People *p = new People;
					getPeople(p);
					p->x=20;
					p->dir = 0;
					ShowWindow(hwnd, SW_HIDE);
					MoveWindow(swnd, 250, 35, 592, 602, true);
					ShowWindow(swnd, nCmdShow);
					UpdateWindow(swnd);
					for (int i = 0; i < 5; i++)
						traptime[i][0] = traptime[i][1] = 0;
					//-----------初始化
					fullmap = CreateCompatibleBitmap(sdc, 592, 602);
					for (int i = 0; i < 18; i++)
						for (int j = 0; j < 18; j++)
							map[i][j] = mapcopy[i][j];
				
					generateMap();
					SelectObject(mdcs, fullmap);
					generateGhosts(0);
					paintMap(sdc,mdcs);
					//initPeople(people);
					srand((unsigned)time(NULL));
					people.setx(0);
					people.sety(0);
					paintWalk(sdc, mdcs, bufdc_ns, bufdc_walks);
					initBoxs();

					initItems();

					vic = false;
				}
				else if(!sec&&dopaint&&haveGhost)
				{
					if (people.hp <= 0)
					{
						paintbg(hdc);

					}
					else
					{
						//gameOver(hdc);
						paintMap(hdc,mdc);
						//检测人是否碰到trap
						if (checkTrap())
						{
							traptime[countTrap][0] = 1;
							People *ttemp = new People;
							getPeople(ttemp);
							if (ttemp->speed - 6 > 0)
								ttemp->speed -= 6;
							//若碰到trap，trap将开始计时
							countTrap += 1;
							
						}
						if (checkFood())
						{
							People *p = new People;
							getPeople(p);
							p->hp += 200;
							if (p->hp > 1000)
								p->hp = 1000;
						}
						for (int i = 0; i <= countTrap; i++)
						{
							if (traptime[i][0] == 1)
							{
								traptime[i][1]++;
								if (traptime[i][1] == 120)
								{
									People *spdtemp = new People;
									getPeople(spdtemp);
									spdtemp->speed += 6;
								}
							}
						}
						paintWalk(hdc,  mdc, bufdc_n, bufdc_walk);
						
	
						//绘制妖怪
						if (haveGhost)
						{
							Ghost *it = new Ghost;
							People *htemp = new People;
							getPeople(htemp);
							while (ghostlist.fence->next != ghostlist.tail)
							{

								ghostlist.getValue(it);
								gHurtP(it, htemp);
								//delete it;
								Ghost *it = new Ghost;
								ghostlist.getValue(it);
								bool decision = false;
								int dis = sqrt((it->x - people.x)*(it->x - people.x) + (it->y - people.y)*(it->y - people.y));
								int cntBomb = 0;
								bool haveP = false;
								if (dis >= 200)
								{
									if (it->countDecision == 0)
									{
										srand((unsigned)time(NULL));
										it->tempDir = (rand() + countGhost * 10) % 4;
										it->dir = it->tempDir;
									}

									if (it->countDecision < 20)
									{
										it->countDecision++;
										if (map[it->x / 32][it->y / 32] == GHOSTC)
											map[it->x / 32][it->y / 32] = GRASS;
										switch (it->tempDir)
										{
										case 0:
											if (it->y > 10 && !checkGCollision(it->x, it->y, 0, 32 * ghost_speed))
											{
												it->y = (int)((double)it->y - 32 * ghost_speed);


											}
											break;
										case 1:
											if (it->y < 592 && !checkGCollision(it->x, it->y, 1, 32 * ghost_speed))
											{
												
												it->y = (int)((double)it->y + 32 * ghost_speed);
											}
											break;
										case 2:
											if (it->x > 10 && !checkGCollision(it->x, it->y, 2, 32 * ghost_speed))
											{
												it->x = (int)((double)it->x - 32 * ghost_speed);
											}
											break;
										case 3:
											if (it->x < 602 && !checkGCollision(it->x, it->y, 3, 32 * ghost_speed))
											{
												it->x = (int)((double)it->x + 32 * ghost_speed);
											}
											break;
										}
										if (map[it->x / 32][it->y / 32] == GRASS)
											map[((it->x) / 32)][((it->y) / 32)] = GHOSTC;
									}
									else if (it->countDecision == 20)
									{
										it->countDecision = 0;

									}

								}
								else
								{
									double value = 0;

									for (int i = (it->x / 32) - 1; i <= (it->x / 32) + 1; i++)
										for (int j = (it->y / 32) - 1; j <= (it->y / 32) + 1; j++)
										{
											if (i >= 0 && i < 18 && j >= 0 && j < 18)
											{
												if (map[i][j] == BOMBC)
												{
													cntBomb++;
												}
												if ((people.x / 32 == i) && (people.y / 32 == j))
												{
													haveP = true;
												}
											}
										}

									value = -100 * cntBomb*0.5 + it->atk * 10 * 1.2;
									//伤害他人更多，a*
									if (value > 0)
										decision = true;
									//逃跑
									else
									{
										if (it->countDecision == 0)
										{
											srand((unsigned)time(NULL));
											it->tempDir = (rand() + countGhost * 10) % 4;
											it->dir = it->tempDir;
										}
										if (it->countDecision < 60)
										{
											if (map[it->x / 32][it->y / 32] == GHOSTC)
												map[it->x / 32][it->y / 32] = GRASS;
											switch (it->tempDir)
											{
											case 0:
												if (it->y > 10 && !checkGCollision(it->x, it->y, 0, 32 * ghost_speed))
												{
													it->y -= 32 * ghost_speed;
												}
												break;
											case 1:
												if (it->y < 592 && !checkGCollision(it->x, it->y, 1, 32 * ghost_speed))
												{
													it->y += 32 * ghost_speed;
												}
												break;
											case 2:
												if (it->x > 10 && !checkGCollision(it->x, it->y, 2, 32 * ghost_speed))
												{
													it->x -= 32 * ghost_speed;
												}
												break;
											case 3:
												if (it->x < 602 && !checkGCollision(it->x, it->y, 3, 32 * ghost_speed))
												{
													it->x += 32 * ghost_speed;

												}
												break;
											}
											if (map[it->x / 32][it->y / 32] == GRASS)
												map[((it->x) / 32)][((it->y) / 32)] = GHOSTC;
											it->countDecision++;
										}
										else if (it->countDecision == 60)
										{

											it->countDecision = 0;

										}
										false;
									}

								}
								if (decision)
								{
									if (map[it->x / 32][it->y / 32] == GHOSTC)
										map[it->x / 32][it->y / 32] = GRASS;

									switch (path_finding(*it, people))
									{
									case 0:
										if (it->y > 10 && !checkGCollision(it->x, it->y, 0, 32 * ghost_speed))
										{
											it->dir = 0;
											it->y = int((double)it->y - 32 * ghost_speed);

										}
										break;
									case 1:
										if (it->y < 562 && !checkGCollision(it->x, it->y, 1, 32 * ghost_speed))
										{
											it->dir = 1;
											it->y = int((double)it->y + 32 * ghost_speed);
										}
										break;
									case 2:
										if (it->x > 10 && !checkGCollision(it->x, it->y, 2, 32 * ghost_speed))
										{
											it->dir = 2;
											it->x = int((double)it->x - 32 * ghost_speed);
										}
										break;
									case 3:
										if (it->x < 592 && !checkGCollision(it->x, it->y, 3, 32 * ghost_speed))
										{
											it->dir = 3;
											it->x = int((double)it->x + 32 * ghost_speed);

										}
										break;
									}
									if (map[it->x / 32][it->y / 32] == GRASS)
										map[((it->x) / 32)][((it->y) / 32)] = GHOSTC;
								}
								countGhost++;
								paintGhost(hdc, *it, mdc, ghostdcn, ghostdc);
								ghostlist.next();
							}
							ghostlist.setStart();
							countGhost = 0;
						}
						//绘制炸弹
					//遍历炸弹链表

						Bomb *item = new Bomb;
						bomblist.setStart();

						if ((bomblist.leftcnt + bomblist.rightcnt) > 0) {
							while (bomblist.fence != bomblist.tail)
							{
								bool flag = false;
								bomblist.getValue(item);
								item->tN = GetTickCount();
								changeValue(item);

								if (item->loop < 20)
								{

									paintBomb(hdc, bombdc, mdc,*item);
								}
								else
								{
									doHurt(item,ghostlist, boxlist, hdc);
									flag = true;
									countatk++;
									map[item->x_axis][item->y_axis] = GRASS;
									Bomb *btemp = new Bomb;
									bomblist.remove(*btemp);
								}
							
								bomblist.next();
							}

							
						}paintHP(people.hp,people.x,people.y,hdc);
					}
				}
				
			}
			
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TOMBRAIDER1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TOMBRAIDER1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   num = 0;
   startwd= CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   //载入地图图片资源
   base = (HBITMAP)LoadImage(NULL, "base.bmp", IMAGE_BITMAP, 288, 32, LR_LOADFROMFILE);
   //花树
   flower0= (HBITMAP)LoadImage(NULL, "flr0.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
   flower1 = (HBITMAP)LoadImage(NULL, "flr1.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
   flower2 = (HBITMAP)LoadImage(NULL, "flr2.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
   flower3 = (HBITMAP)LoadImage(NULL, "flr3.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
  // flower4 = (HBITMAP)LoadImage(NULL, "flr4.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
   lflower= (HBITMAP)LoadImage(NULL, "lflw.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
   lflowern = (HBITMAP)LoadImage(NULL, "lflwn.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
   stone0 = (HBITMAP)LoadImage(NULL, "stn0.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
  
   tree0 = (HBITMAP)LoadImage(NULL, "tr0.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
   //载入人图片资源
   //角色图
   girl[0] = (HBITMAP)LoadImage(NULL, "Yangguo_00.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   girl[1] = (HBITMAP)LoadImage(NULL, "Yangguo_01.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   girl[2] = (HBITMAP)LoadImage(NULL, "Yangguo_02.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   girl[3] = (HBITMAP)LoadImage(NULL, "Yangguo_03.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);

   girln[0] = (HBITMAP)LoadImage(NULL, "Yangguon_00.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   girln[1] = (HBITMAP)LoadImage(NULL, "Yangguon_01.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   girln[2] = (HBITMAP)LoadImage(NULL, "Yangguon_02.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   girln[3] = (HBITMAP)LoadImage(NULL, "Yangguon_03.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   walk0 = (HBITMAP)LoadImage(NULL, "Yangguo_00.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   walk1 = (HBITMAP)LoadImage(NULL, "Yangguo_01.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   walk2 = (HBITMAP)LoadImage(NULL, "Yangguo_02.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   walk3 = (HBITMAP)LoadImage(NULL, "Yangguo_03.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);

   walkn0 = (HBITMAP)LoadImage(NULL, "Yangguon_00.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   walkn1 = (HBITMAP)LoadImage(NULL, "Yangguon_01.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   walkn2= (HBITMAP)LoadImage(NULL, "Yangguon_02.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   walkn3 = (HBITMAP)LoadImage(NULL, "Yangguon_03.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
  //陷阱图
   trap= (HBITMAP)LoadImage(NULL, "Mashroom1.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   trapn = (HBITMAP)LoadImage(NULL, "Mashroomn1.bmp", IMAGE_BITMAP, 96, 32, LR_LOADFROMFILE);
   //怪物图
   ghost[0] = (HBITMAP)LoadImage(NULL, "spider_00.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   ghost[1] = (HBITMAP)LoadImage(NULL, "spider_01.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   ghost[2] = (HBITMAP)LoadImage(NULL, "spider_02.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   ghost[3] = (HBITMAP)LoadImage(NULL, "spider_03.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);

   ghostn[0] = (HBITMAP)LoadImage(NULL, "spidern_00.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   ghostn[1] = (HBITMAP)LoadImage(NULL, "spidern_01.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   ghostn[2] = (HBITMAP)LoadImage(NULL, "spidern_02.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   ghostn[3] = (HBITMAP)LoadImage(NULL, "spidern_03.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   //狗
   dog[0]= (HBITMAP)LoadImage(NULL, "dog_00.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   dog[1] = (HBITMAP)LoadImage(NULL, "dog_01.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   dog[2] = (HBITMAP)LoadImage(NULL, "dog_02.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   dog[3] = (HBITMAP)LoadImage(NULL, "dog_03.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);

   dogn[0] = (HBITMAP)LoadImage(NULL, "dogn_00.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   dogn[1] = (HBITMAP)LoadImage(NULL, "dogn_01.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   dogn[2] = (HBITMAP)LoadImage(NULL, "dogn_02.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   dogn[3] = (HBITMAP)LoadImage(NULL, "dogn_03.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);

   monster[0]= (HBITMAP)LoadImage(NULL, "monster_00.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   monster[1] = (HBITMAP)LoadImage(NULL, "monster_01.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   monster[2] = (HBITMAP)LoadImage(NULL, "monster_02.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   monster[3] = (HBITMAP)LoadImage(NULL, "monster_03.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);

   monstern[0] = (HBITMAP)LoadImage(NULL, "monstern_00.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   monstern[1] = (HBITMAP)LoadImage(NULL, "monstern_01.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   monstern[2] = (HBITMAP)LoadImage(NULL, "monstern_02.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   monstern[3] = (HBITMAP)LoadImage(NULL, "monstern_03.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   monsters[0] = (HBITMAP)LoadImage(NULL, "monster_00.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   monsters[1] = (HBITMAP)LoadImage(NULL, "monster_01.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   monsters[2] = (HBITMAP)LoadImage(NULL, "monster_02.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   monsters[3] = (HBITMAP)LoadImage(NULL, "monster_03.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);

   monsterns[0] = (HBITMAP)LoadImage(NULL, "monstern_00.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   monsterns[1] = (HBITMAP)LoadImage(NULL, "monstern_01.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   monsterns[2] = (HBITMAP)LoadImage(NULL, "monstern_02.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   monsterns[3] = (HBITMAP)LoadImage(NULL, "monstern_03.bmp", IMAGE_BITMAP, 128, 32, LR_LOADFROMFILE);
   food= (HBITMAP)LoadImage(NULL, "food.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
   foodn = (HBITMAP)LoadImage(NULL, "foodn.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
   box = (HBITMAP)LoadImage(NULL, "box.bmp", IMAGE_BITMAP, 256, 256, LR_LOADFROMFILE);
   house= (HBITMAP)LoadImage(NULL, "house.bmp", IMAGE_BITMAP, 32,32, LR_LOADFROMFILE);
   housen= (HBITMAP)LoadImage(NULL, "housen.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
   //炸弹
   bomb= (HBITMAP)LoadImage(NULL, "bomb.bmp", IMAGE_BITMAP, 256,128, LR_LOADFROMFILE);
   bombs = (HBITMAP)LoadImage(NULL, "bomb.bmp", IMAGE_BITMAP, 256, 128, LR_LOADFROMFILE);
   bombn = (HBITMAP)LoadImage(NULL, "bombn.bmp", IMAGE_BITMAP, 256, 128, LR_LOADFROMFILE);
   bgpic= (HBITMAP)LoadImage(NULL, "bgpic.bmp", IMAGE_BITMAP, 1064, 624, LR_LOADFROMFILE);
   //按键
   deg1= LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BM1));
   deg2 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BM2));
   deg3 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BM3));
   btnetrbmp= LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));
   btnextbmp = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP3));
   musicclsbmp = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP4));
 //结束界面
   gv= (HBITMAP)LoadImage(NULL, "gv.bmp", IMAGE_BITMAP, 500, 339, LR_LOADFROMFILE);
   gvn = (HBITMAP)LoadImage(NULL, "gvn.bmp", IMAGE_BITMAP, 500, 339, LR_LOADFROMFILE);
   gvbg= (HBITMAP)LoadImage(NULL, "gvbg.bmp", IMAGE_BITMAP, 592, 602, LR_LOADFROMFILE);
   vicbg= (HBITMAP)LoadImage(NULL, "vic1.bmp", IMAGE_BITMAP, 592, 602, LR_LOADFROMFILE);
   vicbg2= (HBITMAP)LoadImage(NULL, "vic2.bmp", IMAGE_BITMAP, 592, 602, LR_LOADFROMFILE);
   //道具
   bookbmp = (HBITMAP)LoadImage(NULL, "book.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
	 //bubblebmp
    shoebmp= (HBITMAP)LoadImage(NULL, "shoe.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
	shoen= (HBITMAP)LoadImage(NULL, "shoen.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
	bubblebmp = (HBITMAP)LoadImage(NULL, "bubble.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
	bubblen = (HBITMAP)LoadImage(NULL, "bubblen.bmp", IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE);
	hp1 = (HBITMAP)LoadImage(NULL, "hp1.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp2 = (HBITMAP)LoadImage(NULL, "hp2.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp3 = (HBITMAP)LoadImage(NULL, "hp3.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp4 = (HBITMAP)LoadImage(NULL, "hp4.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp5 = (HBITMAP)LoadImage(NULL, "hp5.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp6 = (HBITMAP)LoadImage(NULL, "hp6.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp7 = (HBITMAP)LoadImage(NULL, "hp7.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp8 = (HBITMAP)LoadImage(NULL, "hp8.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp9 = (HBITMAP)LoadImage(NULL, "hp9.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp10= (HBITMAP)LoadImage(NULL, "hp10.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);

	hp1n = (HBITMAP)LoadImage(NULL, "hp1n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp2n = (HBITMAP)LoadImage(NULL, "hp2n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp3n = (HBITMAP)LoadImage(NULL, "hp3n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp4n = (HBITMAP)LoadImage(NULL, "hp4n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp5n = (HBITMAP)LoadImage(NULL, "hp5n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp6n = (HBITMAP)LoadImage(NULL, "hp6n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp7n = (HBITMAP)LoadImage(NULL, "hp7n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp8n = (HBITMAP)LoadImage(NULL, "hp8n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp9n = (HBITMAP)LoadImage(NULL, "hp9n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
	hp10n = (HBITMAP)LoadImage(NULL, "hp10n.bmp", IMAGE_BITMAP, 50, 10, LR_LOADFROMFILE);
   if (!(hwnd|| startwd))
   {
      return FALSE;
   }
    
   MoveWindow(startwd, 60, 5, 1064, 664, true);
   ShowWindow(startwd, nCmdShow);
   UpdateWindow(startwd);
  //获得dc和bitmap
   hdc = GetDC(hwnd);
   mdc = CreateCompatibleDC(hdc);
   bufdc = CreateCompatibleDC(hdc);
   bufdc_walk = CreateCompatibleDC(hdc);
   bufdc_n = CreateCompatibleDC(hdc);
   ghostdc = CreateCompatibleDC(hdc); 
   ghostdcn = CreateCompatibleDC(hdc);
   bombdc= CreateCompatibleDC(hdc);
   bgdc= GetDC(startwd);
   bgbufdc = CreateCompatibleDC(bgdc);
   bgmap = CreateCompatibleBitmap(bgdc, 1064, 624);
   SelectObject(bgbufdc, bgpic);
   gvdc= CreateCompatibleDC(hdc);
   gvdcbuf = CreateCompatibleDC(hdc);

   fullmap = CreateCompatibleBitmap(hdc, 592, 602);
   BitBlt(bgdc, 0, 0, 1064, 624, bgbufdc, 0, 0, SRCCOPY);
   gvbgdc= CreateCompatibleDC(hdc);
   

   hBtn1 = (HWND)CreateWindow(TEXT("Button"), 
	   TEXT(""),
	   WS_VISIBLE | WS_CHILD | BS_BITMAP,
	   500, 340, 109, 40,
	   startwd,
	   (HMENU)IDB_DONE,  //(重点)这里设置按钮id,但是 原本是设置菜单的 所以需要HMENU
	   hInst,
	   NULL);
   hBtn2 = (HWND)CreateWindow(TEXT("Button"),  //Button是预定义 窗体类
	   TEXT(""),
	   WS_VISIBLE | WS_CHILD | BS_BITMAP,
	   500, 390, 109, 40,
	   startwd,
	   (HMENU)IDB_DTWO,  //(重点)这里设置按钮id,但是 原本是设置菜单的 所以需要HMENU
	   hInst,
	   NULL);
   hBtn3 = (HWND)CreateWindow(TEXT("Button"),  //Button是预定义 窗体类
	   TEXT(""),
	   WS_VISIBLE | WS_CHILD | BS_BITMAP,
	   500, 440, 109, 40,
	   startwd,
	   (HMENU)IDB_DTHREE,  //(重点)这里设置按钮id,但是 原本是设置菜单的 所以需要HMENU
	   hInst,
	   NULL);
   hBtnQuit = (HWND)CreateWindow(TEXT("Button"),  //Button是预定义 窗体类
	   TEXT(""),
	   WS_VISIBLE | WS_CHILD | BS_BITMAP,
	   500, 530, 109, 40,
	   startwd,
	   (HMENU)IDB_ONE,  //(重点)这里设置按钮id,但是 原本是设置菜单的 所以需要HMENU
	   hInst,
	   NULL);
   hBtnStop = (HWND)CreateWindow(TEXT("Button"),  
	   TEXT(""),
	   WS_VISIBLE | WS_CHILD | BS_BITMAP,
	   870, 510, 100, 33,
	   startwd,
	   (HMENU)IDB_FOUR,  //(重点)这里设置按钮id,但是 原本是设置菜单的 所以需要HMENU
	   hInst,
	   NULL);
   resEtr = (HWND)CreateWindow(TEXT("Button"), 
	   TEXT(""),
	   WS_VISIBLE | WS_CHILD | BS_BITMAP,
	   200, 420, 109, 40,
	   swnd,
	   (HMENU)IDB_TWO,
	   hInst,
	   NULL);
 
   SendMessage(hBtn1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)deg1);
   SendMessage(hBtn2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)deg2);
   SendMessage(hBtn3, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)deg3);
   SendMessage(hBtnQuit, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)btnextbmp);
   SendMessage(hBtnStop, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)musicclsbmp);
   //生成地图
   generateMap();
   SelectObject(mdc, fullmap);
   //图片素材的保存
   
   //绘制地图和人物
   //生成ghost链表并初始化

  // generateGhost(0);
   paintMap(hdc,mdc);
   //生成bomb链表并初始化
   bomblist.init();
   //initPeople(people);
   srand((unsigned)time(NULL));
   while (true)
   {
	   int x = ((rand()+100) % 500) / 32;
	   int y = ((rand() + 100) % 500) / 32;
		   if (map[x][y] == GRASS)
		   {
			   people.setx(x * 32);
			   people.sety(y * 32);
			   break;
		   }
	   
   }
   paintWalk(hdc,  mdc, bufdc_n, bufdc_walk);
   boxlist.init();
   initBox();
   
   initItems();

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
    switch (message)
    {
	case WM_CREATE:
		PlaySound(TEXT("BGM.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		break;
	case WM_KEYDOWN:
	{
		//按下按键，判断人物行为
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		//按空格键放炸弹
		case VK_SPACE:
		{
			Bomb bomb;
			Bomb &bombref=bomb;
			bomb.atk += (bombplus * 20);
			if(sec)
			{
				if (canPutBomb(&bombref))
				{
					bomblists.append(bomb);
					map[bomb.x_axis][bomb.y_axis] = BOMBC;
					SetTimer(hWnd, 1, 100, NULL);
				}
			}
			else {
				if (canPutBomb(&bombref))
				{
					bomblist.append(bomb);
					map[bomb.x_axis][bomb.y_axis] = BOMBC;
					SetTimer(hWnd, 1, 100, NULL);
				}
			}
			
			
		}
		break;
		//按上键
		case VK_UP:
		{
			people.move(0,people.speed);
			if (checkCollision(people.x, people.y, 0, people.speed))
			{

				people.y += people.speed;
			}
		}
		break;

		case VK_DOWN:
		{
			people.move(1, people.speed);
			if (checkCollision(people.x, people.y, 1, people.speed))
			{

				people.y -= people.speed;
			}
		}
		break;

		case VK_LEFT:
		{
			people.move(2, people.speed);
			if (checkCollision(people.x, people.y, 2, people.speed))
			{

				people.x += people.speed;
			}
		}
		break;
		case VK_RIGHT:
		{
			people.move(3, people.speed);
			if (checkCollision(people.x, people.y, 3, people.speed))
			{

				people.x -= people.speed;
			}
		}
		break;

		case 0x41:
		{
			//捡道具
			pickItem();
			break;
		}
		}
	
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDB_ZERO:
				
				ShowWindow(hWnd, SW_HIDE);
				hWnd = hwnd;
				ShowWindow(hWnd, SW_SHOW);
				MoveWindow(hwnd, 250, 35, 592, 602, true);
				UpdateWindow(hwnd);
				
				break;
			case IDB_DONE:
				ghostlist.init();
				deg = 1;
				generateGhost(0);
				haveGhost = true;
				ShowWindow(hWnd, SW_HIDE);
				hWnd = hwnd;
				ShowWindow(hWnd, SW_SHOW);
				MoveWindow(hwnd, 250, 35, 592, 602, true);
				UpdateWindow(hwnd);
				break;
			case IDB_DTWO:
				ghostlist.init();
				deg = 2;
				generateGhost(0);
				haveGhost = true;
				ShowWindow(hWnd, SW_HIDE);
				hWnd = hwnd;
				ShowWindow(hWnd, SW_SHOW);
				MoveWindow(hwnd, 250, 35, 592, 602, true);
				UpdateWindow(hwnd);
				break;
			case IDB_DTHREE:
				ghostlist.init();
				deg = 3;
				generateGhost(0);
				haveGhost = true;
				ShowWindow(hWnd, SW_HIDE);
				hWnd = hwnd;
				ShowWindow(hWnd, SW_SHOW);
				MoveWindow(hwnd, 250, 35, 592, 602, true);
				UpdateWindow(hwnd);
				break;
			case IDB_ONE:
				DestroyWindow(hWnd);
				break;
			case IDB_TWO:
				hWnd = swnd;
				break;
			case IDB_THREE:
				DestroyWindow(hWnd);
				break;
			case IDB_FOUR:
				if (cntMusic == 0)
				{
					PlaySound(NULL, NULL, SND_FILENAME);
					
					cntMusic++;
				}
				else {PlaySound(TEXT("BGM.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					cntMusic = 0;
				}

				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_TIMER:
	{
	}
	break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
		DeleteDC(mdc);
		DeleteDC(bufdc);
		DeleteDC(bombdc);
		DeleteDC(gvdc);
		DeleteDC(gvdcbuf);
		DeleteDC(gvbgdc);
		DeleteDC(bgbufdc);
		DeleteDC(bgdc); 
		DeleteDC(bufdc_walk);
		DeleteDC(bufdc_n);
		DeleteDC(ghostdc);
		DeleteDC(ghostdcn);
		for (int i = 0; i < 4; i++)
		{
			DeleteObject(girl[i]);
			DeleteObject(girln[i]);
			DeleteObject(ghost[i]);
			DeleteObject(ghostn[i]);
		}
		
		DeleteObject(bomb);
		DeleteObject(bombn);
		DeleteObject(gvbg);
		DeleteObject(vicbg);
		DeleteObject(gv);
		DeleteObject(gvn);
		DeleteObject(gvmap);
		DeleteObject(btnetrbmp);
		DeleteObject(btnextbmp);
		DeleteObject(musicclsbmp);
		DeleteObject(base);
		DeleteObject(box);
		DeleteObject(house);
		DeleteObject(housen);
		DeleteObject(fullmap);
		DeleteObject(bgmap);
		DeleteObject(bgpic);
		DeleteObject(hp1);
		DeleteObject(hp2);
		DeleteObject(hp3);
		DeleteObject(hp4);
		DeleteObject(hp5);
		DeleteObject(hp6);
		DeleteObject(hp7);
		DeleteObject(hp8);
		DeleteObject(hp9);
		DeleteObject(hp10);
		DeleteObject(hp1n);
		DeleteObject(hp2n);
		DeleteObject(hp3n);
		DeleteObject(hp4n);
		DeleteObject(hp5n);
		DeleteObject(hp6n);
		DeleteObject(hp7n);
		DeleteObject(hp8n);
		DeleteObject(hp9n);
		DeleteObject(hp10n);
		DeleteObject(bookbmp);
		DeleteObject(bubblebmp);
		DeleteObject(bubblen);
		DeleteObject(shoebmp);
		DeleteObject(shoen);
		DeleteObject(flower0);
		DeleteObject(flower1);
		DeleteObject(flower2);
		DeleteObject(flower3);
		DeleteObject(flower4);
		DeleteObject(stone0);
		DeleteObject(tree0);
		ReleaseDC(hWnd, hdc);
	
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {

    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
