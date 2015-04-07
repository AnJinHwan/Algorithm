/**********************************************************
*       ü���� ���� ����� ���� (������� �˰���)       *
**********************************************************/

/**********************************************************
*     ���δ��б� ����������Ŵ��� ��ǻ�Ͱ��к� 3�г�      *
*                                        20123426 ������  *
**********************************************************/

#include <iostream>
#include <fstream> 
#include <cstdlib>
using namespace std;  

const int MAX_SIZE = 9;	// ��� �� ũ���� �ִ밪
static int direction[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};
// ��簡 ������ �� �ִ� ������ ����

class Point {	// ���ÿ� ������ ����
public:
	Point();
	Point(int x, int y, int d);
	int getX();
	int getY();
	int getD();
private:
	int xpos;	// �� ��ǥ
	int ypos;	// �� ��ǥ
	int dir;	// ���� �̵��� ����
};

class Stack {	// Point ������ ���� ������ �����ϴ� Ŭ����
public:
	Stack(int stackCapacity = 64);
	bool IsEmpty() const;
	bool IsFull() const;
	Point& Top() const;
	void Push(const Point& item);
	void Pop();
private:
	int top;	// �迭 �ε���(-1�̸� �� ����)
	Point* stack;	// �迭 ������
	int capacity;	// ����ϴ� ���� ���� 
};

class KnightTour { 
public:   
	KnightTour();     // ������
	KnightTour(int sizeRow, int sizeCol);  //������
    bool buildKnightTour(int startRow, int startCol);     
	void printBoard();  // ü���� �迭 ���� ���
private:
	typedef int boardType[MAX_SIZE][MAX_SIZE];            
	bool nonRecurTour(int startRow, int startCol);      
	bool isValidMove (int row, int col);  
    int sizeRow, sizeCol;     // ü������ ��� �� ũ��
	boardType board;	// ü���� �迭
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
	stack = new Point[capacity];	// stackCapacity ��ŭ�� ũ���� �迭 ����
	top = -1;
}

inline bool Stack::IsEmpty() const { return top == -1; }	// �� �����̸� true ��ȯ

inline bool Stack::IsFull() const { return top == capacity-1; }	// ������ �� ���� true ��ȯ

inline Point& Stack::Top() const {	// �� ���� �迭 ���� ��ȯ
	if(!IsEmpty())
		return stack[top];
}

void Stack::Push(const Point& x) {	// �� ���� Point ��ü ����
	stack[++top] = x;
}

void Stack::Pop() {	// �� ���� Point ��ü ����
	if(!IsEmpty())
		stack[top--].~Point();
}

KnightTour::KnightTour() {  // ��� ���� ũ�Ⱑ �־����� ���� ���
	sizeRow = sizeCol = 8;	// �⺻ ũ��� (8, 8)
}  

KnightTour::KnightTour(int sRow, int sCol) { // ��� ���� ũ�Ⱑ �־��� ���
	if (sRow>=2 && sRow<=MAX_SIZE)	// �� ũ���� ������ 2 �̻� MAX_SIZE ����  
		sizeRow = sRow;    
	else         
		sizeRow = 8;	// ������ ��� ��� 8�� ����  
    
	if (sCol>=2 && sCol<=MAX_SIZE)	// �� ũ���� ������ 2 �̻� MAX_SIZE ����    
		sizeCol = sCol;     
	else         
		sizeCol = 8;	// ������ ��� ��� 8�� ����
}

void KnightTour::printBoard() {     
	for (int r = 0; r < sizeRow; r++)      {         
		for (int c = 0; c < sizeCol; c++)             
			cout << board[r][c] << " ";  
        cout <<endl;     
	} 
}

bool KnightTour::buildKnightTour(int startRow, int startCol) {      // ������ �����ϱ� ���� ����
	for (int r=0; r<sizeRow; r++)         
		for (int c=0; c<sizeCol; c++)             
			board[r][c]= 0;	// ü���� ���� ��� ���� 0���� ����
    
	if (startRow <= 0 || startRow > sizeRow)         
		startRow = 0;     
	
	if (startCol <= 0 || startCol > sizeCol)         
		startCol = 0;  
    
	board[startRow-1][startCol-1] = 1;  // �������� ���� 1�� ����
    
	return nonRecurTour(startRow-1, startCol-1); // ���������� ������� ���� ��θ� ����������� Ȯ��
}

