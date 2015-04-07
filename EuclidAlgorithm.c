/*******************************************************
*				  유클리드 알고리즘					   *
*******************************************************/

/*******************************************************  
*    국민대학교 전자정보통신대학 컴퓨터공학부 3학년    *
*                                     20123426 최진성  *
*******************************************************/

#include <stdio.h>
#include <stdlib.h>

unsigned int Euclid(unsigned int x, unsigned int y);

void main(void)
{
	FILE *file;
	int i, nocase;
	
	file = fopen("input.txt", "r");
	if(file == NULL) 
		exit(1);

	fscanf(file, "%d", &nocase);

	for(i=0; i<nocase; i++)
	{
		unsigned int n1, n2;
		fscanf(file, "%u %u", &n1, &n2);	// 표준입력으로 두 정수를 받아서
		printf("%u\n", Euclid(n1, n2));		// 최대공약수를 구하는 함수에 인자로 전달
	}
	
	fclose(file);
}

unsigned int Euclid(unsigned int x, unsigned int y) {
	if(x == 0)	// x가 0이면
		return y;	// 최대공약수는 y
	
	if(y == 0)	// y가 0이면
		return x;	// 최대공약수는 x

	return ((x >= y) ? (Euclid(y, x%y)) : (Euclid(x, y%x)));	// 큰 수를 작은 수로 나눈 나머지와 작은 수를 인자로 재귀 함수 호출
}