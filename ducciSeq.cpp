/************************************************************************
*																		*
*  Problem 9 : Ducci Sequence											*
*																		*
************************************************************************/
/************************************************************************
*	����������Ŵ��� ��ǻ�Ͱ��к� 3�г�									*
*	20103378 ����ȣ	20103389 �ֿ��� 20123426 ������						* 
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void ducciTest(int max, int arr[], int arr2[]);

int main()
{
	FILE* in_file; // �Է� file�� ������ ���� ����ü ������
	int test_case; // test_case�� ����
	int nodata;
	int ducci[16]={0};
	int ducciTmp[16]={0};
	in_file = fopen("input.txt","r"); // ���� ����
	/* file open fail */
	if(in_file == NULL) {
		printf("cannot open the file\n");
		exit(1);
	}

	fscanf(in_file, "%d", &test_case); // test_case ���� �Է�
	while(test_case--) {
		fscanf(in_file, "%d", &nodata); // DucciSequence ���� �Է�

		for(int i=0;i<nodata;i++)
			fscanf(in_file, "%d", &ducci[i]); // DucciSequence �˻��� ���� �Է�
		
		ducciTest(nodata,ducci,ducciTmp);
		
	}
	fclose(in_file); // input.txt ���� �ݱ�

	return 0;
}


/****************************************************************
*	�迭�� ������ �Է¹޾Ƽ� ���� ���밪�� ���������� ���ϰ�	*
*	ZERO ������ �Ǵ����� Ȯ��, count �÷��׸� �ξ��ִ� 1000���� *
*   �Ѵ��� Check �ؼ� LOOP ���� �Ǻ�                            *
****************************************************************/
void ducciTest(int max,int arr[], int arr2[]){
	int count =0;
	int tmp=0;
	while(1){	
		for(int j=0;j<max;j++){
			if(j!=max-1){
				arr2[j]=abs(arr[j]-arr[j+1]);
				
			}
			else if(j==max-1){
				arr2[j]=abs(arr[j]-arr[0]);
				
			}
		}
		count++;
		if(count>1000){
			printf("LOOP\n");
			break;
		}
		else{
			for(int k=0;k<max;k++){
				arr[k]=arr2[k];
				tmp += arr2[k];
			}
			if(tmp==0){
				printf("ZERO\n");
				break;
			}
			else{
				tmp=0;
				continue;
			}
		}

	}
}


