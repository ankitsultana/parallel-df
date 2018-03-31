#include <bits/stdc++.h>
#include <omp.h>
#include <dirent.h>

#include "node.h"
#include "htable.h"
#include "merge_htables.h"
#include "populate_htables.h"
#include "config.h"

using namespace std;

pair<config, bool> set_config(int argc, char* argv[]) {
	pair<config, bool> res;
	res.second = true;
	if(argc != 7) {
		res.second = false; return res;
	}
	for(int i = 1; i < argc; ) {
		if(strcmp(argv[i], "-config") == 0) {
			string cfg_file = string(argv[i + 1]);
			ifstream ifs(cfg_file, ifstream::in);
			string line;
			while(getline(ifs, line)) {
				res.first.root_dirs.push_back(line);
			}
			i += 2;
		} else if(strcmp(argv[i], "-k") == 0) {
			res.first.k = atoi(argv[i + 1]);
			i += 2;
		} else if(strcmp(argv[i], "-nt") == 0) {
			res.first.num_threads = atoi(argv[i + 1]);
			i += 2;
		} else {
			res.second = false;
			break;
		}
	}
	return res;
}

template<typename T>
vector<pair<string, int> > get_kmost(const T &htable, int k) {
	using Data = pair<int, string>;
	priority_queue<Data> q;
	for(const auto &xx: htable) {
		q.push(make_pair(xx.second, xx.first));
	}
	vector<pair<string, int> > ans;
	for(int i = 0; i < k and q.size() > 0; i++) {
		auto f = q.top();
		ans.push_back(make_pair(f.second, f.first));
		q.pop();
	}
	return ans;
}

int main(int argc, char *argv[]) {
	std::ios_base::sync_with_stdio(false);
	auto tmp = set_config(argc, argv);
	auto cfg = tmp.first;
	if(tmp.second == false) {
		cerr << "usage : -config <path/to/config/file> -k <k> -nt <num_threads>" << endl;
		return 0;
	} else {
		cerr << "-----------------------------" << endl;
		cerr << "Configurations Loaded" << endl;
		cerr << "-----------------------------" << endl;
		cerr << "Number of Root Dirs: " << cfg.root_dirs.size() << endl;
		cerr << "Value of K:          " << cfg.k << endl;
		cerr << "Number of Threads:   " << cfg.num_threads << endl;
		cerr << "-----------------------------\n" << endl;
	}
	omp_set_num_threads(cfg.num_threads);
	vector<htable> htables = populate_htables(cfg);
	auto htable = merge_htables(htables);
	vector<pair<string, int> > kmost = get_kmost(htable, cfg.k);
	cout << "K-most frequent words are (in decreasing order):\n";
	int cnt = 0;
	for(auto &x: kmost) {
		cout << setw(4) << (++cnt) << " -> " << setw(15) << x.first
			<< " (freq = " << setw(6) << x.second << ")" << endl;
	}
	return 0;
}
