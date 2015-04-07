/************************************************************************
*																		*
*  Problem 8 : Parenthesis (괄호)										*
*																		*
************************************************************************/
/************************************************************************
*	전자정보통신대학 컴퓨터공학부 3학년	 		팀 CLC					*
*	20103378 임종호, 20103389 최원범, 20123426 최진성					* 
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define PARMAX 51
#define STACKMAX 25

void EnterRoom(FILE** in_file, char par[]);
int isParenthesis(char par[]);
void PrintVaild(int n);

int main()
{
	FILE* in_file; // 입력 file의 정보를 받을 구조체 포인터
	int test_case; // test_case의 개수
	
	in_file = fopen("input.txt","r"); // 파일 열기
	/* file open fail */
	if(in_file == NULL) {
		printf("cannot open the file\n");
		exit(1);
	}

	fscanf(in_file, "%d", &test_case); // test_case 개수 입력
	while(test_case--) {
		char par[PARMAX] = {0};

		EnterRoom(&in_file, par);
		PrintVaild(isParenthesis(par));
	}
	fclose(in_file);

	return 0;
}
/************************************************************
* 괄호 String을 입력받는 함수								*
************************************************************/
void EnterRoom(FILE** in_file, char par[]) {
	/* 괄호 입력 */
	fscanf(*in_file, "%s ", par);
}
/****************************************************************
* 괄호가 정확한지를 검사하는 함수								*
* 정확하지 않으면 -1, 정확하면 0 반환						    *
****************************************************************/
int isParenthesis(char par[]) {
	char stack[STACKMAX] = {0}; // 스택 (스택을 사용하지 않아도 됨)
	int pStack=0;		  // 스택 인덱스 포인터
	int i;

	/* '(' 일때는 스택에 넣고 ')'일 때는 스택에서 (를 뺀다 */
	for(i=0; par[i]!='\0'; i++)
	{
		if(par[i]=='(') {
			// 스택이 꽉 차있는곳에 '('이 또 들어오면 잘못 됨.
			if(pStack==STACKMAX)
				return -1;
			stack[pStack++] = '('; // 스택에 집어넣는다.
		}
		else {
			// 스택이 비었는데 ')'가 나오면 잘못 됨
			if(pStack == 0)
				return -1;
			else 
				stack[--pStack] = 0; // 스택에서 '('를 뺀다.
		}
	}
	// 루프를 끝나고 스택이 빈 상태면 정상, 스택이 비어있지 않으면 잘못 됨.
	if(pStack == 0)
		return 0;  
	else 
		return -1;
}
/****************************************
*	괄호가 정상인지 출력				*
****************************************/
void PrintVaild(int n) {
	if(n==0)
		printf("%s\n", "YES");
	else
		printf("%s\n", "NO");
}