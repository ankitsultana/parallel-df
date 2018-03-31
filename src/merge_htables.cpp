#include "merge_htables.h"

void build_st(int root, int l, int r, htable **hts, vector<htable> &htables,
		bool *vis, vector<int> &q) {
	if(l == r) {
		vis[root] = true;
		hts[root] = &htables[l];
		q.push_back(root / 2);
		return ;
	}
	vis[root] = false;
	int mid = (l + r) >> 1;
	build_st(root*2, l, mid, hts, htables, vis, q);
	build_st(root*2+1, mid+1, r, hts, htables, vis, q);
}

htable merge_htables(vector<htable> &htables) {
	if(htables.size() == 0) return htable();
	else if(htables.size() == 1) return htables[0];
	int size_st = 4 * htables.size();
	htable** hts = new htable*[size_st];
	bool *vis = new bool[size_st];
	vector<int> q;
	build_st(1, 0, htables.size() - 1, hts, htables, vis, q);
	while(q.size() > 0) {
		sort(q.begin(), q.end());
		q.resize(unique(q.begin(), q.end()) - q.begin());
#pragma omp parallel for
		for(int i = 0; i < q.size(); i++) {
			int id = omp_get_thread_num();
			if(vis[q[i]] == false and vis[q[i]*2] and vis[q[i]*2+1]) {
				vis[q[i]] = true;
				if(hts[q[i]*2]->size() > hts[q[i]*2+1]->size()) {
					hts[q[i]*2]->absorb(*hts[q[i]*2+1]);
					hts[q[i]] = hts[q[i]*2];
				} else {
					hts[q[i]*2+1]->absorb(*hts[q[i]*2]);
					hts[q[i]] = hts[q[i]*2+1];
				}
			}
		}
		vector<int> nq;
		for(int i = 0; i < q.size(); i++) {
			int par = q[i] / 2;
			if(par > 0 and vis[par] == false and vis[par*2] and vis[par*2+1]) {
				nq.push_back(par);
			}
		}
		q = nq;
	}
	htable res = *(hts[1]);
	delete[] vis;
	free(hts);
	return res;
}
