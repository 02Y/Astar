#pragma once
#include <iostream>
#include <math.h>
#include <list>
#include <vector>

using namespace std;

const int kCost1 = 10;  //直移一格消耗
const int kCost2 = 14;  //斜移一格消耗

typedef struct _Point
{
	int x, y;    //点坐标，x代表行，y代表列
	int F, G, H;   //F = G + H
	struct _Point* parent;    //parent的坐标
}Point;

/*分配一个节点（格子）*/
Point* AllocPoint(int x, int y);

/*初始化地图*/
void InitAstarMaze(int* _maze, int _lines, int _colums);

/*通过A* 算法寻找路径*/
std::list<Point*> GetPath(Point* startPoint, Point* endPoint);

/*清理资源，结束后必须调用*/
void ClearAstarMaze();

