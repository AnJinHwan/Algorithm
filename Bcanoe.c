/************************************************************************
*																		*
*  Problem 6 : B_Canoe													*
*																		*
************************************************************************/
/************************************************************************
*	����������Ŵ��� ��ǻ�Ͱ��к� 3�г�									*
*	20103378 ����ȣ	20103389 �ֿ��� 20123426 ������						* 
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 1000	// n�� �ִ� ��
#define MAXRES 1000000  // �� Ŭ������ ���� �ִ� ����� ��
#define MAXWEIGHT 10000000  // weight�� �ִ� ��

void EnterData(FILE** in_file, int classes[][MAXNUM], int* k, int* n);	// ������(weight) �Է��ϴ� �Լ�
int sort(int arr[MAXNUM], int n);			// �����ϴ� �Լ�
void sumTwoClass(int classes[][MAXNUM], int n, int* residx1, int* residx2); // Ŭ���� 1,2 �׸��� 3,4�� ���ϴ� �Լ�
int Find(int classes[][MAXNUM], int k, int n, int residx1, int residx2);	// k�� ���ų� ����� ���� ã�� �Լ�
int qsearch(int start, int end, int key);	// key���� �˻��ϴ� �Լ�
int Nearest(int n, int m, int k);  // n�� m�� k�� ����� ���� ã�� �Լ�

int res[2][MAXRES] = {0}; // �� Ŭ������ ���� ���� �迭

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
		int classes[4][MAXNUM] = {0}; // weight�� ������ �迭
		int k, n; // ã�� ��, �л� ��
		int residx1=0, residx2=0; // res[0]�� res[1]�迭�� ���� ����
		
		EnterData(&in_file, classes, &k, &n); // ������ �Է�
		sumTwoClass(classes, n, &residx1, &residx2); // 1,2 �� 3,4 Ŭ������ ����
		printf("%d\n", Find(classes, k, n, residx1, residx2)); // k�� ����� ���� ã�Ƽ� ���
	}
	fclose(in_file); // input.txt ���� �ݱ�

	return 0;
}
/* �� ���Ŀ� �̿�� ���ϴ� �Լ� */
int intcmp(const void* val1, const void* val2) {
	return *(int*)val1 - *(int*)val2;
}
/****************************************************************
*	�����͸� �Է¹޴� �Լ�										*
****************************************************************/
void EnterData(FILE** in_file, int classes[][MAXNUM], int* k, int* n)
{
	int i, j;

	fscanf(*in_file, "%d %d ", k, n); // ã�� �� k�� �л� �� n�� �Է� 
	/* 4���� Ŭ������ weight �Է� */
	for(i=0; i<4; i++) {
		for(j=0; j<(*n); j++) {
			fscanf(*in_file, "%d ", &classes[i][j]);
		}
	}
}
/****************************************************************
*	�迭�� �Է¹޾Ƽ� ������������ �����ϰ� ���� ���� ������	*
*	���� ��ȯ�ϴ� �Լ�. �迭�� ���Ҵ� arr[n] <= 20000000		*
****************************************************************/
int sort(int arr[MAXNUM], int n) 
{
	int i;
	int temp;
	int count=0; // ���� ���� ����

	qsort(arr, n, sizeof(arr[0]), intcmp); // �������� ����

	/* ���� ���� ã�Ƽ� ���� ū ũ��� ���� */
	temp = arr[0];
	for(i=1; i<n; i++) {
		if(temp==arr[i]) {
			arr[i] = MAXWEIGHT*2+1; // �ִ�ũ�� + 1
			count++; // ���� ���� ���� ī��Ʈ
		}
		else
			temp = arr[i];
	}

	qsort(arr, n, sizeof(arr[0]), intcmp); // �ٽ� �������� ����

	return count; // ���� �� ���� ��ȯ
}
/********************************************************************
*	Ŭ���� 1,2�� 3,4�� ���Ͽ� res�迭�� �Է��ϴ� �Լ�				*
*	�Է��ϰ� �迭�� �ε����� residx���ٰ� �Է�						*
********************************************************************/
void sumTwoClass(int classes[][MAXNUM], int n, int* residx1, int* residx2) 
{
	int i, j;

	/* res �迭�� Ŭ���� 1,2�� 3,4�� ���� ���� �Է� */
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++) 
		{
			res[0][(*residx1)++] = classes[0][i] + classes[1][j];
			res[1][(*residx2)++] = classes[2][i] + classes[3][j];
		}
	}

	/* res�迭�� �����ϰ� ��ġ�� ����ŭ �ε������� ���ش� */
	*residx1 -= sort(res[0],*residx1);
	*residx2 -= sort(res[1],*residx2);
}
/********************************************************************
*	res[0]�迭�� res[1]�迭���� �ϳ��� �̾� ���� ���� k�� ���ų�	*
*	���� ����� ���� ��ȯ�ϴ� �Լ�									*
********************************************************************/
int Find(int classes[][MAXNUM], int k, int n, int residx1, int residx2)
{
	int weight, key; // ã�� ��(��ȯ�� ��), res[1]�迭���� ã�ƾ� �� key��
	int i; 

	if(res[0][0] + res[1][0] > k) // ���� ���� ������ ���Ѱ� k���� ũ�� ���� ���� �� ��ȯ
		return res[0][0]+res[1][0];
	else if(res[0][residx1-1] + res[1][residx2-1] <= k) // ���� ū ������ ���Ѱ� k���� �۰ų� ������ ���� ū �� ��ȯ
		return res[0][residx1-1] + res[1][residx2-1];

	weight = -1; // weight �ʱ�ȭ
	for(i=0; i<residx1; i++)
	{	
		key = k-res[0][i]; // res[1]���� ã�ƾ��� key��
		if(residx2 > 1)
			weight = Nearest(weight, res[0][i] + qsearch(1, residx2-1, key), k); // ������ weight�� ã�� weight�� ��
		else // res[1] �迭�� ���Ұ� �ϳ� �� ��
			weight = Nearest(weight, res[0][i] + res[1][0], k);
		if(weight==k) // k�� ���� ���� ã���� �ٷ� ��ȯ
			break;
	}

	return weight; // ���� ���� �� ã���� ����� �� ��ȯ
}
/****************************************************************************
*  ���ĵ� �迭 res���� ���ϴ� key���� ������ ���밪�� ���� ���� ���� ã��	*
*  ������ ���� ��ȯ�ϴ� �Լ�. �Ȱ��� Ű ���� ������ �� �� ��ȯ				*
****************************************************************************/
int qsearch(int start, int end, int key) {
	int mid = (end+start)/2;	// �迭�� �߰� ��ġ

	// �ݾ� �߶󳪰��ٰ� �������ٸ� (���� ����� ���� ã��) 
	// key���� �׻� ������ ���� �迭�� ���� ���ų�			
	// ������ ���� �迭�� ���� �迭 ���̿� �����Ѵ�.		
	if(start == end) {
		int abs_curr = abs(key - res[1][start]);	// ������ ���� �迭�� Ű ���� ����
		int abs_prev = abs(key - res[1][start-1]);  // ���� �迭�� Ű ���� ����

		// ������ ���� �迭�� key���� ���ٸ� ���̰� 0�̹Ƿ� ���� �� ��ȯ.
		// ���� �ʴٸ� �� �� ����� ���� ��ȯ
		return (abs_curr < abs_prev)? res[1][start] : res[1][start-1];
	}

	// key���� ã�� �κ��� �ּҰ����� ���� �� (�־��� ����� �� ó�� �ٷ� �ȴٸ� i-1�� ��)
	if(key < res[1][start]) {
		int abs_curr = abs(key - res[1][start]);
		int abs_prev = abs(key - res[1][start-1]);

		return (abs_curr < abs_prev)? res[1][start] : res[1][start-1];
	}

	// key���� �迭�� �ִ밪���� ũ�� �ִ밪�� ���� �����
	else if(key > res[1][end])
		return res[1][end];

	// �˻��ϴ� �迭 ������ ������ ���ʿ� key���� ���Ե� ��
	else if(key >= res[1][start] && key <= res[1][mid])
		return qsearch(start, mid, key);

	// �˻��ϴ� �迭 ������ ������ �����ʿ� key���� ���Ե� ��
	else if(key > res[1][mid] && key <= res[1][end])
		return qsearch(mid+1, end, key);
}
/************************************************************
*  n�� m�� k�� ����� ���� ��ȯ�ϴ� �Լ�					*
*  �� ���� k���� �Ÿ��� �Ȱ����� n�� m�� ���� ���� ��ȯ		*
************************************************************/
int Nearest(int n, int m, int k)
{
	if(n==-1) // �ʱⰪ�� ���� m���� �ٷ� ��ȯ
		return m;
	else if(abs(n-k) == abs(m-k)) // �Ÿ��� ���� �� ���� �� ��ȯ
		return (n<m)? n:m;
	else if(abs(n-k) < abs(m-k)) // n�� ����� ��
		return n;
	else  // m�� ������ ��
		return m;
}
