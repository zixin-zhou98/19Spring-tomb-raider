#ifndef PEOPLE
#define PEOPLE
class People {
public:
	People();
	People(int hp,int x,int y, int dir,int speed);
	void move(int currentdir,int speed=10);
	int hp;//Ѫ��hit point
	int speed;//�ٶ�
	int x, y;//����
	int dir;//����
	void setx(int x);
	void sety(int y);
	bool isAlive;
private:	
	void putBomb();

};
#endif