#ifndef __OPERATION_H__
#define __OPERATION_H__

#include <vector>
#include <iostream>

using namespace std;

enum Direction { UP = 0, DOWN, LEFT, RIGHT };

// row_�� col_���� ����� dir_����(enum Direction ����)�� ��ϰ� ��ȯ�ϴ� �۾��� ��Ÿ����.
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

	// Todo: pair<pair<int, int>, char> ��� Ŭ������ ����ϴ°� �ξ� ������
	vector<pair<pair<int, int>, char> > to_change_;
};

#endif