/************************************************************************
*																		*
*  Problem 1 : A bowling												*
*																		*
************************************************************************/
/************************************************************************
*	����������Ŵ��� ��ǻ�Ͱ��к� 3�г�									*
*	20123426 ������														* 
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_PIN 3 
#define MAX_SCORE 90
#define MAX_FRAME 10

int EnterScore(FILE** in_file);
int TotalScore(int n, int end_n);
void PrintScore(int play_num);

int* score; // �����Ҵ��Ͽ� ������ ���� ������
int main()
{
	FILE* in_file; // �Է� file�� ������ ���� ����ü ������
	int test_case; // test_case�� ���� (game�� Ƚ��)

	fopen_s(&in_file,"input.txt","r"); // ���� ����
	/* file open fail */
	if(in_file == NULL) {
		printf("cannot open the file\n");
		exit(1);
	}

	fscanf_s(in_file, "%d", &test_case); // game ȸ�� �Է�
	while(test_case--) {
		int play_num; // ���� ���� ȸ��
		int i;

		play_num = EnterScore(&in_file); // ������ score�� �Է��ϰ� ���� ȸ���� ����.
		PrintScore(play_num);

		free(score); // �Ҵ��ߴ� �޸� ����
	}
	fclose(in_file);

	return 0;
}
/************************************************************************
*   score�� �����Ҵ� ���ְ� in_file���� �����͸� �Է¹޾�				*
*	�Է¹��� ������ ������ return ���ִ� �Լ�							*
************************************************************************/
int EnterScore(FILE** in_file) {
	int num, i;
	
	fscanf_s(*in_file, "%d", &num); // ������ ������ �Է� ����.
	score = (int*)malloc(sizeof(int)*num); // ������ ������ŭ �����Ҵ�
	for(i=0; i<num; i++) { // score�� ���� �����߸� ���� �Է�
		fscanf_s(*in_file, "%d", &score[i]);
	}

	return num; // ������ ���� return
}
/****************************************************************************
*   0������ �˻��Ͽ� ������ ������ ������ ���ϴ� �Լ�						*
*	������ �߻��ϸ� ���� �� �ִ� �ְ� ������ ������ return �Ͽ� ����� ����	*
*	end_n-n : ���� ȸ�� �� ���� ��� ���� ���� ȸ��							*
****************************************************************************/
int TotalScore(int n, int end_n, int frame) {
	/* ���� �������� �������� �ּҷ� ĥ �� �ִ� ȸ���� �ִ�� ĥ �� �ִ� ȸ���� */
	/* ����Ͽ� ���� ȸ���� �� �����ȿ� ���� ������ ����					*/
	if( MAX_FRAME-frame+2 > end_n-n || (MAX_FRAME-frame)*2+3 < end_n-n ) {
		return -MAX_SCORE;
	}

	if(frame==10) { // ������ ������
		if(end_n-n == 3) {
			if( score[n]!=MAX_PIN && score[n]+score[n+1]!=MAX_PIN ) // ���� (��Ʈ����ũ�� ���� ġ�� ���ϸ� 2���� ��ȸ)
				return -MAX_SCORE;
			else
				return score[n]+score[n+1]+score[n+2]; // ������ frame������ ��Ʈ����ũ�� ������ �߰� ������ ����.
		}
		else if(end_n-n == 2)
		{
			if( score[n]+score[n+1]>=MAX_PIN ) // ���� (������ �ʰ��ϰų� ��� �Ѿ�� 3���� �ƾ�� ��)
				return -MAX_SCORE;
			else
				return score[n]+score[n+1]; // �߰� ���� ����. (���� ������ ��)
		}
	}
	
	if(score[n]==MAX_PIN){ // ��Ʈ����ũ
		return score[n]+score[n+1]+score[n+2]+TotalScore(n+1,end_n,frame+1); // ���� �� ���� ȸ���� ������ ����.
	}
	else{
		if(score[n]+score[n+1]>MAX_PIN) // ���� (�� ���� �ʰ�)
			return -MAX_SCORE;

		if(score[n]+score[n+1]==MAX_PIN) // �����
			return score[n]+score[n+1]+score[n+2]+TotalScore(n+2,end_n,frame+1); // ���� �� ���� ȸ���� ������ ����.
		else // �� ���� ��ȸ�� ���� �� �� �Ѱ��� ���
			return score[n]+score[n+1]+TotalScore(n+2,end_n,frame+1);
	}
}
/****************************************************************
*	TotalScore�� ����ϴ� �Լ�									*
*   TotalScore �Լ��� return ���� ����̸� �ùٸ� ��			*
*	TotalScore �Լ��� return ���� �����̸� ����					*
****************************************************************/
void PrintScore(int play_num) {
	int total;
	if( (total=TotalScore(0, play_num, 1)) >= 0 ) { // ���� ������ ����� ����.
		printf("%d\n", total);
	}
	else // �����̸� ����
		printf("error\n");
}