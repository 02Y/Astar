#include "Astar.h"

static int* maze;  //迷宫对应的二维数组，使用一级指针表示
static int cols;   //二维数组对应的列数
static int lines;  //二维数组对应的行数

static std::list<Point*> openList;  //开放列表
static std::list<Point*> closeList;  //关闭列表

/*搜索从起点到终点的最佳路径*/
static Point* findPath(Point* startPoint, Point* endPoint);

//从开启列表中返回 F 值最小的节点
static Point* getLeastFpoint();

/*获取当前节点周围可达的节点*/
static vector<Point*> getSurroundPoints(const Point* point);

/*判断下一步节点是否可行*/
static bool isCanreach(const Point* point, const Point* target);

/*判断开启/关闭列表中是否包含某点*/
static Point* isInList(const list<Point*>& list, const Point* point);

/*计算节点G的值*/
static int calcG(Point* temp_star, Point* point);

//计算节点H的值
static int calcH(Point* point, Point* end);

//计算节点F的值
static int calcF(Point* point);

/*分配一个节点（格子）*/
Point* AllocPoint(int x, int y)
{
	Point* temp = new Point;

	memset(temp, 0, sizeof(Point));   //初始值清0
	temp->x = x;
	temp->y = y;

	return temp;
}

/*初始化A* 搜索的地图*/
void InitAstarMaze(int* _maze, int _lines, int _colums)
{
	maze = _maze;
	lines = _lines;
	cols = _colums;
}

/*通过A* 算法寻找路径*/
std::list<Point*> GetPath(Point* startPoint, Point* endPoint)
{
	Point* result = findPath(startPoint, endPoint);


	std::list<Point*> path;

	//返回路径，如果没找到路径，返回空链表
	while (result)
	{
		path.push_front(result);
		result = result->parent;
	}
	return path;
}

/*搜索从起点到终点的最佳路径*/
static Point* findPath(Point* startPoint, Point* endPoint)
{
	//置入起点，拷贝开辟一个节点，内外隔离
	openList.push_back(AllocPoint(startPoint->x, startPoint->y));

	while (!openList.empty())
	{
		//第一步，从开放列表中取 F 值最小的节点
		Point* curPoint = getLeastFpoint();  //找到 F 最小值


		//第二步，把当前节点放到关闭列表中
		openList.remove(curPoint);
		closeList.push_back(curPoint);

		//第三步，找到当前节点周围可达的节点，并计算F值
		vector<Point*> surroundPoints = getSurroundPoints(curPoint);
		vector<Point*>::const_iterator itor;
		for (itor = surroundPoints.begin(); itor != surroundPoints.end(); itor++)
		{
			Point* target = *itor;
			//对某一个格子，如果他不在开放列表中，加入到开放列表，设置当前格为父节点，并计算 F G H
			Point* exist = isInList(openList, target);
			if (!exist)
			{
				target->parent = curPoint;
				target->G = calcG(curPoint, target);
				target->H = calcH(target, endPoint);
				target->F = calcF(target);

				openList.push_back(target);
			}
			else   //如果在开放列表中
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

/*获取当前节点周围可达的节点*/
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

/*判断下一步节点是否可行*/
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
	if (abs(point->x - target->x) + abs(point->y - target->y) == 1)  // abs求绝对值
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*判断开启/关闭列表中是否包含某点*/
static Point* isInList(const list<Point*>& list, const Point* point)
{
	//判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较值
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

/*计算节点G的值*/
static int calcG(Point* temp_star, Point* point)
{
	int extraG = (abs(point->x - temp_star->x) + abs(point->y - temp_star->y)) == 1 ? kCost1 : kCost2;
	int parentG = (point->parent == NULL ? NULL : point->parent->G);  //如果是初始节点，没有父节点
	return parentG + extraG;
}

//计算节点H的值
static int calcH(Point* point, Point* end)
{
	// a方 + b方 = c方  勾股定理
	return (int)sqrt((double)(static_cast<double>(end->x) - point->x) *
		(double)(static_cast<double>(end->x) - point->x) +
		(double)(static_cast<double>(end->y) - point->y) *
		(double)(static_cast<double>(end->y) - point->y));
}

//计算节点F的值
static int calcF(Point* point)
{
	return (point->G + point->H);
}

/*清理资源，结束后必须调用*/
void ClearAstarMaze()
{
	maze = NULL;
	lines = 0;
	cols = 0;
	list<Point*>::iterator itor;

	//清除openlist 中的元素
	for (itor = openList.begin(); itor != openList.end();)
	{
		delete* itor;
		itor = openList.erase(itor);  // 获取到下一个节点
	}

	//清除closeList 中的元素
	for (itor = closeList.begin(); itor != closeList.end();)
	{
		delete* itor;
		itor = closeList.erase(itor);
	}
}
