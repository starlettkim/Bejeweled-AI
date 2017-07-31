#ifndef __DERIVED_BOARD_H__
#define __DERIVED_BOARD_H__

#include "board.h"
#include <algorithm>
#include <set>

/* �ùķ��̼��� �غ� �ܰ� ��. ���� ���� ���¿��� �ùķ��̼��� �ʹ� ���� ������ ��� ���귮��
�����ϰ� �������� ������ ������ �ܰ������ �ùķ������� �Ѵ�. ����ð��� ���� ������ ����. */
#define MAX_SEARCH_STEP 2

using namespace std;

// �Էµ� �ʱ� ���� ���¿��� �ùķ������غ� ���� ����.
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