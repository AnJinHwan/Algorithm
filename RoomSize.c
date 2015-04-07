/*******************************************************
*     		       ���� ũ�� ���ϱ�	                   *
*******************************************************/

/*******************************************************  
*    ���δ��б� ����������Ŵ��� ��ǻ�Ͱ��к� 3�г�    *
*                                     20123426 ������  *
*******************************************************/

#include <stdio.h>
#include <stdlib.h>

int cover(char **dptr, int row, int col, int *roomSizeArr);
void check(char **dptr, int startRow, int startCol, int row, int col);
void sort(int *roomSizeArr, int start, int end);
int part(int *roomSizeArr, int start, int end);
void swap(int *roomSizeArr, int start, int end);

int roomSize = 0;	// �� �� ���� ũ��
int roomNum = 0;	// ���� ����

void main(void)
{
	FILE *file;
	int i, nocase;
	
	file = fopen("input.txt", "r");
	if(file == NULL) 
		exit(1);

	fscanf(file, "%d", &nocase);

	for(i=0; i<nocase; i++)
	{
		int *roomSizeArr = (int *)malloc(sizeof(int)*100);	// �׽�Ʈ���̽� �ϳ� �� ����� ũ�⸦ ���� �迭
		int i, j;
		int row, col;
		char **dptr = NULL;
		roomNum = 0; 

		fscanf(file, "%d %d\n", &col, &row);	// ������ ����(���� ����), ������ ����(���� ����)�� �Է� ����
		dptr = (char **)malloc(sizeof(char*)*row);

		for(i = 0; i < row; i++) {
			dptr[i] = (char *)malloc(sizeof(char)*(col+1));
			for(j = 0; j < col+1; j++) {
				fscanf(file, "%c", &dptr[i][j]);	// �� ����� �ǹ��ϴ� 2���� �迭�� �Է� ����
			}
		}
		
		while(1) {
			if(!cover(dptr, row, col, roomSizeArr))	// ���� ������ ũ�⸦ ����
				break;
		}

		sort(roomSizeArr, 0, roomNum-1);		// ���� ũ�� ������������ ����
		
		printf("%d\n", roomNum);	// ���� ���� ���

		for(i = 0; i < roomNum; i++)
			printf("%d ", roomSizeArr[i]);	// ���� ũ�� ���
		printf("\n");
		
		for(i = 0; i < row; i++)
			free(dptr[i]);

		free(dptr);
		free(roomSizeArr);
	}
	
	fclose(file);
}

int cover(char **dptr, int row, int col, int *roomSizeArr) {
	int i, j;
	int found = 0;
	int startRow, startCol;
	roomSize = 0;

	for(i = 1; i < row-1; i++) {		
		for(j = 1; j < col-1; j++) {	
			if(dptr[i][j] == '.') {	// �� ������ ������
				startRow = i, startCol = j;	// startRow, startCol�� ���
				found = 1;	// �� ������ �־��ٴ� flag ǥ��
				break;
			}
		}
		if(found)	// flag�� �̿��� for�� Ż��
			break;
	}

	if(!found)		// �� ������ ������
		return 0;	// return

	check(dptr, startRow, startCol, row, col);	// �� ������ Ȯ���ϰ� ���İ��ٴ� ǥ�ø� �ϴ� ��� �Լ�

	roomNum++;	// �� �ϳ��� Ȯ��(ũ�⸦ ���ϰ� �� ������ ǥ��)�ϸ� ���� ���� 1 ����

	roomSizeArr[roomNum-1] = roomSize;	// �� ũ�� �迭�� �� ũ�� ����
	
	return 1;
}

void check(char **dptr, int startRow, int startCol, int row, int col) {
	int i, j;

	if(dptr[startRow][startCol]=='.') {	// ���� ��ǥ�� �� �����̶��
		dptr[startRow][startCol] = '*';	// ǥ�ø� �ϰ�
		roomSize++;						// �� ũ�⸦ 1 ������Ŵ
	}
	
	if(dptr[startRow-1][startCol]!='.' && dptr[startRow+1][startCol]!='.' && dptr[startRow][startCol-1]!='.' && dptr[startRow][startCol+1]!='.')
		return;	// ����� �̹� ������ ��ǥ��� return
	
	if(startCol >= 2)
		if(dptr[startRow][startCol-1]=='.')		// �ٷ� ���� ĭ�� ���� ��� �Լ� ȣ��
			check(dptr, startRow, startCol-1, row, col);

	if(startCol <= col-2)
		if(dptr[startRow][startCol+1]=='.')		// �ٷ� ������ ĭ�� ���� ��� �Լ� ȣ��
			check(dptr, startRow, startCol+1, row, col);

	if(startRow >= 2)
		if(dptr[startRow-1][startCol]=='.')		// �ٷ� �� ĭ�� ���� ��� �Լ� ȣ��
			check(dptr, startRow-1, startCol, row, col);

	if(startRow <= row-2)
		if(dptr[startRow+1][startCol]=='.')		// �ٷ� �Ʒ� ĭ�� ���� ��� �Լ� ȣ��
			check(dptr, startRow+1, startCol, row, col);
}

void sort(int *roomSizeArr, int start, int end) {	// ������ �Լ�
	if(start < end) {
		int index = part(roomSizeArr, start, end);
		sort(roomSizeArr, start, index - 1);
		sort(roomSizeArr, index + 1, end);
	}
}

int part(int *roomSizeArr, int start, int end) {	// �������� ���� �ǹ��� ã�� �Լ�
	int first = start;
	int pivot = roomSizeArr[first];

	start++;

	while(start <= end) {
		while(roomSizeArr[start] >= pivot && start < end)
			start++;

		while(roomSizeArr[end] < pivot && start <= end)
			end--;

		if(start < end)
			swap(roomSizeArr, start, end);
		else
			break;
	}

	swap(roomSizeArr, first, end);

	return end;
}

void swap(int *roomSizeArr, int start, int end) {	// ���� �Լ�
	int temp = roomSizeArr[start];
	roomSizeArr[start] = roomSizeArr[end];
	roomSizeArr[end] = temp;
}