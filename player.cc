/*
 * �� �ڵ�� "â��������Ʈ�����" ������ �⸻ ������ "â���� ����Ʈ���� ���� ������ȸ"��
 * ������ �ڵ��̴�. Python3 ������ "contest3.py"�� C++ ������ "refree.cpp"�� �Բ� �۵��Ѵ�.
 * Bejeweled ����(refree.cpp)�� �ڵ����� �����ϸ� ������ �� �� �ְ� �����Ͽ���. 
 *
 * @author	�Ѿ���б� ��ǻ�Ͱ��к� 2016025305 ������
 *			(Jihun Kim, starlettkim@gmail.com)
 * @since	2016-12-06
 */

#include "board.h"
#include <iostream>
#include <algorithm>

//#include <ctime>

using namespace std;

// ���带 �Է¹ޱ� ���� istream �����ε�.
istream& operator >> (istream& is, Board& board) {
	for (int i = 0; i < board.height_; i++) {
		for (int j = 0; j < board.width_; j++) {
			is >> board.matrix[i][j];
		}
	}
	return is;
}

// Operation�� ����ϱ� ���� ostream �����ε�.
ostream& operator << (ostream& os, const InterchangeOperation& oper) {
	char dir[4] = { 'U', 'D', 'L', 'R' };
	os << oper.col_ << " " << oper.row_ << " " << dir[oper.dir_] << endl;
	return os;
}

int main() {
	int W, H, N;
	cin >> W >> H >> N;
	Board board(W, H, N);
	cin >> board;	
	//clock_t begin = clock();
	cout << board.GetMaxExpectOperation();
	//cout << double(clock() - begin) / CLOCKS_PER_SEC;

	while (cin.good()) {
		int score;
		cin >> score >> board;
		//begin = clock();
		cout << board.GetMaxExpectOperation();
		//cout << double(clock() - begin) / CLOCKS_PER_SEC;
	}

	return 0;
}