bool KnightTour::nonRecurTour(int row, int col) {
	int size = sizeRow*sizeCol;	// ��� ���� ����� ���� ����
	Stack* s = new Stack(size);	// ������ ũ��� ������ ����

	int dir = 0;	// ���� ����(0~7���� 8���� ����)
	int move = 1;	// 2���� board ��Ŀ� ���� ��(�̵� ������ ��Ÿ��)

	s -> Push(Point(row, col, 0));	// ���ÿ� ���� Point ����

	for(; !(s -> IsFull()); ) {	// ������ �� �� ������ ���ѷ���
		row = s -> Top().getX();	// ���� �� �� Point�� �� ��
		col = s -> Top().getY();// ���� �� �� Point�� �� ��
		dir = s -> Top().getD();// ���� �� �� Point�� ����
	
		if(isValidMove(row+direction[dir][0], col+direction[dir][1])) {// ���� Point�� ����Ű�� ���� �� �� �ִ� ���̸�
			row += direction[dir][0];	
			col += direction[dir][1];

			s -> Push(Point(row, col, 0));	// �� ���� ��� �� ������ ���� �� Point�� ���ÿ� ����(������ 0���� ����)
			board[row][col] = ++move;	// board ��Ŀ� 1 ������ move ǥ��
			
			continue;	// ���� for�� ����
		}
		else {
			while(1) {	// ���� Point�� ����Ű�� ���� �� �� ���� ���̸�
				if(s -> Top().getD() == 7) {	// ������ 7�̶��(= 8���� ��� �� ���� ������)
					board[s -> Top().getX()][s -> Top().getY()] = 0;	// move�� �����ߴ� ���� 0���� �ǵ�����
					--move;	// move�� 1 ����
					s -> Pop();	// �� ���� ���� Point�� ���ÿ��� �����ϰ�
					if(s -> IsEmpty()) // ������ ���(��ΰ� �������� ����)
						return false;	// false ��ȯ
				}
				else
					break;
			}
			
			row = s -> Top().getX();	// ���� �� �� Point�� �� ��
			col = s -> Top().getY();// ���� �� �� Point�� �� ��
			dir = s -> Top().getD() + 1;	
			// while���� Ż�������Ƿ� ���� �� �� Point�� ������ 7���� �۴�.
			// 1�� ���ؼ� ���� �������� ��� Ž�� �غ�

			s -> Pop();	// ���� �� �� Point�� ��, ��, ���� ���� �޾ƿͼ� ���ÿ��� Point�� ������ ��
			s -> Push(Point(row, col, dir));	// ���� ��, ���� ��, �ٸ� ������ ���� �� Point ����(���� ��� Ž��)
		}
	}
	return true;	// IsFull()���� true�� ��ȯ�����Ƿ� ��� ���� (���������� true ��ȯ)
}

bool KnightTour::isValidMove(int row, int col) {  
	if(row>=sizeRow || row<0)	// row�� 0 �̸��̰ų� sizeRow �̻��̸� ��ȿ   
		return false;            
	
	if(col>=sizeCol || col<0)   // col�� 0 �̸��̰ų� sizeCol �̻��̸� ��ȿ
		return false;            
	
	if(board[row][col] != 0)    // (row, col) ���� ���� 0�� �ƴϸ� �̹� ������ ���̹Ƿ� ��ȿ
		return false;                  
	
	else						// �� �ܿ� ��ȿ
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
        if (kTour.buildKnightTour(startRow, startCol)) {   // ��ΰ� �����ϸ�          
			cout << 1 << endl;	// 1�� ����ϰ�
			kTour.printBoard();	// ü������ ���
		} else             // �������� ������
			cout << 0 << endl;   // 0�� ���
	}    

	inStream.close();
}   