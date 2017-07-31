#include "derived_board.h"
#include <algorithm>
#include <math.h>

using namespace std;

inline void DerivedBoard::Swap(char& lhs, char& rhs) {
	char tmp = lhs;
	lhs = rhs;
	rhs = tmp;
}

DerivedBoard::DerivedBoard(const Board* board, InterchangeOperation oper) {
	step = board->step + 1;
	width_ = board->Width();
	height_ = board->Height();
	num_ = board->Num();
	matrix = new char*[height_];
	for (int i = 0; i < height_; i++) {
		matrix[i] = new char[width_];
		for (int j = 0; j < width_; j++) {
			matrix[i][j] = board->Matrix()[i][j];
		}
	}

	if (oper.dir_ == Direction::UP) {
		if (oper.row_ <= 0) {
			throw OutOfRangeException();
		}
		Swap(matrix[oper.row_][oper.col_], matrix[oper.row_ - 1][oper.col_]);

	} else if (oper.dir_ == Direction::DOWN) {
		if (oper.row_ >= height_ - 1) {
			throw OutOfRangeException();
		}
		Swap(matrix[oper.row_][oper.col_], matrix[oper.row_ + 1][oper.col_]);

	} else if (oper.dir_ == Direction::LEFT) {
		if (oper.col_ <= 0) {
			throw OutOfRangeException();
		}
		Swap(matrix[oper.row_][oper.col_], matrix[oper.row_][oper.col_ - 1]);

	} else if (oper.dir_ == Direction::RIGHT) {
		if (oper.col_ >= width_ - 1) {
			throw OutOfRangeException();
		}
		Swap(matrix[oper.row_][oper.col_], matrix[oper.row_][oper.col_ + 1]);
	}
}

DerivedBoard::DerivedBoard(const Board* board, ChangeOperation oper) {
	step = board->step + 1;
	ratio = board->ratio * 1.5;
	width_ = board->Width();
	height_ = board->Height();
	num_ = board->Num();
	matrix = new char*[height_];
	for (int i = 0; i < height_; i++) {
		matrix[i] = new char[width_];
		for (int j = 0; j < width_; j++) {
			matrix[i][j] = board->Matrix()[i][j];
		}
	}

	for (auto it : oper.to_change_) {
		matrix[it.first.first][it.first.second] = it.second;
	}
}

double DerivedBoard::GetExpectValue() {
	double expect_value = 0;
	// 이 코드는 정확성을 희생하는 대신 연산량을 줄일 것이다.
	while (CurrentScore()) {
		expect_value += removed_blocks.size() * 10 * ratio;
		Update();
		ratio *= 1.5;
	}

	for (int i = 0; i < width_; i++) {
		int row = 0;
		while (row < height_ && !matrix[row][i]) {
			removed_blocks.insert(make_pair(row, i));
			row++;
		}
	}

	if (step == MAX_SEARCH_STEP) {
		return expect_value;
	}

	// 지워진 블록의 수가 너무 많으면 연산량이 많아지므로 그냥 대충 찍는다.
	if (static_cast<int>(pow(num_, removed_blocks.size())) > 1000) {
		return expect_value + 50 / num_;
	}

	// 현재 보드에서 점수가 발생한 경우, Change를 해본다.
	if (expect_value) {
		vector<pair<pair<int, int>, char> > change_operation;
		GetChangeOperations(change_operation);
		for (int i = 0; i < change_operations.size(); i++) {
			ChangeOperation operation(change_operations[i]);
			DerivedBoard derived_board(dynamic_cast<const Board*>(this), operation);
			expect_value += derived_board.GetExpectValue() / pow(num_, removed_blocks.size());
		}

	// 현재 보드에서 점수가 발생하지 않은 경우, Interchange를 해본다.
	} else {
		for (int i = 0; i < height_; i++) {
			for (int j = 0; j < width_; j++) {
				for (int k = 0; k < 4; k++) {
					InterchangeOperation operation(i, j, k);
					DerivedBoard* derived_board;

					try {
						derived_board = new DerivedBoard(dynamic_cast<const Board*>(this), operation);
					}
					catch (OutOfRangeException& e) {
						continue;
					}

					if (derived_board->CurrentScore() == 0) {
						continue;
					}
					expect_value += derived_board->GetExpectValue() / pow(num_, removed_blocks.size());
				}
			}
		}
	}

	return expect_value;
}

void DerivedBoard::GetChangeOperations(vector<pair<pair<int, int>, char> >& change_operation) {
	if (change_operation.size() == removed_blocks.size()) {
		change_operations.push_back(change_operation);
		change_operation.pop_back();
		return;
	}

	for (int i = 0; i < num_; i++) {
		auto it = removed_blocks.begin();
		advance(it, change_operation.size());
		int to_change_row = it->first;
		int to_change_col = it->second;
		change_operation.push_back(make_pair(make_pair(to_change_row, to_change_col), i + 'a'));
		GetChangeOperations(change_operation);
	}

	if (change_operation.size()) {
		change_operation.pop_back();
	}
}

// 점수를 내는 위치를 찾아 removed_blocks에 삽입하고 점수를 리턴한다.
int DerivedBoard::CurrentScore() {
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			if (matrix[i][j]) {

				// 오른쪽과 아래쪽으로 같은 블록을 찾는다.
				for (int k = 0; k < 2; k++) {
					// 매칭되는 row, col 쌍을 저장하는 set.
					set<pair<int, int> > matches;
					matches.insert(make_pair(i, j));
					int pos_row = i + (k == 0);
					int pos_col = j + (k == 1);

					while (pos_row < height_ && pos_col < width_
						&& matrix[pos_row][pos_col] == matrix[i][j]) {
						matches.insert(make_pair(pos_row, pos_col));
						pos_row += (k == 0);
						pos_col += (k == 1);
					}

					if (matches.size() >= 3) {
						for (auto it : matches) {
							removed_blocks.insert(it);
						}
					}
				}

			}
		}
	}
	return static_cast<int>(removed_blocks.size() * 10);
}

void DerivedBoard::Update() {
	for (auto it : removed_blocks) {
		int removed_row = it.first;
		int removed_col = it.second;
		for (int i = removed_row - 1; i >= 0; i--) {
			matrix[i + 1][removed_col] = matrix[i][removed_col];
		}
		matrix[0][removed_col] = 0;
	}
	removed_blocks.clear();
}