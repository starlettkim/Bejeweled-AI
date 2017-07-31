#include "board.h"
#include "derived_board.h"
#include <iostream>

using namespace std;

Board::Board(int width, int height, int num) {
	width_ = width;
	height_ = height;
	num_ = num;
	matrix = new char*[height_];
	for (int i = 0; i < height_; i++) {
		matrix[i] = new char[width_];
	}
}

Board::~Board() {
	for (int i = 0; i < height_; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

/*
* 현재 보드 상태에서 가장 높은 기대값을 갖는 작업을 선택하여 리턴한다.
*/
InterchangeOperation Board::GetMaxExpectOperation() {
	InterchangeOperation max_operation;
	double max_expect_value = 0;
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			for (int k = 0; k < 4; k++) {
				InterchangeOperation operation(i, j, k);
				DerivedBoard* derived_board;
				try {
					derived_board
						= new DerivedBoard(dynamic_cast<const Board*>(this), operation);
				}
				catch (OutOfRangeException& e) {
					continue;
				}
				
				if (derived_board->CurrentScore() == 0) {
					continue;
				}
				double expect_value = derived_board->GetExpectValue();
				if (max_expect_value <= expect_value) {
					max_expect_value = expect_value;
					max_operation = operation;
				}
			}
		}
	}
	return max_operation;
}