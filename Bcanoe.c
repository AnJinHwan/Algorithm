/************************************************************************
*																		*
*  Problem 6 : B_Canoe													*
*																		*
************************************************************************/
/************************************************************************
*	전자정보통신대학 컴퓨터공학부 3학년									*
*	20103378 임종호	20103389 최원범 20123426 최진성						* 
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 1000	// n의 최대 수
#define MAXRES 1000000  // 두 클래스의 합의 최대 경우의 수
#define MAXWEIGHT 10000000  // weight의 최대 수

void EnterData(FILE** in_file, int classes[][MAXNUM], int* k, int* n);	// 데이터(weight) 입력하는 함수
int sort(int arr[MAXNUM], int n);			// 정렬하는 함수
void sumTwoClass(int classes[][MAXNUM], int n, int* residx1, int* residx2); // 클래스 1,2 그리고 3,4를 더하는 함수
int Find(int classes[][MAXNUM], int k, int n, int residx1, int residx2);	// k와 같거나 가까운 수를 찾는 함수
int qsearch(int start, int end, int key);	// key값을 검색하는 함수
int Nearest(int n, int m, int k);  // n과 m중 k와 가까운 수를 찾는 함수

int res[2][MAXRES] = {0}; // 두 클래스의 합을 받을 배열

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
		int classes[4][MAXNUM] = {0}; // weight를 저장할 배열
		int k, n; // 찾는 값, 학생 수
		int residx1=0, residx2=0; // res[0]과 res[1]배열의 원소 개수
		
		EnterData(&in_file, classes, &k, &n); // 데이터 입력
		sumTwoClass(classes, n, &residx1, &residx2); // 1,2 와 3,4 클래스를 더함
		printf("%d\n", Find(classes, k, n, residx1, residx2)); // k와 가까운 수를 찾아서 출력
	}
	fclose(in_file); // input.txt 파일 닫기

	return 0;
}
/* 퀵 정렬에 이용될 비교하는 함수 */
int intcmp(const void* val1, const void* val2) {
	return *(int*)val1 - *(int*)val2;
}
/****************************************************************
*	데이터를 입력받는 함수										*
****************************************************************/
void EnterData(FILE** in_file, int classes[][MAXNUM], int* k, int* n)
{
	int i, j;

	fscanf(*in_file, "%d %d ", k, n); // 찾는 수 k와 학생 수 n을 입력 
	/* 4개의 클래스에 weight 입력 */
	for(i=0; i<4; i++) {
		for(j=0; j<(*n); j++) {
			fscanf(*in_file, "%d ", &classes[i][j]);
		}
	}
}
/****************************************************************
*	배열을 입력받아서 오름차순으로 정렬하고 같은 수의 개수를	*
*	세서 반환하는 함수. 배열의 원소는 arr[n] <= 20000000		*
****************************************************************/
int sort(int arr[MAXNUM], int n) 
{
	int i;
	int temp;
	int count=0; // 같은 수의 개수

	qsort(arr, n, sizeof(arr[0]), intcmp); // 오름차순 정렬

	/* 같은 수를 찾아서 아주 큰 크기로 만듦 */
	temp = arr[0];
	for(i=1; i<n; i++) {
		if(temp==arr[i]) {
			arr[i] = MAXWEIGHT*2+1; // 최대크기 + 1
			count++; // 같은 수의 개수 카운트
		}
		else
			temp = arr[i];
	}

	qsort(arr, n, sizeof(arr[0]), intcmp); // 다시 오름차순 정렬

	return count; // 같은 수 개수 반환
}
/********************************************************************
*	클래스 1,2와 3,4를 더하여 res배열에 입력하는 함수				*
*	입력하고 배열의 인덱스를 residx에다가 입력						*
********************************************************************/
void sumTwoClass(int classes[][MAXNUM], int n, int* residx1, int* residx2) 
{
	int i, j;

	/* res 배열에 클래스 1,2와 3,4를 더한 값을 입력 */
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++) 
		{
			res[0][(*residx1)++] = classes[0][i] + classes[1][j];
			res[1][(*residx2)++] = classes[2][i] + classes[3][j];
		}
	}

	/* res배열을 정렬하고 겹치는 수만큼 인덱스에서 빼준다 */
	*residx1 -= sort(res[0],*residx1);
	*residx2 -= sort(res[1],*residx2);
}
/********************************************************************
*	res[0]배열과 res[1]배열에서 하나씩 뽑아 더한 값이 k와 같거나	*
*	가장 가까운 수를 반환하는 함수									*
********************************************************************/
int Find(int classes[][MAXNUM], int k, int n, int residx1, int residx2)
{
	int weight, key; // 찾은 값(반환할 값), res[1]배열에서 찾아야 할 key값
	int i; 

	if(res[0][0] + res[1][0] > k) // 가장 작은 수끼리 더한게 k보다 크면 가장 작은 수 반환
		return res[0][0]+res[1][0];
	else if(res[0][residx1-1] + res[1][residx2-1] <= k) // 가장 큰 수끼리 더한게 k보다 작거나 같으면 가장 큰 수 반환
		return res[0][residx1-1] + res[1][residx2-1];

	weight = -1; // weight 초기화
	for(i=0; i<residx1; i++)
	{	
		key = k-res[0][i]; // res[1]에서 찾아야할 key값
		if(residx2 > 1)
			weight = Nearest(weight, res[0][i] + qsearch(1, residx2-1, key), k); // 기존의 weight와 찾은 weight를 비교
		else // res[1] 배열에 원소가 하나 일 때
			weight = Nearest(weight, res[0][i] + res[1][0], k);
		if(weight==k) // k와 같은 수를 찾으면 바로 반환
			break;
	}

	return weight; // 같은 수를 못 찾으면 가까운 수 반환
}
/****************************************************************************
*  정렬된 배열 res에서 원하는 key값과 차이의 절대값이 가장 작은 것을 찾아	*
*  원소의 값을 반환하는 함수. 똑같은 키 값이 있으면 그 값 반환				*
****************************************************************************/
int qsearch(int start, int end, int key) {
	int mid = (end+start)/2;	// 배열의 중간 위치

	// 반씩 잘라나가다가 같아진다면 (가장 가까운 수를 찾음) 
	// key값은 항상 마지막 남은 배열의 값과 같거나			
	// 마지막 남은 배열과 이전 배열 사이에 존재한다.		
	if(start == end) {
		int abs_curr = abs(key - res[1][start]);	// 마지막 남은 배열과 키 값의 차이
		int abs_prev = abs(key - res[1][start-1]);  // 이전 배열과 키 값의 차이

		// 마지막 남은 배열과 key값이 같다면 차이가 0이므로 같은 수 반환.
		// 같지 않다면 둘 중 가까운 수를 반환
		return (abs_curr < abs_prev)? res[1][start] : res[1][start-1];
	}

	// key값이 찾는 부분의 최소값보다 작을 때 (최악의 경우인 맨 처음 바로 된다면 i-1과 비교)
	if(key < res[1][start]) {
		int abs_curr = abs(key - res[1][start]);
		int abs_prev = abs(key - res[1][start-1]);

		return (abs_curr < abs_prev)? res[1][start] : res[1][start-1];
	}

	// key값이 배열의 최대값보다 크면 최대값이 가장 가까움
	else if(key > res[1][end])
		return res[1][end];

	// 검사하는 배열 범위에 절반의 왼쪽에 key값이 포함될 때
	else if(key >= res[1][start] && key <= res[1][mid])
		return qsearch(start, mid, key);

	// 검사하는 배열 범위에 절반의 오른쪽에 key값이 포함될 때
	else if(key > res[1][mid] && key <= res[1][end])
		return qsearch(mid+1, end, key);
}
/************************************************************
*  n과 m중 k와 가까운 값을 반환하는 함수					*
*  두 수의 k와의 거리가 똑같으면 n과 m중 작은 수를 반환		*
************************************************************/
int Nearest(int n, int m, int k)
{
	if(n==-1) // 초기값일 때는 m값을 바로 반환
		return m;
	else if(abs(n-k) == abs(m-k)) // 거리가 같을 땐 작은 수 반환
		return (n<m)? n:m;
	else if(abs(n-k) < abs(m-k)) // n이 가까울 때
		return n;
	else  // m과 가가울 때
		return m;
}
