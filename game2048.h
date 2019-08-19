#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdbool>
#include <ctime>
#include <getch.h>

class game2048
{

public:
	// 创建二维数组
	int arr[4][4];
	// 是否移动或合并过
	bool IS_MOVE_MERGE;

	game2048()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				arr[i][j] = 0;
			}
		}
		IS_MOVE_MERGE = true;
	}
	// 显示界面
	void show_view(void);
	bool is_null(void);
	// 创建一个数
	void creat_num(void);

	void up(void);

	void down(void);

	void right(void);

	void left(void);
	// 判断是否结束
	bool is_over(void);
	//保存
	bool save(void);

	bool load(void);
};
