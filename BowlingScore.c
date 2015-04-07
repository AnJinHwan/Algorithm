/************************************************************************
*																		*
*  Problem 1 : A bowling												*
*																		*
************************************************************************/
/************************************************************************
*	전자정보통신대학 컴퓨터공학부 3학년									*
*	20123426 최진성														* 
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_PIN 3 
#define MAX_SCORE 90
#define MAX_FRAME 10

int EnterScore(FILE** in_file);
int TotalScore(int n, int end_n);
void PrintScore(int play_num);

int* score; // 동적할당하여 점수를 넣을 포인터
int main()
{
	FILE* in_file; // 입력 file의 정보를 받을 구조체 포인터
	int test_case; // test_case의 개수 (game의 횟수)

	fopen_s(&in_file,"input.txt","r"); // 파일 열기
	/* file open fail */
	if(in_file == NULL) {
		printf("cannot open the file\n");
		exit(1);
	}

	fscanf_s(in_file, "%d", &test_case); // game 회수 입력
	while(test_case--) {
		int play_num; // 공을 굴린 회수
		int i;

		play_num = EnterScore(&in_file); // 점수를 score에 입력하고 굴린 회수를 받음.
		PrintScore(play_num);

		free(score); // 할당했던 메모리 해제
	}
	fclose(in_file);

	return 0;
}
/************************************************************************
*   score에 동적할당 해주고 in_file에서 데이터를 입력받아				*
*	입력받은 데이터 개수를 return 해주는 함수							*
************************************************************************/
int EnterScore(FILE** in_file) {
	int num, i;
	
	fscanf_s(*in_file, "%d", &num); // 데이터 개수를 입력 받음.
	score = (int*)malloc(sizeof(int)*num); // 데이터 개수만큼 동적할당
	for(i=0; i<num; i++) { // score에 핀을 쓰러뜨린 개수 입력
		fscanf_s(*in_file, "%d", &score[i]);
	}

	return num; // 데이터 개수 return
}
/****************************************************************************
*   0번부터 검사하여 프레임 단위로 점수를 더하는 함수						*
*	에러가 발생하면 받을 수 있는 최고 점수를 음수로 return 하여 결과가 음수	*
*	end_n-n : 굴린 회수 중 아직 계산 하지 않은 회수							*
****************************************************************************/
int TotalScore(int n, int end_n, int frame) {
	/* 현재 프레임을 기준으로 최소로 칠 수 있는 회수와 최대로 칠 수 있는 회수를 */
	/* 계산하여 남은 회수가 이 범위안에 들어가지 않으면 에러					*/
	if( MAX_FRAME-frame+2 > end_n-n || (MAX_FRAME-frame)*2+3 < end_n-n ) {
		return -MAX_SCORE;
	}

	if(frame==10) { // 마지막 프레임
		if(end_n-n == 3) {
			if( score[n]!=MAX_PIN && score[n]+score[n+1]!=MAX_PIN ) // 에러 (스트라이크나 스페어를 치지 못하면 2번의 기회)
				return -MAX_SCORE;
			else
				return score[n]+score[n+1]+score[n+2]; // 마지막 frame에서는 스트라이크나 스페어에서 추가 점수가 없음.
		}
		else if(end_n-n == 2)
		{
			if( score[n]+score[n+1]>=MAX_PIN ) // 에러 (개수가 초과하거나 모두 넘어가면 3번을 쳤어야 함)
				return -MAX_SCORE;
			else
				return score[n]+score[n+1]; // 추가 점수 없음. (남은 점수를 합)
		}
	}
	
	if(score[n]==MAX_PIN){ // 스트라이크
		return score[n]+score[n+1]+score[n+2]+TotalScore(n+1,end_n,frame+1); // 다음 두 번의 회수의 점수를 더함.
	}
	else{
		if(score[n]+score[n+1]>MAX_PIN) // 에러 (핀 개수 초과)
			return -MAX_SCORE;

		if(score[n]+score[n+1]==MAX_PIN) // 스페어
			return score[n]+score[n+1]+score[n+2]+TotalScore(n+2,end_n,frame+1); // 다음 한 번의 회수의 점수를 더함.
		else // 두 번의 기회에 핀을 다 못 넘겼을 경우
			return score[n]+score[n+1]+TotalScore(n+2,end_n,frame+1);
	}
}
/****************************************************************
*	TotalScore를 출력하는 함수									*
*   TotalScore 함수의 return 값이 양수이면 올바른 합			*
*	TotalScore 함수의 return 값이 음수이면 에러					*
****************************************************************/
void PrintScore(int play_num) {
	int total;
	if( (total=TotalScore(0, play_num, 1)) >= 0 ) { // 합한 점수가 양수면 정상.
		printf("%d\n", total);
	}
	else // 음수이면 에러
		printf("error\n");
}