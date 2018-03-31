#include "populate_htables.h"

unordered_set<string> parse_file(const node &nd) {
	file_handler fh(nd.get_path());
	unordered_set<string> s;
	string word;
	while((word = fh.get_next_word()).size() > 0) {
		s.insert(word);
	}
	return s;
}

vector<node> bfs_step(const vector<node> &frontier, const config &cfg,
		vector<htable> *ans) {
	vector<vector<node> > temp(cfg.num_threads);
#pragma omp parallel for
	for(int i = 0; i < frontier.size(); i++) {
		int id = omp_get_thread_num();
		if(frontier[i].is_leaf()) {
			if(frontier[i].pass_filters())
				(*ans)[id].absorb(parse_file(frontier[i]));
		} else {
			vector<node> C = frontier[i].get_children();
			temp[id].insert(temp[id].end(), C.begin(), C.end());
		}
	}
	vector<int> pre(cfg.num_threads);
	int total = temp[0].size();
	for(int i = 1; i < cfg.num_threads; i++) {
		pre[i] = pre[i - 1] + temp[i - 1].size();
		total += temp[i].size();
	}
	vector<node> res(total);
#pragma omp parallel for
	for(int i = 0; i < pre.size(); i++) {
		for(int j = 0; j < temp[i].size(); j++) {
			res[pre[i] + j] = temp[i][j];
		}
	}
	return res;
}

vector<htable> populate_htables(const config &cfg) {
	vector<htable> ans(cfg.num_threads);
	vector<node> frontier;
	for(int i = 0; i < cfg.root_dirs.size(); i++) {
		frontier.push_back(node(cfg.root_dirs[i]));
	}
	while(frontier.size() > 0) {
		frontier = bfs_step(frontier, cfg, &ans);
	}
	return ans;
}
