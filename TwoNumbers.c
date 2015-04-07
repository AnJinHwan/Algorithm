/************************************************************************
*																		*
*  Problem 2 : Two Numbers												*
*																		*
************************************************************************/
/************************************************************************
*	전자정보통신대학 컴퓨터공학부 3학년									*
*	20123426 최진성														* 
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void EnterElement(FILE** in_file, int num);
int TargetNumCount(int elmt_num, int target_num);
int intcmp(const void* val1, const void* val2);
int qsearch(int start, int end, int key) ;

int* s; // 집합 배열
int max_idx; // s 배열을 참조할 수 있는 최대 인덱스
char double_count = 0; // 가장 가까운 수가 같을 때를 위한 flag

int main()
{
	FILE* in_file; // 입력 file의 정보를 받을 구조체 포인터
	int test_case; // test_case의 개수

	fopen_s(&in_file,"input.txt","r"); // 파일 열기
	/* file open fail */
	if(in_file == NULL) {
		printf("cannot open the file\n");
		exit(1);
	}

	fscanf_s(in_file, "%d", &test_case); // test_case 개수 입력
	while(test_case--) {
		int elmt_num; // 집합의 원소 개수
		int k;		  // 찾는 두 원소의 합
		int num_count;// 찾는 수와 일치하거나 가장 가까운 두 원소(부분집합)의 개수

		fscanf_s(in_file, "%d %d", &elmt_num, &k); // 총 원소의 개수와 찾는 두 수의 합 입력
		EnterElement(&in_file, elmt_num);		   // 집합의 원소들 입력
		
		qsort(s, elmt_num, sizeof(s[0]), intcmp);  // 퀵 정렬

		num_count = TargetNumCount(elmt_num, k);   // k와 일치하거나 가까운 두 원소(부분집합)의 개수 계산
		printf("%d\n", num_count); // 개수 출력

		free(s); // 동적할당한 메모리 해제
	}
	fclose(in_file);

	return 0;
}
/* 퀵 정렬에 이용될 비교하는 함수 */
int intcmp(const void* val1, const void* val2) {
	return *(int*)val1 - *(int*)val2;
}
/******************************************************************
*	필요한 만큼의 메모리를 동적할당하고 데이터를 입력받는 함수    *
******************************************************************/
void EnterElement(FILE** in_file, int num) {
	int i;

	s = (int*)malloc(sizeof(int) * num); // 필요한 만큼 메모리 할당
	max_idx = num-1;

	for(i=0; i<num; i++)
		fscanf_s(*in_file, "%d", s+i); // 데이터(집합의 원소) 입력
}
/******************************************************************
*	찾는 수와 두 원소(부분집합)의 합이 일치하거나 				  *
*   가장 가까운 부분집합의 개수를 찾아주는 함수					  *
******************************************************************/
int TargetNumCount(int elmt_num, int target_num) {
	int target_count = 0;	// 두 원소의 합이 찾는 수와 일치하는 개수
	int near_target = 0;	// 가장 가까운 수와의 거리(절대값)
	int near_count = 0;   // 두 원소의 합이 절대값 차이만큼나는 수의 개수
	int key;			// 합하여 target_num이 되는 키 값
	int abs_val;		// 절대값
	int i;

	for(i=0; i<elmt_num-1; i++) {
		key = target_num - s[i];  // 더해서 target_num이 될 수 있는 key값을 구한다.
		
		double_count=0; // 카운트 초기화
		if(i+1 == elmt_num-1) // 검사 할 값이 하나밖에 없으면 바로 계산 (남은 원소가 2개)
			abs_val = abs(key-s[elmt_num-1]);
		else // 남은 원소가 3개 이상일 때
			abs_val = qsearch(i+2, elmt_num-1, key); // key값과 가장 가까운 값과 차이의 절대값을 구한다

		/* 두 수의 합이 찾는 수와 같으면 count 올림 */
		if(abs_val == 0)
			target_count++;	

		/* 같지않고 절대값 차이가 같으면 가까운 수 count 올림 */
		else if(abs_val == near_target) {
			near_count += 1 + double_count; // double_count에 따라 1 or 2가 올라간다.
		}

		/* 초기값이거나 합과 찾는 수와 거리가 현재의 합과 찾는 수의 거리보다 가까우면 가까운 수로 변경 */
		else if(near_target == 0 || abs_val < near_target) { 
			near_target = abs_val;
			near_count = 1 + double_count; // double_count에 따라 초기값이 1 or 2
		}
	}

	/* 찾는 수가 있으면 찾는 수의 개수 return, 아니면 가까운 수의 개수 return */
	if(target_count != 0) {
		return target_count;
	}
	else {
		return near_count;
	}
}
/****************************************************************************
*  정렬된 배열 s에서 원하는 key값과 차이의 절대값이 가장 작은 것을 찾아		*
*  절대값을 반환하는 함수 똑같은 키 값이 있으면 0을 반환하는 함수.			*
*  같은 키값이 없다면 key값과 가장 가까운 값과 차이의 절대값을 return 한다. *
****************************************************************************/
int qsearch(int start, int end, int key) {
	int mid = (end+start)/2;	// 배열의 중간 위치

	/* 반씩 잘라나가다가 같아진다면 (가장 가까운 수를 찾음) */
	/* key값은 항상 마지막 남은 배열의 값과 같거나			*/
	/* 마지막 남은 배열과 이전 배열 사이에 존재한다.		*/
	if(start == end) {
		int abs_curr = abs(key - s[start]);	// 마지막 남은 배열과 키 값의 차이
		int abs_prev = abs(key - s[start-1]); // 이전 배열과 키 값의 차이

		// 차이가 같다면 count를 하나 더 올림
		if(abs_curr == abs_prev)
			double_count=1;

		// 마지막 남은 배열과 key값이 같다면 차이가 0이므로 0이 반환.
		// 같지 않다면 둘 중 가까운 수와의 차이의 절대값을 반환
		return (abs_curr < abs_prev)? abs_curr : abs_prev;
	}
	
	// key값이 찾는 부분의 최소값보다 작을 때 (최악의 경우인 맨 처음 바로 된다면 i-1과 비교)
	if(key < s[start]) {
		int abs_curr = abs(key - s[start]);
		int abs_prev = abs(key - s[start-1]);

		if(abs_curr == abs_prev) {
			double_count = 1;
		}
		return (abs_curr < abs_prev)? abs_curr : abs_prev;
	}

	// key값이 배열의 최대값보다 크면 최대값이 가장 가까움
	else if(key > s[end])
		return abs(key - s[end]);

	// 검사하는 배열 범위에 절반의 왼쪽에 key값이 포함될 때
	else if(key >= s[start] && key <= s[mid])
		return qsearch(start, mid, key);

	// 검사하는 배열 범위에 절반의 오른쪽에 key값이 포함될 때
	else if(key > s[mid] && key <= s[end])
		return qsearch(mid+1, end, key);
}