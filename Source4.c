#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

int former_Coordinate_x, former_Coordinate_y;
int *trimmer = 1;
double *score;


void number_to_array(int** p, int a, int b, int c, int d, int e, int f, int g, int h)
{
	p[0][0] = a;
	p[0][1] = b;
	p[1][0] = c;
	p[1][1] = d;
	p[2][0] = e;
	p[2][1] = f;
	p[3][0] = g;
	p[3][1] = h;
}
void base_rectangle(char** a)
{
	
}
void show_graphic(char*** a)
{
	int i, j;
	for (i = 0; i < 30; i++)
	{
		for (j = 0; j < 30; j++)
		{
			printf("%s", a[i][j]);
		}
		if(i!=29)
		printf("\n");
	}
}
int arrow(char key)
{
	switch (key)
	{
	case 72:
		return 2;
	case 75:
		return 3;
	case 77:
		return 1;
	case 80:
		return 0;
	default:
		return -1;
	}
}
int check_piles(char*** c, int** v, int a, int b)
{
	int i,j, temp_i, temp_j;
	int *former_temp_i, *former_temp_j;
	former_temp_i=(int*)malloc(sizeof(int)*4);
	former_temp_j = (int*)malloc(sizeof(int) * 4);
	for (i = 0; i < 4; i++)
	{
		temp_i = a + v[i][0];
		temp_j = b + v[i][1];
		
		if (c[temp_i][temp_j] == "▤")
		{
			return 0;
		}
		former_temp_i[i] = temp_i;
		former_temp_j[i] = temp_j;
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (former_temp_j[j] == former_temp_j[i]) {
				if (former_temp_i[j] > former_temp_i[i])
					former_temp_i[i] = former_temp_i[j];
			}
		}
	}
	for (i = 0; i < 4; i++)
	{
		if (c[former_temp_i[i]][former_temp_j[i]] == "■")
		{
			return 0;
		}
	}
	return 1;
}
int check_edge(char*** c, int** v, int a, int b)
{
	int i, temp_i, temp_j;

	for (i = 0; i < 4; i++)
	{
		temp_i = a + v[i][0];
		temp_j = b + v[i][1];

	if (c[temp_i][temp_j+1] == "▧")
		return 1;
	if (c[temp_i][temp_j-1] == "▨") 
		return 2;
	}
	return 0;
}

int coordinated_edge_left(char*** c, int** v, int a, int b)
{
	int i, j, temp_i, temp_j;

	int* former_temp_i, * former_temp_j;
	former_temp_i = (int*)malloc(sizeof(int) * 4);
	former_temp_j = (int*)malloc(sizeof(int) * 4);

	for (i = 0; i < 4; i++)
	{
		temp_i = a + v[i][0];
		temp_j = b + v[i][1];

		former_temp_i[i] = temp_i;
		former_temp_j[i] = temp_j;
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (former_temp_i[i] == former_temp_i[j]) {
				if (former_temp_j[j] < former_temp_j[i])
					former_temp_j[i] = former_temp_j[j];
			}
		}
	}
	for (i = 0; i < 4; i++)
	{
		if (c[former_temp_i[i]][former_temp_j[i] - 1] == "■")
		{
			return 1;
		}
	}
	return 0;
}
int coordinated_edge_right(char*** c, int** v, int a, int b)
{
	int i, j,temp_i, temp_j;

	int* former_temp_i, * former_temp_j;
	former_temp_i = (int*)malloc(sizeof(int) * 4);
	former_temp_j = (int*)malloc(sizeof(int) * 4);

	for (i = 0; i < 4; i++)
	{
		temp_i = a + v[i][0];
		temp_j = b + v[i][1];

		former_temp_i[i] = temp_i;
		former_temp_j[i] = temp_j;
	}
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++)
		{
			if (former_temp_i[i] == former_temp_i[j])
			{
				if (former_temp_j[j] > former_temp_j[i])
					former_temp_j[i] = former_temp_j[j];
			}
		}
	}
	for (i = 0; i < 4; i++)
	{
		if (c[former_temp_i[i]][former_temp_j[i] + 1] == "■")
		{
			return 1;
		}
	}
	return 0;
}


