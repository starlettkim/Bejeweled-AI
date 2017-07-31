#ifndef __BOARD_H__
#define __BOARD_H__

#include "operation.h"
#include <iostream>

using namespace std;

// ��ȯ �۾��� ������ ���带 �Ѿ�� throw�Ǵ� ���� Ŭ����.
struct OutOfRangeException {};

// �Էµ� �ʱ� ���� ���¸� �����Ѵ�.
class Board {
public:
	Board() {}
	Board(int width, int height, int num);
	~Board();
	InterchangeOperation GetMaxExpectOperation();

	// Getter functions
	char** Matrix() const { return matrix; }
	int Width() const { return width_; }
	int Height() const { return height_; }
	int Num() const { return num_; }

	friend istream& operator >> (istream& is, Board& board);
	int step = 0;
	double ratio = 1.0;

protected:
	char** matrix;
	int width_, height_, num_;
};

#endif