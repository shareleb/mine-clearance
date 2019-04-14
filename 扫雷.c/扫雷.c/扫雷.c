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
	printf("����������ѡ��>: ");
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
	printf("��������Ҫ�ƿ���λ��:��ʽΪ x,y\n");

	while (1) {
		scanf("%d,%d", &row, &col);
		while ('\0' == getchar());
		if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL) {
			printf("������������,����������:\n");
			continue;
		}
		else if (show_map[row][col] != '*') {
			printf("��λ���Ѿ����ƿ�,����������\n");
		}
		if (mine_map[row][col] == '1') {
			return mine_map[row][col];
		}
		show_map[row][col] = UpdateShowmap(row, col, mine_map) + '0';
		break;
	}
	return '0';
}
//1������Ϸ����
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
//1.��������ά����,һ��������ʾ������Ϊ����, ����Ϊ����,δ����δ*;���������ܿ���,

//����һ�����׺Ͳ��ǵ��׵�״̬.���ֻ�ܵ����ܿ���.

				 //4.���ж��Ƿ������,������˾�gameover 
				 //5���û�Ⱦ��ж��Ƿ���Ϸʤ��,

				 //������ʾ����ط���Χ�������.

void game() {
	int blank_count = 0;
	char show_map[MAX_ROW][MAX_COL];
	char mine_map[MAX_ROW][MAX_COL];
	//1.��ʼ����ͼ,show_mapȫ����ʼ��Ϊ*,��mine_map�ȳ�ʼ��Ϊ0,Ȼ���������10�������.������1����ʾ.
	Initarray(show_map, mine_map);
	//2.��ӡ��ҿ��ӵ�ͼ.
	PrintMap(show_map, mine_map);

	while (1) {
		char ch;
		//3.��������,�ж������λ���Ƿ�Ϸ�(�����Ƿ񳬳���Χ�������λ���Ƿ��Ѿ����ƿ�,)�ƿ�show_map�ϵ����λ��,
		ch = PlayInput(show_map, mine_map, &blank_count);
		system("cls");
		
		PrintMap(show_map, mine_map);

		if (IsGameOver(ch) == 1) {
			printf("��Ϸʧ��,�����\n");
			printWinmap(mine_map);
			break;
		}
		if (blank_count == MAX_ROW * MAX_COL - MINE_COUNT) {
			printf("��ϲ��,ɨ�׳ɹ�\n");
			

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
			printf("������������,����������\n");

		}
	}
	system("pause");
	return 0;

}

