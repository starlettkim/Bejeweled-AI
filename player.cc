/*
 * 이 코드는 "창의적소프트웨어설계" 과목의 기말 과제인 "창의적 소프트웨어 설계 경진대회"에
 * 제출할 코드이다. Python3 파일인 "contest3.py"와 C++ 파일인 "refree.cpp"와 함께 작동한다.
 * Bejeweled 게임(refree.cpp)을 자동으로 수행하며 점수를 낼 수 있게 구성하였다. 
 *
 * @author	한양대학교 컴퓨터공학부 2016025305 김지훈
 *			(Jihun Kim, starlettkim@gmail.com)
 * @since	2016-12-06
 */

#include "board.h"
#include <iostream>
#include <algorithm>

//#include <ctime>

using namespace std;

// 보드를 입력받기 위한 istream 오버로딩.
istream& operator >> (istream& is, Board& board) {
	for (int i = 0; i < board.height_; i++) {
		for (int j = 0; j < board.width_; j++) {
			is >> board.matrix[i][j];
		}
	}
	return is;
}

// Operation을 출력하기 위한 ostream 오버로딩.
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