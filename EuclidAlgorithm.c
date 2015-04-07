/*******************************************************
*				  ��Ŭ���� �˰���					   *
*******************************************************/

/*******************************************************  
*    ���δ��б� ����������Ŵ��� ��ǻ�Ͱ��к� 3�г�    *
*                                     20123426 ������  *
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
		fscanf(file, "%u %u", &n1, &n2);	// ǥ���Է����� �� ������ �޾Ƽ�
		printf("%u\n", Euclid(n1, n2));		// �ִ������� ���ϴ� �Լ��� ���ڷ� ����
	}
	
	fclose(file);
}

unsigned int Euclid(unsigned int x, unsigned int y) {
	if(x == 0)	// x�� 0�̸�
		return y;	// �ִ������� y
	
	if(y == 0)	// y�� 0�̸�
		return x;	// �ִ������� x

	return ((x >= y) ? (Euclid(y, x%y)) : (Euclid(x, y%x)));	// ū ���� ���� ���� ���� �������� ���� ���� ���ڷ� ��� �Լ� ȣ��
}