void put_block(char*** c, int** v, int a, int b)
{
	int i, temp_i, temp_j;
	for (i = 0; i < 4; i++)
	{
		temp_i = a + v[i][0];
		temp_j = b + v[i][1];
		if(temp_i>trimmer)c[temp_i][temp_j] = "■";
	}
}
void put_block_rm(char*** c, int** v, int a, int b)
{
	int i, temp_i, temp_j;
	for (i = 0; i < 4; i++)
	{
		temp_i = a + v[i][0];
		temp_j = b + v[i][1];
		if (temp_i > trimmer)c[temp_i][temp_j] = "  ";
	}
}
void blocktype_to_coordinate(int** p, int blocktype, int spinvalue)
{
	switch (blocktype)
	{
	case 0:
		switch (spinvalue)
		{
		case 0:
			number_to_array(p, -1, 0, 0, 0, 1, 0, 2, 0);
			return;
		case 1:
			number_to_array(p, 0, -1, 0, 0, 0, 1, 0, 2);
			return;
		case 2:
			number_to_array(p, -1, 0, 0, 0, 1, 0, 2, 0);
			return;
		case 3:
			number_to_array(p, 0, -1, 0, 0, 0, 1, 0, 2);
			return;
		}
	case 1:
		switch (spinvalue)
		{
		case 0:
			number_to_array(p, -1, -1, 0, -1, 0, 0, 0, 1);
			return;
		case 1:
			number_to_array(p, -1, 0, 0, 0, 1, 0, 1, -1);
			return;
		case 2:
			number_to_array(p, 0, -1, 0, 0, 0, 1, 1, 1);
			return;
		case 3:
			number_to_array(p, -1, 0, -1, 1, 0, 0, 1, 0);
			return;
		}
	case 2:
		switch (spinvalue)
		{
		case 0:
			number_to_array(p, 0, -1, 0, 0, 0, 1, -1, 1);
			return;
		case 1:
			number_to_array(p, -1, -1, -1, 0, 0, 0, 1, 0);
			return;
		case 2:
			number_to_array(p, 1, -1, 0, -1, 0, 0, 0, 1);
			return;
		case 3:
			number_to_array(p, -1, 0, 0, 0, 1, 0, 1, 1);
			return;
		}
	case 3:
		switch (spinvalue)
		{
		case 0:
			number_to_array(p, -1, 0, 0, 0, 0, 1, 1, 1);
			return;
		case 1:
			number_to_array(p, 0, -1, 0, 0, -1, 0, -1, 1);
			return;
		case 2:
			number_to_array(p, -1, 0, 0, 0, 0, 1, 1, 1);
			return;
		case 3:
			number_to_array(p, 0, -1, 0, 0, -1, 0, -1, 1);
			return;
		}
	case 4:
		switch (spinvalue)
		{
		case 0:
			number_to_array(p, 0, 0, 0, 1, -1, 1, 1, 0);
			return;
		case 1:
			number_to_array(p, -1, -1, -1, 0, 0, 0, 0, 1);
			return;
		case 2:
			number_to_array(p, 0, 0, 0, 1, -1, 1, 1, 0);
			return;
		case 3:
			number_to_array(p, -1, -1, -1, 0, 0, 0, 0, 1);
			return;
		}
	case 5:
		switch (spinvalue)
		{
		case 0:
			number_to_array(p, 0, 0, 0, 1, 1, 0, 1, 1);
			return;
		case 1:
			number_to_array(p, 0, 0, 0, 1, 1, 0, 1, 1);
			return;
		case 2:
			number_to_array(p, 0, 0, 0, 1, 1, 0, 1, 1);
			return;
		case 3:
			number_to_array(p, 0, 0, 0, 1, 1, 0, 1, 1);
			return;
		}
	
	}

}

void check_line(char*** a)
{
	int i, j,t,p;
	for (i = 2; i < 28; i++)
	{
		if ((a[i][10] == "■") && (a[i][11] == "■") && (a[i][12] == "■")
			&& (a[i][13] == "■") && (a[i][14] == "■") && (a[i][15] == "■")
			&& (a[i][16] == "■") && (a[i][17] == "■") && (a[i][18] == "■") && (a[i][19] == "■"))
		{
			for (j = 10; j < 20; j++)
			{
				a[i][j] = "▣";
			}

			for (j = 10; j < 20; j++)
			{
				a[i][j] = "  ";
			}
			for (j = 10; j < 20; j++)
			{
				for (t = i; t > 2; t--)
				{
					a[t][j] = a[t - 1][j];
				}
			}
			score=score+1;
		}
	}
}

