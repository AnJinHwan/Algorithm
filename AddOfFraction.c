/*******************************************************
*     				 분수의 덧셈		               *
*******************************************************/

/*******************************************************  
*    국민대학교 전자정보통신대학 컴퓨터공학부 3학년    *
*                                     20123426 최진성  *
*******************************************************/

#include <stdio.h>
#include <stdlib.h>

unsigned int gcd(unsigned int x, unsigned int y);

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
		unsigned int n1, n2, d1, d2;	// 입력받을 input 값
		unsigned int num, den;	// 결과값 분자와 분모(약분 전)
		unsigned int gcdTwoDen;	// 두 분수의 분모의 최대공약수
		unsigned int gcdDenNum; // 더해진 결과의 분자, 분모의 최대공약수

		fscanf(file, "%u %u %u %u", &n1, &d1, &n2, &d2);	// 분수1의 분자, 분모, 분수2의 분자, 분모를 입력받음
		
		gcdTwoDen = gcd(d1, d2);	// 두 분수의 분모의 최대공약수를 반환
		
		den = d1 * d2 / gcdTwoDen;	// 두 수의 곱 = 두 수의 최대공약수 * 두 수의 최소공배수
		num = (n1 * d2 / gcdTwoDen) + (n2 * d1 / gcdTwoDen);	// 분모의 최소공배수로 통분하여 덧셈한 결과 
		
		gcdDenNum = gcd(num, den);	// 기약분수로 만들기 위해 분자, 분모의 최대공약수를 구함

		printf("%u %u\n", num/gcdDenNum, den/gcdDenNum); // 약분한 최종 결과
	}
	
	fclose(file);
}

unsigned int gcd(unsigned int x, unsigned int y) {
	if(x == 0)	// x가 0이면
		return y;	// 최대공약수는 y
	
	if(y == 0)	// y가 0이면
		return x;	// 최대공약수는 x

	return ((x >= y) ? (gcd(y, x%y)) : (gcd(x, y%x)));	// 큰 수를 작은 수로 나눈 나머지와 작은 수를 인자로 재귀 함수 호출
}