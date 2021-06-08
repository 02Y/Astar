#include "Astar.h"

static int* maze;  //�Թ���Ӧ�Ķ�ά���飬ʹ��һ��ָ���ʾ
static int cols;   //��ά�����Ӧ������
static int lines;  //��ά�����Ӧ������

static std::list<Point*> openList;  //�����б�
static std::list<Point*> closeList;  //�ر��б�

/*��������㵽�յ�����·��*/
static Point* findPath(Point* startPoint, Point* endPoint);

//�ӿ����б��з��� F ֵ��С�Ľڵ�
static Point* getLeastFpoint();

/*��ȡ��ǰ�ڵ���Χ�ɴ�Ľڵ�*/
static vector<Point*> getSurroundPoints(const Point* point);

/*�ж���һ���ڵ��Ƿ����*/
static bool isCanreach(const Point* point, const Point* target);

/*�жϿ���/�ر��б����Ƿ����ĳ��*/
static Point* isInList(const list<Point*>& list, const Point* point);

/*����ڵ�G��ֵ*/
static int calcG(Point* temp_star, Point* point);

//����ڵ�H��ֵ
static int calcH(Point* point, Point* end);

//����ڵ�F��ֵ
static int calcF(Point* point);

/*����һ���ڵ㣨���ӣ�*/
Point* AllocPoint(int x, int y)
{
	Point* temp = new Point;

	memset(temp, 0, sizeof(Point));   //��ʼֵ��0
	temp->x = x;
	temp->y = y;

	return temp;
}

/*��ʼ��A* �����ĵ�ͼ*/
void InitAstarMaze(int* _maze, int _lines, int _colums)
{
	maze = _maze;
	lines = _lines;
	cols = _colums;
}

/*ͨ��A* �㷨Ѱ��·��*/
std::list<Point*> GetPath(Point* startPoint, Point* endPoint)
{
	Point* result = findPath(startPoint, endPoint);


	std::list<Point*> path;

	//����·�������û�ҵ�·�������ؿ�����
	while (result)
	{
		path.push_front(result);
		result = result->parent;
	}
	return path;
}

/*��������㵽�յ�����·��*/
static Point* findPath(Point* startPoint, Point* endPoint)
{
	//������㣬��������һ���ڵ㣬�������
	openList.push_back(AllocPoint(startPoint->x, startPoint->y));

	while (!openList.empty())
	{
		//��һ�����ӿ����б���ȡ F ֵ��С�Ľڵ�
		Point* curPoint = getLeastFpoint();  //�ҵ� F ��Сֵ


		//�ڶ������ѵ�ǰ�ڵ�ŵ��ر��б���
		openList.remove(curPoint);
		closeList.push_back(curPoint);

		//���������ҵ���ǰ�ڵ���Χ�ɴ�Ľڵ㣬������Fֵ
		vector<Point*> surroundPoints = getSurroundPoints(curPoint);
		vector<Point*>::const_iterator itor;
		for (itor = surroundPoints.begin(); itor != surroundPoints.end(); itor++)
		{
			Point* target = *itor;
			//��ĳһ�����ӣ���������ڿ����б��У����뵽�����б����õ�ǰ��Ϊ���ڵ㣬������ F G H
			Point* exist = isInList(openList, target);
			if (!exist)
			{
				target->parent = curPoint;
				target->G = calcG(curPoint, target);
				target->H = calcH(target, endPoint);
				target->F = calcF(target);

				openList.push_back(target);
			}
			else   //����ڿ����б���
			{
				int tempG = calcG(curPoint, target);
				if (tempG < target->G)
				{
					exist->parent = curPoint;
					exist->G = tempG;
					exist->F = calcF(target);
				}
				delete target;
			}
		} // end for
		surroundPoints.clear();
		Point* resPoint = isInList(openList, endPoint);
		if (resPoint)
		{
			return resPoint;
		}
	}
	return NULL;
}

static Point* getLeastFpoint()
{
	if (!openList.empty())
	{
		Point* resPoint = openList.front();
		std::list<Point*>::const_iterator itor;

		for (itor = openList.begin(); itor != openList.end(); itor++)
		{
			if ((*itor)->F < resPoint->F)
			{
				resPoint = *itor;
			}
		}
		return resPoint;
	}
	return NULL;
}

/*��ȡ��ǰ�ڵ���Χ�ɴ�Ľڵ�*/
static vector<Point*> getSurroundPoints(const Point* point)
{
	vector<Point* > surroundPoints;
	for (int x = point->x - 1; x <= point->x + 1; x++)
	{
		for (int y = point->y - 1; y <= point->y + 1; y++)
		{
			Point* temp = AllocPoint(x, y);
			if (isCanreach(point, temp))
			{
				surroundPoints.push_back(temp);
			}
			else
			{
				delete temp;
			}
		}
	}
	return surroundPoints;
}

/*�ж���һ���ڵ��Ƿ����*/
static bool isCanreach(const Point* point, const Point* target)
{
	if (target->x < 0 || target->x >(lines - 1)
		|| target->y < 0 || target->y >(cols - 1)
		|| maze[target->x * cols + target->y] == 1
		|| maze[target->x * cols + target->y] == 2
		|| (target->x == point->x && target->y == point->y)
		|| isInList(closeList, target))
	{
		return false;
	}
	if (abs(point->x - target->x) + abs(point->y - target->y) == 1)  // abs�����ֵ
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*�жϿ���/�ر��б����Ƿ����ĳ��*/
static Point* isInList(const list<Point*>& list, const Point* point)
{
	//�ж�ĳ���ڵ��Ƿ����б��У����ﲻ�ܱȽ�ָ�룬��Ϊÿ�μ����б����¿��ٵĽڵ㣬ֻ�ܱȽ�ֵ
	std::list<Point*>::const_iterator itor;

	for (itor = list.begin(); itor != list.end(); itor++)
	{
		if ((*itor)->x == point->x && (*itor)->y == point->y)
		{
			return *itor;
		}
	}
	return NULL;
}

/*����ڵ�G��ֵ*/
static int calcG(Point* temp_star, Point* point)
{
	int extraG = (abs(point->x - temp_star->x) + abs(point->y - temp_star->y)) == 1 ? kCost1 : kCost2;
	int parentG = (point->parent == NULL ? NULL : point->parent->G);  //����ǳ�ʼ�ڵ㣬û�и��ڵ�
	return parentG + extraG;
}

//����ڵ�H��ֵ
static int calcH(Point* point, Point* end)
{
	// a�� + b�� = c��  ���ɶ���
	return (int)sqrt((double)(static_cast<double>(end->x) - point->x) *
		(double)(static_cast<double>(end->x) - point->x) +
		(double)(static_cast<double>(end->y) - point->y) *
		(double)(static_cast<double>(end->y) - point->y));
}

//����ڵ�F��ֵ
static int calcF(Point* point)
{
	return (point->G + point->H);
}

/*������Դ��������������*/
void ClearAstarMaze()
{
	maze = NULL;
	lines = 0;
	cols = 0;
	list<Point*>::iterator itor;

	//���openlist �е�Ԫ��
	for (itor = openList.begin(); itor != openList.end();)
	{
		delete* itor;
		itor = openList.erase(itor);  // ��ȡ����һ���ڵ�
	}

	//���closeList �е�Ԫ��
	for (itor = closeList.begin(); itor != closeList.end();)
	{
		delete* itor;
		itor = closeList.erase(itor);
	}
}
