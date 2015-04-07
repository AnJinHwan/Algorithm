/************************************************************************
*																		*
*  Problem 8 : Parenthesis (��ȣ)										*
*																		*
************************************************************************/
/************************************************************************
*	����������Ŵ��� ��ǻ�Ͱ��к� 3�г�	 		�� CLC					*
*	20103378 ����ȣ, 20103389 �ֿ���, 20123426 ������					* 
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
	FILE* in_file; // �Է� file�� ������ ���� ����ü ������
	int test_case; // test_case�� ����
	
	in_file = fopen("input.txt","r"); // ���� ����
	/* file open fail */
	if(in_file == NULL) {
		printf("cannot open the file\n");
		exit(1);
	}

	fscanf(in_file, "%d", &test_case); // test_case ���� �Է�
	while(test_case--) {
		char par[PARMAX] = {0};

		EnterRoom(&in_file, par);
		PrintVaild(isParenthesis(par));
	}
	fclose(in_file);

	return 0;
}
/************************************************************
* ��ȣ String�� �Է¹޴� �Լ�								*
************************************************************/
void EnterRoom(FILE** in_file, char par[]) {
	/* ��ȣ �Է� */
	fscanf(*in_file, "%s ", par);
}
/****************************************************************
* ��ȣ�� ��Ȯ������ �˻��ϴ� �Լ�								*
* ��Ȯ���� ������ -1, ��Ȯ�ϸ� 0 ��ȯ						    *
****************************************************************/
int isParenthesis(char par[]) {
	char stack[STACKMAX] = {0}; // ���� (������ ������� �ʾƵ� ��)
	int pStack=0;		  // ���� �ε��� ������
	int i;

	/* '(' �϶��� ���ÿ� �ְ� ')'�� ���� ���ÿ��� (�� ���� */
	for(i=0; par[i]!='\0'; i++)
	{
		if(par[i]=='(') {
			// ������ �� ���ִ°��� '('�� �� ������ �߸� ��.
			if(pStack==STACKMAX)
				return -1;
			stack[pStack++] = '('; // ���ÿ� ����ִ´�.
		}
		else {
			// ������ ����µ� ')'�� ������ �߸� ��
			if(pStack == 0)
				return -1;
			else 
				stack[--pStack] = 0; // ���ÿ��� '('�� ����.
		}
	}
	// ������ ������ ������ �� ���¸� ����, ������ ������� ������ �߸� ��.
	if(pStack == 0)
		return 0;  
	else 
		return -1;
}
/****************************************
*	��ȣ�� �������� ���				*
****************************************/
void PrintVaild(int n) {
	if(n==0)
		printf("%s\n", "YES");
	else
		printf("%s\n", "NO");
}