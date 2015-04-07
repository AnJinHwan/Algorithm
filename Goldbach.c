/*******************************************************
*     		     Goldbach's Conjecture                 *
*******************************************************/

/*******************************************************  
*    국민대학교 전자정보통신대학 컴퓨터공학부 3학년	   *
*     20103378 임종호 20103389 최원범 20123426 최진성  *
*******************************************************/

#include <stdio.h>
#include <stdlib.h>

int isNatNum(int n);

void main(void) {
	FILE *file;
	int i, nocase, num;
	
	file = fopen("input.txt", "r");
	if(file == NULL) 
		exit(1);

	fscanf(file, "%d", &nocase);

	for(i = 0; i < nocase; i++) {
		int j;
		fscanf(file, "%d", &num);	// input값을 입력받아서
		num/=2;						// 반값을 저장(두 수의 차이를 최소화하기 위해 같은 값일 때부터 검사)

		for(j = 0; j <= num-2; j++) {	// 검사 대상을 가장 작은 소수인 2 이상으로 제한
			if(isNatNum(num-j) && isNatNum(num+j)) {	// for문을 돌 때마다 검사 대상들의 차이가 2씩 증가
				printf("%d %d\n", num-j, num+j);
				break;
			}
		}
	}
	
	fclose(file);
}

int isNatNum(int n) {
	int i;
	
	for(i = n/2; i > 1; i--)	// n이 소수가 아니라면 가장 큰 약수(n을 제외한)는 n/2보다 작거나 같음
		if(!(n%i))	// 나머지가 0이면(나눠떨어지면)
			return 0;	// n은 소수가 아님
	
	return 1;	// n은 소수
}