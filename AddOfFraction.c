/*******************************************************
*     				 �м��� ����		               *
*******************************************************/

/*******************************************************  
*    ���δ��б� ����������Ŵ��� ��ǻ�Ͱ��к� 3�г�    *
*                                     20123426 ������  *
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
		unsigned int n1, n2, d1, d2;	// �Է¹��� input ��
		unsigned int num, den;	// ����� ���ڿ� �и�(��� ��)
		unsigned int gcdTwoDen;	// �� �м��� �и��� �ִ�����
		unsigned int gcdDenNum; // ������ ����� ����, �и��� �ִ�����

		fscanf(file, "%u %u %u %u", &n1, &d1, &n2, &d2);	// �м�1�� ����, �и�, �м�2�� ����, �и� �Է¹���
		
		gcdTwoDen = gcd(d1, d2);	// �� �м��� �и��� �ִ������� ��ȯ
		
		den = d1 * d2 / gcdTwoDen;	// �� ���� �� = �� ���� �ִ����� * �� ���� �ּҰ����
		num = (n1 * d2 / gcdTwoDen) + (n2 * d1 / gcdTwoDen);	// �и��� �ּҰ������ ����Ͽ� ������ ��� 
		
		gcdDenNum = gcd(num, den);	// ���м��� ����� ���� ����, �и��� �ִ������� ����

		printf("%u %u\n", num/gcdDenNum, den/gcdDenNum); // ����� ���� ���
	}
	
	fclose(file);
}

unsigned int gcd(unsigned int x, unsigned int y) {
	if(x == 0)	// x�� 0�̸�
		return y;	// �ִ������� y
	
	if(y == 0)	// y�� 0�̸�
		return x;	// �ִ������� x

	return ((x >= y) ? (gcd(y, x%y)) : (gcd(x, y%x)));	// ū ���� ���� ���� ���� �������� ���� ���� ���ڷ� ��� �Լ� ȣ��
}