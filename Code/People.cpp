#include"People.h"
#include "stdafx.h"
People::People()
{
	hp = 1000;
	this->isAlive = true;
}
People::People(int hp=1000, int x=30, int y=30, int dir=0,int speed=10)
{
	this->hp = hp;
	this->x = x;
	this->y = y;
	this->dir = dir;
	this->speed = speed;
	this->isAlive = true;
}
void People::setx(int x)
{
	this->x = x;
}
void People::sety(int y)
{
	this->y = y;
}
void People::putBomb()
{

}
void People::move(int targetdir, int speed)
{
	//根据原来位置修正人物位置，暂时这样
	switch (targetdir)
	{
	case 0:
	{
		switch (dir)
		{
		case 0:
			y -= speed;
			break;
		case 1:
			//x -= 1;
			y -= speed;
			break;
		case 2:
			//x += 2;
			y -= speed;
			break;
		case 3:
			//x += 2;
			y -= speed;
			break;
		}
		if (y < 0)
			y = 0;

	}
	break;
	case 1:
	{
		y += speed;
		if (y > 512)
			y = 512;
	}
	break;
	case 2:
	{
		x -= speed;
		if (x < 0)
			x = 0;

	}
	break;
	case 3:
	{
		x += speed;
		if (x > 560)
			x = 560;

	}
	break;
	
	}
	dir = targetdir;
}