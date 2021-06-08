#include "Astar.h"
#include <windows.h>


//定义地图数组
int map[13][13] =
{    //二维数组在内存顺序存储的
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

	//设置起始和结束点
	Point* star = AllocPoint(12, 4);
	Point* end = AllocPoint(0, 0);

	//A*算法寻找路径
	list<Point*>path = GetPath(star, end);
	list<Point*>::const_iterator itor;

	cout << "寻路结果：" << endl;
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
