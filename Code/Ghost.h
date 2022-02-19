#ifndef GHOST
#define GHOST
class Ghost
{
public:
	Ghost();
	Ghost(int hp,int x,int y,int atk,int dir,int speed,int type,int sec);
	int hp=600;
	int x=60;
	int y=60;
	int atk=100;
	int dir=0;
	int speed=10;
	int count=0;
	int x_axis;
	int y_axis;
	int countDecision = 0;
	int tempDir = 0;
	int type;
	int sec;
};

#endif
