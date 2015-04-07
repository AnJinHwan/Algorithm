/************************************************************************
*																		*
*  Problem 7 : Order													*
*																		*
************************************************************************/
/************************************************************************
*	전자정보통신대학 컴퓨터공학부 3학년		CLC팀						*
*	20103378 임종호, 20103389 최원범, 20123426 최진성					* 
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNUM 100 // 최대 집합의 크기

void EnterData(FILE** in_file, int R[MAXNUM], int S[MAXNUM], int* num); // Data 입력
int Order(int R[MAXNUM], int S[MAXNUM], int num, int minimum, int maxidx); // 집합 S를 출력

int main()
{
	FILE* in_file; 
	int test_case; // test case 수
	
	in_file = fopen("input.txt", "r"); // 파일 열기
	/* 에러처리 */
	if(in_file == NULL) {
		printf("file open error\n");
		exit(1);
	}

	fscanf(in_file, "%d ", &test_case); // test case 개수 입력
	while(test_case--) {
		int S[MAXNUM];			// S 집합에 들어가는 1~n 숫자
		int R[MAXNUM];			// R 집합
		int num;				// 집합의 크기

		EnterData(&in_file, R, S, &num); // Data 입력
		if(Order(R, S, num, 0, num)==-1) // 집합을 찾아서 출력 불가능하면 IMPOSSIBLE 출력
			printf("IMPOSSIBLE");
		printf("\n");
	}
}
/****************************************************
*	데이터들을 입력받는 함수						*
****************************************************/
void EnterData(FILE** in_file, int R[MAXNUM], int S[MAXNUM], int* num)
{
	int i=0;
	
	fscanf(*in_file, "%d ", num); // 집합의 크기 입력
	/* 집합 입력 */
	for(i=0; i<(*num); i++) {
		fscanf(*in_file, "%d ", &R[i]);
		S[i] = i+1;
	}		
}
/************************************************************
*	집합S를 찾아 출력하는 함수								*
*	배열S에 1~maxidx 까지의 숫자가 들어있다. (1~n)			*
*	배열S에 숫자를 사용하면 minimum이 1증가하고				*
*	사용한 숫자는 0으로 만들어 배열의 맨 왼쪽으로 보낸다	*
*	집합S를 만드는것이 불가능하면 -1 반환					*
************************************************************/
int Order(int R[MAXNUM], int S[MAXNUM], int num, int minimum, int maxidx) 
{
	int res, small; // 결과, 원래집합S(num-1) 보다 작은 수의 개수

	if(num<=0) {
		if(S[maxidx-1]!=0) {
			return -1;
		}
		else
			return 0;
	}

	small = R[--num]; // 작은 수 개수 입력
	/* R이 잘못 입력된 경우 남아 있는 배열S의 최소 idx인 */
	/* minimum과 작은 수의 개수의 합이 배열의 크기를 넘으면 잘못 됨 */
	if(small+minimum >= maxidx)
		return -1;

	res = S[small+minimum]; // 집합S에 출력 될 수 입력

	/* S에서 수 하나를 사용했으므로 0으로 만들고 맨 왼쪽으로 보냄 */
	memmove(&S[1], &S[0], sizeof(S[0])*(small+minimum)); // 사용한 수의 왼쪽 배열들을 오른쪽으로 한칸 밀고
	S[0]=0; // 맨 왼쪽에 0 입력

	/* reculsive */
	if(!Order(R, S, num, minimum+1, maxidx))
	{
		printf("%d ", res);
		return 0;
	}
	else
		return -1;
}