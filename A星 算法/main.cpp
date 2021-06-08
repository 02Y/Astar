#include "Astar.h"
#include <windows.h>


//�����ͼ����
int map[13][13] =
{    //��ά�������ڴ�˳��洢��
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
	{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,},
	{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,},
	{0, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0,},
	{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,},
	{0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0,},
	{0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0,},
	{2, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 2,},
	{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0,},
	{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,},
	{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0,},
	{0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0,},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}
};

void AstarTest()
{
	InitAstarMaze(&map[0][0], 13, 13);

	//������ʼ�ͽ�����
	Point* star = AllocPoint(12, 4);
	Point* end = AllocPoint(0, 0);

	//A*�㷨Ѱ��·��
	list<Point*>path = GetPath(star, end);
	list<Point*>::const_iterator itor;

	cout << "Ѱ·�����" << endl;
	for (itor = path.begin(); itor != path.end(); itor++)
	{
		Point* cur = *itor;
		cout << "(" << cur->x << "," << cur->y << ")\n";
		Sleep(800);
	}
	ClearAstarMaze();
}

int main(void)
{
	AstarTest();

	return 0;
}
