#include <vector>
#include <omp.h>

#include "htable.h"
#include "node.h"
#include "config.h"
#include "file_handler.h"

using namespace std;

vector<node> bfs_step(const vector<node> &frontier, const config &cfg,
		vector<htable> *ans);
vector<htable> populate_htables(const config &cfg);
