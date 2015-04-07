/**********************************************************
*                체스판 위의 기사의 여행                  *
**********************************************************/

/**********************************************************
*     국민대학교 전자정보통신대학 컴퓨터공학부 3학년      *
*                                        20123426 최진성  *
**********************************************************/

#include <iostream>
#include <fstream> 
#include <cstdlib>
using namespace std;  

const int MAX_SIZE = 9;	// 행과 열 크기의 최대값
static int direction[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};
// 기사가 움직일 수 있는 방향의 집합

class KnightTour { 
public:   
	KnightTour();     // 생성자
	KnightTour(int sizeRow, int sizeCol);  //생성자
    bool buildKnightTour(int startRow, int startCol);     
	void printBoard();  // 체스판 배열 원소 출력
private:
	typedef int boardType[MAX_SIZE][MAX_SIZE];            
	bool recurKnightTour(int startRow, int startCol,int move);      
	bool isValidMove (int row, int col);  
    int sizeRow, sizeCol;     // 체스판의 행과 열 크기
	boardType board;	// 체스판 배열
};  
  
KnightTour::KnightTour() {  // 행과 열의 크기가 주어지지 않을 경우
	sizeRow = sizeCol = 8;	// 기본 크기는 (8, 8)
}  

KnightTour::KnightTour(int sRow, int sCol) { // 행과 열의 크기가 주어질 경우
	if (sRow>=2 && sRow<=MAX_SIZE)	// 행 크기의 범위는 2 이상 MAX_SIZE 이하  
		sizeRow = sRow;    
	else         
		sizeRow = 8;	// 범위를 벗어날 경우 8로 지정  
    
	if (sCol>=2 && sCol<=MAX_SIZE)	// 열 크기의 범위는 2 이상 MAX_SIZE 이하    
		sizeCol = sCol;     
	else         
		sizeCol = 8;	// 범위를 벗어날 경우 8로 지정
}

void KnightTour::printBoard() {     
	for (int r = 0; r < sizeRow; r++)      {         
		for (int c = 0; c < sizeCol; c++)             
			cout << board[r][c] << " ";  
        cout <<endl;     
	} 
}

bool KnightTour::buildKnightTour(int startRow, int startCol) {      // 여행을 시작하기 위한 설정
	for (int r=0; r<sizeRow; r++)         
		for (int c=0; c<sizeCol; c++)             
			board[r][c]= 0;	// 체스판 위의 모든 값을 0으로 놓음
    
	if (startRow <= 0 || startRow > sizeRow)         
		startRow = 0;     
	
	if (startCol <= 0 || startCol > sizeCol)         
		startCol = 0;  
    
	board[startRow-1][startCol-1] = 1;  // 시작점의 값을 1로 놓음
    
	return recurKnightTour(startRow-1, startCol-1, 1); // 시작점에서 출발했을 때의 경로를 재귀적으로 확인
}

bool KnightTour::recurKnightTour(int row, int col, int move) {     
	int nextRow, nextCol;

    if (move == sizeRow*sizeCol)         // 한군데를 지나갈 때마다 move의 값을 1 증가시키고 그 곳에 저장하므로
		return true;          // move가 칸의 개수와 같아지면 모든 장소를 지나는 경로가 존재(true)
	
	for(int dir=0; dir<8; dir++)     {         // 여덟 방향을 하나씩 확인
		nextRow = row + direction[dir][0];  // 다음 장소의 행 정보
		nextCol = col + direction[dir][1];	// 다음 장소의 열 정보

        if(isValidMove(nextRow, nextCol))         {  // 다음 장소가 범위를 이탈하지 않고 지나지 않았던 장소라면
			board[nextRow][nextCol] = move+1;	// 다음 장소에 자취를 남김
			if(recurKnightTour(nextRow, nextCol, move+1)) { // 이후 모든 곳을 지나는 경로가 존재하면
				return true;	// true를 연쇄적으로 반환
			}
			else
				board[nextRow][nextCol] = 0;	// 경로가 존재하지 않으면 지나온 곳을 0으로 수정
        }     
	}          
	
	return false;
}

bool KnightTour::isValidMove(int row, int col) {  
	if(row>=sizeRow || row<0)	// row가 0 미만이거나 sizeRow 이상이면 무효   
		return false;            
	
	if(col>=sizeCol || col<0)   // col이 0 미만이거나 sizeCol 이상이면 무효
		return false;            
	
	if(board[row][col] != 0)    // (row, col) 위의 값이 0이 아니면 이미 지나간 곳이므로 무효
		return false;                  
	
	else						// 그 외엔 유효
		return true;      
}  
   
void main() {     
	ifstream inStream;     
	int numTestCases;  
    
	inStream.open("input.txt");     
	if (inStream.fail())     {         
		cerr << "Input file opening failed.\n";         
		exit(1);     
	}  
    
	inStream >> numTestCases;  
    
	for(int i=0; i<numTestCases; i++)     {         
		int sizeRow, sizeCol;         
		int startRow, startCol;  
        
		inStream >> sizeRow >> sizeCol;         
		inStream >> startRow >> startCol;

        KnightTour kTour(sizeRow, sizeCol);  
        if (kTour.buildKnightTour(startRow, startCol)) {   // 경로가 존재하면          
			cout << 1 << endl;	// 1을 출력하고
			kTour.printBoard();	// 체스판을 출력
		} else             // 존재하지 않으면
			cout << 0 << endl;   // 0을 출력
	}    

	inStream.close();
}   