#include "game2048.h"

// 显示界面
void game2048::show_view(void)
{
	// 清理屏幕
	system("clear");

	for (int i = 0; i < 4; i++)
	{
		printf("---------------------\n");
		for (int j = 0; j < 4; j++)
		{
			if (game2048::arr[i][j])
				printf("|%4d", game2048::arr[i][j]);
			else
				printf("|    ");
		}
		printf("|\n");
	}
	printf("---------------------\n");
}

bool game2048::is_null(void)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (0 == game2048::arr[i][j])
			{
				return true;
			}
		}
	}
	return false;
}

// 创建一个数
void game2048::creat_num(void)
{
	// 进入循环前要先保证有空位置
	while (game2048::is_null() && game2048::IS_MOVE_MERGE)
	{
		int x = rand() % 4;
		int y = rand() % 4;
		if (0 == game2048::arr[x][y])
		{
			game2048::arr[x][y] = 2;
			break;
		}
	}
}

void game2048::up(void)
{
	for (int y = 0; y < 4; y++)
	{
		int end = 0;
		for (int x = 1; x < 4; x++)
		{
			for (int m = x; m > end && game2048::arr[m][y]; m--)
			{
				if (game2048::arr[m][y] == game2048::arr[m - 1][y])
				{
					game2048::arr[m - 1][y] *= 2;
					game2048::arr[x][y] = 0;
					end = m;
					game2048::IS_MOVE_MERGE = true;
				}
				else if (0 == arr[m - 1][y])
				{
					game2048::arr[m - 1][y] = game2048::arr[m][y];
					game2048::arr[m][y] = 0;
					game2048::IS_MOVE_MERGE = true;
				}
			}
		}
	}
}

void game2048::down(void)
{
	for (int y = 0; y < 4; y++)
	{
		int end = 3;
		for (int x = 2; x >= 0; x--)
		{
			for (int m = x; m < end && game2048::arr[m][y]; m++)
			{
				if (game2048::arr[m][y] == game2048::arr[m + 1][y])
				{
					game2048::arr[m + 1][y] *= 2;
					game2048::arr[m][y] = 0;
					end = m;
					game2048::IS_MOVE_MERGE = true;
				}
				else if (0 == game2048::arr[m + 1][y])
				{
					game2048::arr[m + 1][y] = game2048::arr[m][y];
					game2048::arr[m][y] = 0;
					game2048::IS_MOVE_MERGE = true;
				}
			}
		}
	}
}

void game2048::right(void)
{
	for (int x = 0; x < 4; x++)
	{
		int end = 3;
		for (int y = 2; y >= 0; y--)
		{
			for (int m = y; m < end && game2048::arr[x][m]; m++)
			{
				if (game2048::arr[x][m] == game2048::arr[x][m + 1])
				{
					game2048::arr[x][m + 1] *= 2;
					game2048::arr[x][m] = 0;
					end = m;
					game2048::IS_MOVE_MERGE = true;
				}
				else if (0 == game2048::arr[x][m + 1])
				{
					game2048::arr[x][m + 1] = game2048::arr[x][m];
					game2048::arr[x][m] = 0;
					game2048::IS_MOVE_MERGE = true;
				}
			}
		}
	}
}

void game2048::left(void)
{
	for (int x = 0; x < 4; x++)
	{
		int end = 0;
		for (int y = 1; y < 4; y++)
		{
			for (int m = y; m > end && game2048::arr[x][m]; m--)
			{
				if (game2048::arr[x][m] == game2048::arr[x][m - 1])
				{
					game2048::arr[x][m - 1] *= 2;
					game2048::arr[x][m] = 0;
					end = m;
					game2048::IS_MOVE_MERGE = true;
				}
				else if (0 == game2048::arr[x][m - 1])
				{
					game2048::arr[x][m - 1] = game2048::arr[x][m];
					game2048::arr[x][m] = 0;
					game2048::IS_MOVE_MERGE = true;
				}
			}
		}
	}
}

// 判断是否结束
bool game2048::is_over(void)
{
	if (game2048::is_null())
	{
		return false;
	}

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (arr[x][y] == game2048::arr[x][y + 1])
			{
				return false;
			}
		}
	}
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (game2048::arr[x][y] == game2048::arr[x + 1][y])
			{
				return false;
			}
		}
	}
	return true;
}

//保存
bool game2048::save(void)
{
	FILE *file = fopen("save.dat", "w");
	fseek(file, 0, SEEK_SET);
	if (1 == fwrite(game2048::arr, sizeof(game2048::arr), 1, file))
	{
		fclose(file);
		return true;
	}
	else
	{
		fclose(file);
		return false;
	}
}

bool game2048::load(void)
{
	FILE *file = fopen("save.dat", "r");
	fseek(file, 0, SEEK_SET);
	if (1 == fread(game2048::arr, sizeof(game2048::arr), 1, file))
	{
		fclose(file);
		return true;
	}
	else
	{
		fclose(file);
		return false;
	}
}

int main()
{
	game2048 *game = new game2048;
	// 设置随机数获取位置
	srand(time(NULL));

	printf("读取上一次保存的存档?\nY.yes\nN.no,start a new game\n");
	switch (getch())
	{
	case 121:
		game->load();
		break;
	default:
		break;
	}
	while (1)
	{
		// 创建一个数
		game->creat_num();
		// 显示界面
		game->show_view();
		// 判断游戏是否结束
		if (game->is_over())
		{
			printf("游戏结束!\n");
			return 0;
		}
		// 假定此次不能移动或合并
		game->IS_MOVE_MERGE = false;
		// 获取方向键，并处理
		switch (getch())
		{
		case 183:
			game->up();
			break; //up
		case 184:
			game->down();
			break; //down
		case 185:
			game->right();
			break; //right
		case 186:
			game->left();
			break; //left
		case 115:
			game->save();
			return -1;
		default:
			break;
		}
	}
}
