
#ifndef BOMB
#define BOMB
class Bomb {
public:
	Bomb();
	int atk;
	int s_time;//start time
	int e_time;//end time
	int l_time;//last time
	int loop;//��ѭ������
	//x y ����
	int x;
	int y;
	int x_axis;
	int y_axis;
	DWORD tN,tP;
	
};
#endif