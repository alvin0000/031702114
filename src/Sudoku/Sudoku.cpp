// Sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<fstream>
using namespace std;
string OUT;
class Map {
private:
	int map_int[10][10];//存放九宫格 
	int e;//阶数 
	bool vis[3][55][10];//标识列、行、宫数字是否可用
	int k;//待填区域下标
	bool flag;//是否填完 
	struct Node {
		int x;
		int y;
	}arr[100];//链式存放九宫格待填区域 
public:
	//构造函数 
	Map(int (*data)[10],int e1)
	{
		for (int i = 1; i <= 9; i++)
			for (int j = 1; j <= 9; j++)
				map_int[i][j] = data[i][j];
		memset(vis, true, sizeof(vis));
		e = e1;
		k = 0;
		flag = false;
	}
	//计算所属宫 
	int Hash(int i, int j)
	{
		switch (e)
		{
		case 3:return ( i - 1)*3 + j;
		case 4:return (i - 1) / 2 * 2 + (j - 1) / 2 + 1;
		case 5:return (i - 1) * 5 + j;
		case 6:return (i - 1) / 2 * 2 + (j - 1) / 3 + 1;
		case 7:return (i - 1) * 7 + j;
		case 8:return (i - 1) / 4 * 4 + (j - 1) / 2 + 1;
		case 9:return (i - 1) / 3 * 3 + (j - 1) / 3 + 1;
		default: printf("阶数不符\n");
		}
		return 0;
	}
	//记录各行、列、宫的数字使用情况 
	void Record()
	{
		for (int i = 1; i <= e; i++)
			for (int j = 1; j <= e; j++)
			{
				if (map_int[i][j] == 0)
					arr[k++].x = i, arr[k - 1].y = j;
				vis[0][i][map_int[i][j]] = vis[1][j][map_int[i][j]] = vis[2][Hash(i, j)][map_int[i][j]] = false;
			}
	}
	//遍历所有情况
	void dfs(int h)
	{
		if (h == k)
		{
			flag = true;
			return;
		}
		int x = arr[h].x;
		int y = arr[h].y;
		for (int i = 1; i <= e; i++)
		{
			if (!vis[0][x][i] || !vis[1][y][i] || !vis[2][Hash(x, y)][i])
				continue;
			vis[0][x][i] = vis[1][y][i] = vis[2][Hash(x, y)][i] = false;
			map_int[x][y] = i;
			dfs(h + 1);
			if (flag) return;
			vis[0][x][i] = vis[1][y][i] = vis[2][Hash(x, y)][i] = true;
		}
	}
	//打印结果 
	void Print()
	{
		fstream bfile;
		bfile.open(OUT, ios::app | ios::out);
		for (int i = 1; i <= e; i++)
			for (int j = 1; j <= e; j++)
			{
				bfile << map_int[i][j];
				if (j == e)
					bfile << endl;
				else
					bfile << " ";
//				printf("%d%c", map_int[i][j], j == e ? '\n' : ' ');
			}
		bfile << endl;
				
	}
};
int main(int argc,char **argv)
//int main()
{
	int data[10][10], m = 0, n = 0;
	fstream afile;
	afile.open(argv[6], ios::app |ios::in);
//	cin >> m >> n;
	m=atoi(argv[2]);
	n=atoi(argv[4]);
//	printf("%d\n", m);
//	printf("%d\n", n);
	OUT = argv[8];
	while (n--)
	{
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= m; j++)
			{
//				cin >> data[i][j];
				afile >> data[i][j];
//				printf("%d", data[i][j]);
			}
//		printf("\n");
		Map Map1(data,m);
		Map1.Record();
		Map1.dfs(0);
		Map1.Print();
	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
