#ifndef __OPERATION_H__
#define __OPERATION_H__

#include <vector>
#include <iostream>

using namespace std;

enum Direction { UP = 0, DOWN, LEFT, RIGHT };

// row_행 col_열의 블록을 dir_방향(enum Direction 참조)의 블록과 교환하는 작업을 나타낸다.
class InterchangeOperation {
public:
	InterchangeOperation() {}
	InterchangeOperation(int row, int col, int dir)
		: row_(row), col_(col), dir_(dir) {}

	int row_, col_, dir_;
};

class ChangeOperation {
public:
	ChangeOperation() {}
	ChangeOperation(vector<pair<pair<int, int>, char> >& to_change)
		: to_change_(to_change) {}

	// Todo: pair<pair<int, int>, char> 대신 클래스를 사용하는게 훨씬 나을듯
	vector<pair<pair<int, int>, char> > to_change_;
};

#endif