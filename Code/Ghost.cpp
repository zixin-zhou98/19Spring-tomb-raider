#include"Ghost.h"
#include "stdafx.h"
Ghost::Ghost()
{
	hp = 600;
}
Ghost::Ghost(int hp = 600, int x = 30, int y = 30, int atk = 10, int dir = 0, int speed = 8,int type=0,int sec=0)
{
	this->hp = hp;
	this->x = x;
	this->y = y;
	this->atk = atk;
	this->dir = dir;
	this->speed = speed;
	this->countDecision = 0;
	this->tempDir = 0;
	this->type = type;
	this->sec = sec;
}