int main(int argc, char** argv)
{
	int i = 0, j = 0;

	char*** graphic; // 문자열을 원소로 갖는 2차원 배열
	int** block_Coordinate; // 블록 좌표
	int* location;
	clock_t start;
	score = 0;

	/*graphic 동적할당*/
	graphic = (char**)malloc(sizeof(char*) * 30); //30개의 열 확보
	if (graphic== NULL)return -1;
	for (i = 0; i < 30; i++) {
		graphic[i] = (char**)malloc(sizeof(char*) * 30); //30개의 행 확보
		if (graphic[i] == NULL)return -1;
	}
		
	/*블럭 좌표 동적할당*/
	block_Coordinate = (int**)malloc(sizeof(int*) * 4);
	if (block_Coordinate == NULL)return -1;
	for (i = 0; i < 4; i++) {
		block_Coordinate[i] = (int*)malloc(sizeof(int) * 2);
		if (block_Coordinate[i] == NULL)return -1;
	}
		
	/*위치 관련 동적 할당*/
	location = (int*)malloc(sizeof(int) * 2);
	if (location == NULL) return -1;

	/*    기본세팅    */
	for (i = 0; i < 30; i++)
	{
		for (j = 0; j < 30; j++)
		{

			if (i == 1 && (j > 8 && j < 21))graphic[i][j] = "▥";
			else if (i == 28 && (j > 8 && j < 21))graphic[i][j] = "▤";
			else if (j == 9 && (i > 1 && i < 28))graphic[i][j] = "▨"; 
			else if (j == 20 && (i > 1 && i < 28))graphic[i][j] = "▧";

			else
			graphic[i][j] = "  ";
		}
	}
	location[0] = 1;
	location[1] = 14;
	
	srand(time(NULL));
	int blocktype = rand()%6;
	int spinvalue = rand() % 4;
	blocktype_to_coordinate(block_Coordinate, blocktype, spinvalue);
	//if (location[0] > 2)
	put_block(graphic, block_Coordinate, location[0], location[1]);


	show_graphic(graphic);

	//방향 키 설정
	char t=0;
	start = clock();
	
	while (1)
	{
		
		if (_kbhit()) 
		{
			t = _getch();
			if (t == 32)
			{
				system("cls");
				int test_val = check_piles(graphic, block_Coordinate, location[0] + 1, location[1]);
				if (test_val != 0)
				{
					put_block_rm(graphic, block_Coordinate, location[0], location[1]);
					blocktype_to_coordinate(block_Coordinate, blocktype, block_Coordinate);
					location[0]++;
					put_block(graphic, block_Coordinate, location[0], location[1]);
					show_graphic(graphic);
				}
				else
					show_graphic(graphic);
			}
			if (t == -32) 
			{
				t = _getch();
				system("cls");
				int test_block = check_edge(graphic, block_Coordinate, location[0], location[1]);

				if ((arrow(t) == 3))
				{	
					if(test_block==0||test_block == 1)
					{
						//왼쪽에 네모가 있는지 확인하는 함수
						int check_1 = coordinated_edge_left(graphic, block_Coordinate, location[0], location[1]);
						if (check_1 == 0)
						{
							put_block_rm(graphic, block_Coordinate, location[0], location[1]);
							location[1]--;
							put_block(graphic, block_Coordinate, location[0], location[1]);
						}
					} 
				}
				if ((arrow(t) == 1))
				{
					if (test_block == 0 || test_block == 2)
					{
						//오른쪽에 네모가 있는지 확인하는 함수
						int check_2 = coordinated_edge_right(graphic, block_Coordinate, location[0], location[1]);
						if (check_2 == 0)
						{
							put_block_rm(graphic, block_Coordinate, location[0], location[1]);
							location[1]++;
							put_block(graphic, block_Coordinate, location[0], location[1]);
						}
					}
				}
				if ((arrow(t) == 2))
				{
					if (test_block == 0)
					{
						//블럭이 변할 조건
						int check_1 = coordinated_edge_left(graphic, block_Coordinate, location[0], location[1]);
						int check_2 = coordinated_edge_right(graphic, block_Coordinate, location[0], location[1]);
						if ((check_1 == 0)&&(check_2==0))
						{
							if (spinvalue < 3)spinvalue++;
							else
								spinvalue = 0;


							put_block_rm(graphic, block_Coordinate, location[0], location[1]);
							blocktype_to_coordinate(block_Coordinate, blocktype, spinvalue);
							put_block(graphic, block_Coordinate, location[0], location[1]);
						}
					}
				}
				show_graphic(graphic);
			}
		}
		if ((clock() - start) >100)
		{
			start = clock();
			
			system("cls");
			int test_val = check_piles(graphic, block_Coordinate, location[0]+1, location[1]);
			if (test_val != 0)
			{
				put_block_rm(graphic, block_Coordinate, location[0], location[1]);
				blocktype_to_coordinate(block_Coordinate, blocktype, block_Coordinate);
				location[0]++;
				put_block(graphic, block_Coordinate, location[0], location[1]);
			}
			else if(test_val==0)
			{

				check_line(graphic);
				location[0] = 1;
				location[1] = 14;
				srand(time(NULL));
				blocktype = rand() % 6;
				spinvalue = rand() % 4;
				blocktype_to_coordinate(block_Coordinate, blocktype, spinvalue);
				put_block(graphic, block_Coordinate, location[0], location[1]);
			}
			show_graphic(graphic);
		}
	}
	return 0;
}