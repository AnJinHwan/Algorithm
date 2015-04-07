/*******************************************************
*     		     Goldbach's Conjecture                 *
*******************************************************/

/*******************************************************  
*    ���δ��б� ����������Ŵ��� ��ǻ�Ͱ��к� 3�г�	   *
*     20103378 ����ȣ 20103389 �ֿ��� 20123426 ������  *
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
		fscanf(file, "%d", &num);	// input���� �Է¹޾Ƽ�
		num/=2;						// �ݰ��� ����(�� ���� ���̸� �ּ�ȭ�ϱ� ���� ���� ���� ������ �˻�)

		for(j = 0; j <= num-2; j++) {	// �˻� ����� ���� ���� �Ҽ��� 2 �̻����� ����
			if(isNatNum(num-j) && isNatNum(num+j)) {	// for���� �� ������ �˻� ������ ���̰� 2�� ����
				printf("%d %d\n", num-j, num+j);
				break;
			}
		}
	}
	
	fclose(file);
}

int isNatNum(int n) {
	int i;
	
	for(i = n/2; i > 1; i--)	// n�� �Ҽ��� �ƴ϶�� ���� ū ���(n�� ������)�� n/2���� �۰ų� ����
		if(!(n%i))	// �������� 0�̸�(������������)
			return 0;	// n�� �Ҽ��� �ƴ�
	
	return 1;	// n�� �Ҽ�
}