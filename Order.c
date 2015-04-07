/************************************************************************
*																		*
*  Problem 7 : Order													*
*																		*
************************************************************************/
/************************************************************************
*	����������Ŵ��� ��ǻ�Ͱ��к� 3�г�		CLC��						*
*	20103378 ����ȣ, 20103389 �ֿ���, 20123426 ������					* 
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNUM 100 // �ִ� ������ ũ��

void EnterData(FILE** in_file, int R[MAXNUM], int S[MAXNUM], int* num); // Data �Է�
int Order(int R[MAXNUM], int S[MAXNUM], int num, int minimum, int maxidx); // ���� S�� ���

int main()
{
	FILE* in_file; 
	int test_case; // test case ��
	
	in_file = fopen("input.txt", "r"); // ���� ����
	/* ����ó�� */
	if(in_file == NULL) {
		printf("file open error\n");
		exit(1);
	}

	fscanf(in_file, "%d ", &test_case); // test case ���� �Է�
	while(test_case--) {
		int S[MAXNUM];			// S ���տ� ���� 1~n ����
		int R[MAXNUM];			// R ����
		int num;				// ������ ũ��

		EnterData(&in_file, R, S, &num); // Data �Է�
		if(Order(R, S, num, 0, num)==-1) // ������ ã�Ƽ� ��� �Ұ����ϸ� IMPOSSIBLE ���
			printf("IMPOSSIBLE");
		printf("\n");
	}
}
/****************************************************
*	�����͵��� �Է¹޴� �Լ�						*
****************************************************/
void EnterData(FILE** in_file, int R[MAXNUM], int S[MAXNUM], int* num)
{
	int i=0;
	
	fscanf(*in_file, "%d ", num); // ������ ũ�� �Է�
	/* ���� �Է� */
	for(i=0; i<(*num); i++) {
		fscanf(*in_file, "%d ", &R[i]);
		S[i] = i+1;
	}		
}
/************************************************************
*	����S�� ã�� ����ϴ� �Լ�								*
*	�迭S�� 1~maxidx ������ ���ڰ� ����ִ�. (1~n)			*
*	�迭S�� ���ڸ� ����ϸ� minimum�� 1�����ϰ�				*
*	����� ���ڴ� 0���� ����� �迭�� �� �������� ������	*
*	����S�� ����°��� �Ұ����ϸ� -1 ��ȯ					*
************************************************************/
int Order(int R[MAXNUM], int S[MAXNUM], int num, int minimum, int maxidx) 
{
	int res, small; // ���, ��������S(num-1) ���� ���� ���� ����

	if(num<=0) {
		if(S[maxidx-1]!=0) {
			return -1;
		}
		else
			return 0;
	}

	small = R[--num]; // ���� �� ���� �Է�
	/* R�� �߸� �Էµ� ��� ���� �ִ� �迭S�� �ּ� idx�� */
	/* minimum�� ���� ���� ������ ���� �迭�� ũ�⸦ ������ �߸� �� */
	if(small+minimum >= maxidx)
		return -1;

	res = S[small+minimum]; // ����S�� ��� �� �� �Է�

	/* S���� �� �ϳ��� ��������Ƿ� 0���� ����� �� �������� ���� */
	memmove(&S[1], &S[0], sizeof(S[0])*(small+minimum)); // ����� ���� ���� �迭���� ���������� ��ĭ �а�
	S[0]=0; // �� ���ʿ� 0 �Է�

	/* reculsive */
	if(!Order(R, S, num, minimum+1, maxidx))
	{
		printf("%d ", res);
		return 0;
	}
	else
		return -1;
}