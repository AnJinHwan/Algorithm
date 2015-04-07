/*******************************************************
*     		       방의 크기 구하기	                   *
*******************************************************/

/*******************************************************  
*    국민대학교 전자정보통신대학 컴퓨터공학부 3학년    *
*                                     20123426 최진성  *
*******************************************************/

#include <stdio.h>
#include <stdlib.h>

int cover(char **dptr, int row, int col, int *roomSizeArr);
void check(char **dptr, int startRow, int startCol, int row, int col);
void sort(int *roomSizeArr, int start, int end);
int part(int *roomSizeArr, int start, int end);
void swap(int *roomSizeArr, int start, int end);

int roomSize = 0;	// 방 한 개당 크기
int roomNum = 0;	// 방의 갯수

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
		int *roomSizeArr = (int *)malloc(sizeof(int)*100);	// 테스트케이스 하나 당 방들의 크기를 담을 배열
		int i, j;
		int row, col;
		char **dptr = NULL;
		roomNum = 0; 

		fscanf(file, "%d %d\n", &col, &row);	// 가로의 길이(열의 갯수), 세로의 길이(행의 갯수)를 입력 받음
		dptr = (char **)malloc(sizeof(char*)*row);

		for(i = 0; i < row; i++) {
			dptr[i] = (char *)malloc(sizeof(char)*(col+1));
			for(j = 0; j < col+1; j++) {
				fscanf(file, "%c", &dptr[i][j]);	// 방 모양을 의미하는 2차원 배열을 입력 받음
			}
		}
		
		while(1) {
			if(!cover(dptr, row, col, roomSizeArr))	// 방의 갯수와 크기를 구함
				break;
		}

		sort(roomSizeArr, 0, roomNum-1);		// 방의 크기 내림차순으로 정렬
		
		printf("%d\n", roomNum);	// 방의 갯수 출력

		for(i = 0; i < roomNum; i++)
			printf("%d ", roomSizeArr[i]);	// 방의 크기 출력
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
			if(dptr[i][j] == '.') {	// 빈 공간이 있으면
				startRow = i, startCol = j;	// startRow, startCol에 담고
				found = 1;	// 빈 공간이 있었다는 flag 표시
				break;
			}
		}
		if(found)	// flag를 이용해 for문 탈출
			break;
	}

	if(!found)		// 빈 공간이 없으면
		return 0;	// return

	check(dptr, startRow, startCol, row, col);	// 빈 공간을 확인하고 거쳐갔다는 표시를 하는 재귀 함수

	roomNum++;	// 방 하나를 확인(크기를 구하고 빈 공간에 표시)하면 방의 갯수 1 증가

	roomSizeArr[roomNum-1] = roomSize;	// 방 크기 배열에 방 크기 저장
	
	return 1;
}

void check(char **dptr, int startRow, int startCol, int row, int col) {
	int i, j;

	if(dptr[startRow][startCol]=='.') {	// 현재 좌표가 빈 공간이라면
		dptr[startRow][startCol] = '*';	// 표시를 하고
		roomSize++;						// 방 크기를 1 증가시킴
	}
	
	if(dptr[startRow-1][startCol]!='.' && dptr[startRow+1][startCol]!='.' && dptr[startRow][startCol-1]!='.' && dptr[startRow][startCol+1]!='.')
		return;	// 사방이 이미 지났던 좌표라면 return
	
	if(startCol >= 2)
		if(dptr[startRow][startCol-1]=='.')		// 바로 왼쪽 칸에 대해 재귀 함수 호출
			check(dptr, startRow, startCol-1, row, col);

	if(startCol <= col-2)
		if(dptr[startRow][startCol+1]=='.')		// 바로 오른쪽 칸에 대해 재귀 함수 호출
			check(dptr, startRow, startCol+1, row, col);

	if(startRow >= 2)
		if(dptr[startRow-1][startCol]=='.')		// 바로 위 칸에 대해 재귀 함수 호출
			check(dptr, startRow-1, startCol, row, col);

	if(startRow <= row-2)
		if(dptr[startRow+1][startCol]=='.')		// 바로 아래 칸에 대해 재귀 함수 호출
			check(dptr, startRow+1, startCol, row, col);
}

void sort(int *roomSizeArr, int start, int end) {	// 퀵정렬 함수
	if(start < end) {
		int index = part(roomSizeArr, start, end);
		sort(roomSizeArr, start, index - 1);
		sort(roomSizeArr, index + 1, end);
	}
}

int part(int *roomSizeArr, int start, int end) {	// 퀵정렬을 위해 피벗을 찾는 함수
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

void swap(int *roomSizeArr, int start, int end) {	// 스왑 함수
	int temp = roomSizeArr[start];
	roomSizeArr[start] = roomSizeArr[end];
	roomSizeArr[end] = temp;
}