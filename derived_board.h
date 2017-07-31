#ifndef __DERIVED_BOARD_H__
#define __DERIVED_BOARD_H__

#include "board.h"
#include <algorithm>
#include <set>

/* 시뮬레이션을 해볼 단계 수. 현재 보드 상태에서 시뮬레이션을 너무 많이 진행할 경우 연산량이
과도하게 많아지기 때문에 임의의 단계까지만 시뮬레이팅을 한다. 연산시간에 따라 적절히 조정. */
#define MAX_SEARCH_STEP 2

using namespace std;

// 입력된 초기 보드 상태에서 시뮬레이팅해볼 보드 상태.
class DerivedBoard : public Board {
public:
	DerivedBoard(const Board* board, InterchangeOperation oper);
	DerivedBoard(const Board* board, ChangeOperation oper);
	~DerivedBoard() {}
	int CurrentScore();
	double GetExpectValue();

private:
	inline void Swap(char& lhs, char& rhs);
	void Update();
	void GetChangeOperations(vector<pair<pair<int, int>, char> >& change_operation);

	set<pair<int, int> > removed_blocks;
	vector<vector<pair<pair<int, int>, char> > > change_operations;
};

#endif