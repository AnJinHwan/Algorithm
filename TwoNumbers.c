/************************************************************************
*																		*
*  Problem 2 : Two Numbers												*
*																		*
************************************************************************/
/************************************************************************
*	����������Ŵ��� ��ǻ�Ͱ��к� 3�г�									*
*	20123426 ������														* 
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void EnterElement(FILE** in_file, int num);
int TargetNumCount(int elmt_num, int target_num);
int intcmp(const void* val1, const void* val2);
int qsearch(int start, int end, int key) ;

int* s; // ���� �迭
int max_idx; // s �迭�� ������ �� �ִ� �ִ� �ε���
char double_count = 0; // ���� ����� ���� ���� ���� ���� flag

int main()
{
	FILE* in_file; // �Է� file�� ������ ���� ����ü ������
	int test_case; // test_case�� ����

	fopen_s(&in_file,"input.txt","r"); // ���� ����
	/* file open fail */
	if(in_file == NULL) {
		printf("cannot open the file\n");
		exit(1);
	}

	fscanf_s(in_file, "%d", &test_case); // test_case ���� �Է�
	while(test_case--) {
		int elmt_num; // ������ ���� ����
		int k;		  // ã�� �� ������ ��
		int num_count;// ã�� ���� ��ġ�ϰų� ���� ����� �� ����(�κ�����)�� ����

		fscanf_s(in_file, "%d %d", &elmt_num, &k); // �� ������ ������ ã�� �� ���� �� �Է�
		EnterElement(&in_file, elmt_num);		   // ������ ���ҵ� �Է�
		
		qsort(s, elmt_num, sizeof(s[0]), intcmp);  // �� ����

		num_count = TargetNumCount(elmt_num, k);   // k�� ��ġ�ϰų� ����� �� ����(�κ�����)�� ���� ���
		printf("%d\n", num_count); // ���� ���

		free(s); // �����Ҵ��� �޸� ����
	}
	fclose(in_file);

	return 0;
}
/* �� ���Ŀ� �̿�� ���ϴ� �Լ� */
int intcmp(const void* val1, const void* val2) {
	return *(int*)val1 - *(int*)val2;
}
/******************************************************************
*	�ʿ��� ��ŭ�� �޸𸮸� �����Ҵ��ϰ� �����͸� �Է¹޴� �Լ�    *
******************************************************************/
void EnterElement(FILE** in_file, int num) {
	int i;

	s = (int*)malloc(sizeof(int) * num); // �ʿ��� ��ŭ �޸� �Ҵ�
	max_idx = num-1;

	for(i=0; i<num; i++)
		fscanf_s(*in_file, "%d", s+i); // ������(������ ����) �Է�
}
/******************************************************************
*	ã�� ���� �� ����(�κ�����)�� ���� ��ġ�ϰų� 				  *
*   ���� ����� �κ������� ������ ã���ִ� �Լ�					  *
******************************************************************/
int TargetNumCount(int elmt_num, int target_num) {
	int target_count = 0;	// �� ������ ���� ã�� ���� ��ġ�ϴ� ����
	int near_target = 0;	// ���� ����� ������ �Ÿ�(���밪)
	int near_count = 0;   // �� ������ ���� ���밪 ���̸�ŭ���� ���� ����
	int key;			// ���Ͽ� target_num�� �Ǵ� Ű ��
	int abs_val;		// ���밪
	int i;

	for(i=0; i<elmt_num-1; i++) {
		key = target_num - s[i];  // ���ؼ� target_num�� �� �� �ִ� key���� ���Ѵ�.
		
		double_count=0; // ī��Ʈ �ʱ�ȭ
		if(i+1 == elmt_num-1) // �˻� �� ���� �ϳ��ۿ� ������ �ٷ� ��� (���� ���Ұ� 2��)
			abs_val = abs(key-s[elmt_num-1]);
		else // ���� ���Ұ� 3�� �̻��� ��
			abs_val = qsearch(i+2, elmt_num-1, key); // key���� ���� ����� ���� ������ ���밪�� ���Ѵ�

		/* �� ���� ���� ã�� ���� ������ count �ø� */
		if(abs_val == 0)
			target_count++;	

		/* �����ʰ� ���밪 ���̰� ������ ����� �� count �ø� */
		else if(abs_val == near_target) {
			near_count += 1 + double_count; // double_count�� ���� 1 or 2�� �ö󰣴�.
		}

		/* �ʱⰪ�̰ų� �հ� ã�� ���� �Ÿ��� ������ �հ� ã�� ���� �Ÿ����� ������ ����� ���� ���� */
		else if(near_target == 0 || abs_val < near_target) { 
			near_target = abs_val;
			near_count = 1 + double_count; // double_count�� ���� �ʱⰪ�� 1 or 2
		}
	}

	/* ã�� ���� ������ ã�� ���� ���� return, �ƴϸ� ����� ���� ���� return */
	if(target_count != 0) {
		return target_count;
	}
	else {
		return near_count;
	}
}
/****************************************************************************
*  ���ĵ� �迭 s���� ���ϴ� key���� ������ ���밪�� ���� ���� ���� ã��		*
*  ���밪�� ��ȯ�ϴ� �Լ� �Ȱ��� Ű ���� ������ 0�� ��ȯ�ϴ� �Լ�.			*
*  ���� Ű���� ���ٸ� key���� ���� ����� ���� ������ ���밪�� return �Ѵ�. *
****************************************************************************/
int qsearch(int start, int end, int key) {
	int mid = (end+start)/2;	// �迭�� �߰� ��ġ

	/* �ݾ� �߶󳪰��ٰ� �������ٸ� (���� ����� ���� ã��) */
	/* key���� �׻� ������ ���� �迭�� ���� ���ų�			*/
	/* ������ ���� �迭�� ���� �迭 ���̿� �����Ѵ�.		*/
	if(start == end) {
		int abs_curr = abs(key - s[start]);	// ������ ���� �迭�� Ű ���� ����
		int abs_prev = abs(key - s[start-1]); // ���� �迭�� Ű ���� ����

		// ���̰� ���ٸ� count�� �ϳ� �� �ø�
		if(abs_curr == abs_prev)
			double_count=1;

		// ������ ���� �迭�� key���� ���ٸ� ���̰� 0�̹Ƿ� 0�� ��ȯ.
		// ���� �ʴٸ� �� �� ����� ������ ������ ���밪�� ��ȯ
		return (abs_curr < abs_prev)? abs_curr : abs_prev;
	}
	
	// key���� ã�� �κ��� �ּҰ����� ���� �� (�־��� ����� �� ó�� �ٷ� �ȴٸ� i-1�� ��)
	if(key < s[start]) {
		int abs_curr = abs(key - s[start]);
		int abs_prev = abs(key - s[start-1]);

		if(abs_curr == abs_prev) {
			double_count = 1;
		}
		return (abs_curr < abs_prev)? abs_curr : abs_prev;
	}

	// key���� �迭�� �ִ밪���� ũ�� �ִ밪�� ���� �����
	else if(key > s[end])
		return abs(key - s[end]);

	// �˻��ϴ� �迭 ������ ������ ���ʿ� key���� ���Ե� ��
	else if(key >= s[start] && key <= s[mid])
		return qsearch(start, mid, key);

	// �˻��ϴ� �迭 ������ ������ �����ʿ� key���� ���Ե� ��
	else if(key > s[mid] && key <= s[end])
		return qsearch(mid+1, end, key);
}