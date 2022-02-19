#ifndef PEOPLE
#define PEOPLE
class People {
public:
	People();
	People(int hp,int x,int y, int dir,int speed);
	void move(int currentdir,int speed=10);
	int hp;//血量hit point
	int speed;//速度
	int x, y;//坐标
	int dir;//方向
	void setx(int x);
	void sety(int y);
	bool isAlive;
private:	
	void putBomb();

};
#endif