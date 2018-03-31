#include "htable.h"
#include <vector>
#include <algorithm>
#include <omp.h>
using namespace std;

void build_st(int root, int l, int r, htable **hts, vector<htable> &htables,
		bool *vis, vector<int> &q);
htable merge_htables(vector<htable> &htables);
