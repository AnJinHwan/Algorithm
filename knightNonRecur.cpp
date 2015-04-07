/**********************************************************
*       체스판 위의 기사의 여행 (비재귀적 알고리즘)       *
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

class Point {	// 스택에 저장할 구조
public:
	Point();
	Point(int x, int y, int d);
	int getX();
	int getY();
	int getD();
private:
	int xpos;	// 행 좌표
	int ypos;	// 열 좌표
	int dir;	// 다음 이동할 방향
};

class Stack {	// Point 구조로 스택 연산을 수행하는 클래스
public:
	Stack(int stackCapacity = 64);
	bool IsEmpty() const;
	bool IsFull() const;
	Point& Top() const;
	void Push(const Point& item);
	void Pop();
private:
	int top;	// 배열 인덱스(-1이면 빈 스택)
	Point* stack;	// 배열 포인터
	int capacity;	// 허용하는 원소 개수 
};

class KnightTour { 
public:   
	KnightTour();     // 생성자
	KnightTour(int sizeRow, int sizeCol);  //생성자
    bool buildKnightTour(int startRow, int startCol);     
	void printBoard();  // 체스판 배열 원소 출력
private:
	typedef int boardType[MAX_SIZE][MAX_SIZE];            
	bool nonRecurTour(int startRow, int startCol);      
	bool isValidMove (int row, int col);  
    int sizeRow, sizeCol;     // 체스판의 행과 열 크기
	boardType board;	// 체스판 배열
};  

Point::Point() {
	xpos = -1, ypos = -1; dir = -1;
}

Point::Point(int x, int y, int d) {
	xpos = x, ypos = y; dir = d;
}

int Point::getX() { return xpos; }

int Point::getY() { return ypos; }

int Point::getD() { return dir; }

Stack::Stack(int stackCapacity) : capacity(stackCapacity) {
	stack = new Point[capacity];	// stackCapacity 만큼의 크기의 배열 생성
	top = -1;
}

inline bool Stack::IsEmpty() const { return top == -1; }	// 빈 스택이면 true 반환

inline bool Stack::IsFull() const { return top == capacity-1; }	// 스택이 꽉 차면 true 반환

inline Point& Stack::Top() const {	// 맨 위의 배열 원소 반환
	if(!IsEmpty())
		return stack[top];
}

void Stack::Push(const Point& x) {	// 맨 위에 Point 객체 삽입
	stack[++top] = x;
}

void Stack::Pop() {	// 맨 위의 Point 객체 제거
	if(!IsEmpty())
		stack[top--].~Point();
}

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
    
	return nonRecurTour(startRow-1, startCol-1); // 시작점에서 출발했을 때의 경로를 비재귀적으로 확인
}

bool KnightTour::nonRecurTour(int row, int col) {
	int size = sizeRow*sizeCol;	// 행과 열의 사이즈를 곱한 값을
	Stack* s = new Stack(size);	// 스택의 크기로 전달해 생성

	int dir = 0;	// 방향 변수(0~7까지 8가지 방향)
	int move = 1;	// 2차원 board 행렬에 넣을 값(이동 순서를 나타냄)

	s -> Push(Point(row, col, 0));	// 스택에 시작 Point 저장

	for(; !(s -> IsFull()); ) {	// 스택이 꽉 찰 때까지 무한루프
		row = s -> Top().getX();	// 스택 맨 위 Point의 행 값
		col = s -> Top().getY();// 스택 맨 위 Point의 열 값
		dir = s -> Top().getD();// 스택 맨 위 Point의 방향
	
		if(isValidMove(row+direction[dir][0], col+direction[dir][1])) {// 맨위 Point가 가리키는 곳이 갈 수 있는 곳이면
			row += direction[dir][0];	
			col += direction[dir][1];

			s -> Push(Point(row, col, 0));	// 그 곳을 행과 열 값으로 갖는 새 Point를 스택에 저장(방향은 0으로 설정)
			board[row][col] = ++move;	// board 행렬에 1 증가된 move 표시
			
			continue;	// 다음 for문 진행
		}
		else {
			while(1) {	// 맨위 Point가 가리키는 곳이 갈 수 없는 곳이며
				if(s -> Top().getD() == 7) {	// 방향이 7이라면(= 8방향 모두 갈 곳이 없으면)
					board[s -> Top().getX()][s -> Top().getY()] = 0;	// move를 저장했던 곳을 0으로 되돌리고
					--move;	// move를 1 감소
					s -> Pop();	// 갈 곳이 없는 Point를 스택에서 제거하고
					if(s -> IsEmpty()) // 스택이 비면(경로가 존재하지 않음)
						return false;	// false 반환
				}
				else
					break;
			}
			
			row = s -> Top().getX();	// 스택 맨 위 Point의 행 값
			col = s -> Top().getY();// 스택 맨 위 Point의 열 값
			dir = s -> Top().getD() + 1;	
			// while문을 탈출했으므로 스택 맨 위 Point의 방향은 7보다 작다.
			// 1을 더해서 다음 방향으로 경로 탐색 준비

			s -> Pop();	// 스택 맨 위 Point의 행, 열, 방향 값을 받아와서 스택에서 Point를 제거한 뒤
			s -> Push(Point(row, col, dir));	// 같은 행, 같은 열, 다른 방향을 갖는 새 Point 저장(다음 경로 탐색)
		}
	}
	return true;	// IsFull()에서 true를 반환했으므로 경로 존재 (최종적으로 true 반환)
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