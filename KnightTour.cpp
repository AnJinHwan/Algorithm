/**********************************************************
*                ü���� ���� ����� ����                  *
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

class KnightTour { 
public:   
	KnightTour();     // ������
	KnightTour(int sizeRow, int sizeCol);  //������
    bool buildKnightTour(int startRow, int startCol);     
	void printBoard();  // ü���� �迭 ���� ���
private:
	typedef int boardType[MAX_SIZE][MAX_SIZE];            
	bool recurKnightTour(int startRow, int startCol,int move);      
	bool isValidMove (int row, int col);  
    int sizeRow, sizeCol;     // ü������ ��� �� ũ��
	boardType board;	// ü���� �迭
};  
  
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
    
	return recurKnightTour(startRow-1, startCol-1, 1); // ���������� ������� ���� ��θ� ��������� Ȯ��
}

bool KnightTour::recurKnightTour(int row, int col, int move) {     
	int nextRow, nextCol;

    if (move == sizeRow*sizeCol)         // �ѱ����� ������ ������ move�� ���� 1 ������Ű�� �� ���� �����ϹǷ�
		return true;          // move�� ĭ�� ������ �������� ��� ��Ҹ� ������ ��ΰ� ����(true)
	
	for(int dir=0; dir<8; dir++)     {         // ���� ������ �ϳ��� Ȯ��
		nextRow = row + direction[dir][0];  // ���� ����� �� ����
		nextCol = col + direction[dir][1];	// ���� ����� �� ����

        if(isValidMove(nextRow, nextCol))         {  // ���� ��Ұ� ������ ��Ż���� �ʰ� ������ �ʾҴ� ��Ҷ��
			board[nextRow][nextCol] = move+1;	// ���� ��ҿ� ���븦 ����
			if(recurKnightTour(nextRow, nextCol, move+1)) { // ���� ��� ���� ������ ��ΰ� �����ϸ�
				return true;	// true�� ���������� ��ȯ
			}
			else
				board[nextRow][nextCol] = 0;	// ��ΰ� �������� ������ ������ ���� 0���� ����
        }     
	}          
	
	return false;
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