/************************************************************************
*																		*
*  Problem 9 : Ducci Sequence											*
*																		*
************************************************************************/
/************************************************************************
*	전자정보통신대학 컴퓨터공학부 3학년									*
*	20103378 임종호	20103389 최원범 20123426 최진성						* 
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void ducciTest(int max, int arr[], int arr2[]);

int main()
{
	FILE* in_file; // 입력 file의 정보를 받을 구조체 포인터
	int test_case; // test_case의 개수
	int nodata;
	int ducci[16]={0};
	int ducciTmp[16]={0};
	in_file = fopen("input.txt","r"); // 파일 열기
	/* file open fail */
	if(in_file == NULL) {
		printf("cannot open the file\n");
		exit(1);
	}

	fscanf(in_file, "%d", &test_case); // test_case 개수 입력
	while(test_case--) {
		fscanf(in_file, "%d", &nodata); // DucciSequence 개수 입력

		for(int i=0;i<nodata;i++)
			fscanf(in_file, "%d", &ducci[i]); // DucciSequence 검사할 수열 입력
		
		ducciTest(nodata,ducci,ducciTmp);
		
	}
	fclose(in_file); // input.txt 파일 닫기

	return 0;
}


/****************************************************************
*	배열과 개수를 입력받아서 차의 절대값을 연속적으로 구하고	*
*	ZERO 터플이 되는지를 확인, count 플래그를 두어최대 1000번이 *
*   넘는지 Check 해서 LOOP 인지 판별                            *
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


