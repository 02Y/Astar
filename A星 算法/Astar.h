#pragma once
#include <iostream>
#include <math.h>
#include <list>
#include <vector>

using namespace std;

const int kCost1 = 10;  //ֱ��һ������
const int kCost2 = 14;  //б��һ������

typedef struct _Point
{
	int x, y;    //�����꣬x�����У�y������
	int F, G, H;   //F = G + H
	struct _Point* parent;    //parent������
}Point;

/*����һ���ڵ㣨���ӣ�*/
Point* AllocPoint(int x, int y);

/*��ʼ����ͼ*/
void InitAstarMaze(int* _maze, int _lines, int _colums);

/*ͨ��A* �㷨Ѱ��·��*/
std::list<Point*> GetPath(Point* startPoint, Point* endPoint);

/*������Դ��������������*/
void ClearAstarMaze();

