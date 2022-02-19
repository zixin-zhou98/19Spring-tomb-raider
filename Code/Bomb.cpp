#include"Bomb.h"
#include<time.h>
#include"stdafx.h"
Bomb::Bomb()
{
	atk = 200;
	loop = 0;
	x =x_axis= 0;
	y = y_axis = 0;
	tP = GetTickCount();
	l_time = 1000;
}