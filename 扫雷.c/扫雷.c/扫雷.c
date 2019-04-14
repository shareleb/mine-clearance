#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#include<time.h>
#define MAX_ROW  9
#define MAX_COL  9
#define MINE_COUNT 10
int menu() {
	int input = 0;
	printf("====================\n");
	printf("==== 1.play ========\n");
	printf("==== 0.exit ========\n");
	printf("====================\n");
	printf("请输入您的选择>: ");
	scanf("%d", &input);
	return input;
}
void Initarray(char show_map[][MAX_COL], char mine_map[][MAX_COL]) {
	for (int row = 0; row < MAX_ROW; row++) {
		for (int col = 0; col < MAX_COL; col++) {
			show_map[row][col] = '*';
		}
	}
		for (int row = 0; row < MAX_ROW; row++) {
			for (int col = 0; col < MAX_COL; col++) {
				mine_map[row][col] = '0';
			}
		}
	srand((unsigned)time(0));
	int count = 0;
	while (count <MINE_COUNT) {
		int row = rand() % 9;
		int col = rand() % 9;
		if (mine_map[row][col] == '1') {
			continue;
		}
		mine_map[row][col] = '1';
		count++;
	}
}
int  UpdateShowmap(int row, int col, char mine_map[][MAX_COL]) {
	int number = 0;
	if (col - 1 >= 0 && mine_map[row - 1][col - 1] == '1'&&row - 1 >= 0) {
		number++;
	}
	if (row - 1 >= 0 && mine_map[row - 1][col] == '1') {
		number++;
	}
	if (row - 1 >= 0 && col + 1 < MAX_COL&&mine_map[row - 1][col + 1] == '1') {
		number++;
	}
	if (col - 1 >= 0 && mine_map[row][col - 1] == '1') {
		number++;
	}
	if (col + 1 < MAX_COL&&mine_map[row][col + 1] == '1') {
		number++;
	}
	if (row + 1 <= MAX_ROW && col - 1 >= 0 && mine_map[row + 1][col - 1] == '1') {
		number++;
	}
	if (row + 1 < MAX_COL&&mine_map[row + 1][col] == '1') {
		number++;
	}
	if (row + 1 < MAX_ROW && col + 1 < MAX_COL&&mine_map[row + 1][col + 1] == '1') {
		number++;
	}
	return number;


}
void PrintMap(char show_map[][MAX_COL], char mine_map[][MAX_COL]) {
	printf(" |0 1 2 3 4 5 6 7 8 \n");
	printf("--------------------\n");
	for (int row = 0; row < MAX_ROW; row++) {
		printf("%d|", row);
		for (int col = 0; col < MAX_COL; col++) {
			printf("%c ", show_map[row][col]);
		}
		printf("\n");
	}
    printf("\n");
/*	printf(" |0 1 2 3 4 5 6 7 8 \n");
	printf("--------------------\n");
		for (int row = 0; row < MAX_ROW; row++) {
			printf("%d|",row);
			for (int col = 0; col < MAX_COL; col++) {
			printf("%c ", mine_map[row][col]);
			}
			printf("\n");
		}
		*/
}
char PlayInput(char show_map[][MAX_COL], char mine_map[][MAX_COL], int *x) {
	int row, col;
	printf("请输入您要掀开的位置:格式为 x,y\n");

	while (1) {
		scanf("%d,%d", &row, &col);
		while ('\0' == getchar());
		if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL) {
			printf("您的输入有误,请重新输入:\n");
			continue;
		}
		else if (show_map[row][col] != '*') {
			printf("该位置已经被掀开,请重新输入\n");
		}
		if (mine_map[row][col] == '1') {
			return mine_map[row][col];
		}
		show_map[row][col] = UpdateShowmap(row, col, mine_map) + '0';
		break;
	}
	return '0';
}
//1代表游戏结束
int IsGameOver(char x) {
	if (x == '1') {
		return 1;
	}
}
 void printWinmap( char mine_map[MAX_ROW][MAX_COL]) {
	 printf(" |0 1 2 3 4 5 6 7 8 \n");
	 printf("--------------------\n");
	 for (int row = 0; row < MAX_ROW; row++) {
		 printf("%d|", row);
		 for (int col = 0; col < MAX_COL; col++) {
			 printf("%c ", mine_map[row][col]);
		 }
		 printf("\n");
	 }
}
//1.用两个二维数组,一个用来表示翻开和为翻开, 翻开为数字,未翻开未*;这个是玩家能看见,

//另外一个地雷和不是地雷的状态.这个只能电脑能看见.

				 //4.先判断是否踩雷了,如果踩了就gameover 
				 //5如果没踩就判断是否游戏胜利,

				 //否者显示这个地方周围类的数量.

void game() {
	int blank_count = 0;
	char show_map[MAX_ROW][MAX_COL];
	char mine_map[MAX_ROW][MAX_COL];
	//1.初始化地图,show_map全部初始化为*,而mine_map先初始化为0,然后随机生成10个随机数.地雷用1来表示.
	Initarray(show_map, mine_map);
	//2.打印玩家可视地图.
	PrintMap(show_map, mine_map);

	while (1) {
		char ch;
		//3.输入坐标,判断输入的位置是否合法(包括是否超出范围或者这个位置是否已经被掀开,)掀开show_map上的相对位置,
		ch = PlayInput(show_map, mine_map, &blank_count);
		system("cls");
		
		PrintMap(show_map, mine_map);

		if (IsGameOver(ch) == 1) {
			printf("游戏失败,你真菜\n");
			printWinmap(mine_map);
			break;
		}
		if (blank_count == MAX_ROW * MAX_COL - MINE_COUNT) {
			printf("恭喜你,扫雷成功\n");
			

			break;
		}



	}
}
int main() {

	int x;
	while (1) {
		x = menu();


		if (x == 1) {
			system("cls");
			game();

		}
		else if (x == 0) {
			break;
		}
		else {
			printf("您的输入有误,请重新输入\n");

		}
	}
	system("pause");
	return 0;

}

